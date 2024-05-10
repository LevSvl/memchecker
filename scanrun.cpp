#include<dirent.h>
#include<errno.h>

#include"infocollector.h"

#define CURRENT_DIR "."
#define PARENT_DIR ".."

extern int scandir(const std::string &path);

extern void showinfo();
extern int processfile(const std::string &);
extern int vis_init();

int scanrun(const std::string &path)
{
  if (scandir(path) < 0){
    return -1;
  }
  showinfo();
  vis_init();
  return 0;
}


int 
scandir(const std::string &path) 
{
  DIR *dirptr;
  dirptr = ::opendir(path.c_str());
  
  if (!dirptr){
    switch (errno)
    {

    case ETXTBSY:
    case EACCES:
    case EPERM:
      // todo: 
      // Сохранить информацию о правах
      // и продолжить выполнение
      perror("opendir: No accsess to dir");
      exit(1);
      break;

    case EAGAIN:
      // todo:
      // Возможно, стоит как-то обработать
      perror("opendir: Try to open dir again");
      exit(1);

    case ENOENT:
      // Ошибка имени файла или директории
      perror("opendir: Path does not exist or could not be read");
      return -1;

    case ENOTDIR:
      // Это файл, обработать файл
      if (processfile(path) < 0){
        perror("Error during the file processing");
        return -1;
      }
      return 0;

    default:
      perror("Undefined error");
      return -1;
    }
  }

  // Для сканируемой папки рекурсивно
  // просканировать вложенные файлы и папки.
  // Папки текущей и родительской директорий
  // не сканировать не нужно.
  std::string childdirname;
  struct dirent *entry;

  while ((entry = ::readdir(dirptr))) {
    childdirname = entry->d_name;
    if (childdirname.compare(CURRENT_DIR) == 0){
      continue;
    } 
    else if (childdirname.compare(PARENT_DIR) == 0){
      continue;
    }

    std::string filepath = std::string(path + "/" + childdirname);
    if (scandir(filepath) < 0){
      return -1;
      ;
    }
  }

  ::closedir(dirptr);
  return 0;
}