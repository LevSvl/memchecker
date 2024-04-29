#include<dirent.h>
#include<errno.h>
#include<stdlib.h>

#include"infocollector.h"

#define CURRENT_DIR "."
#define PARENT_DIR ".."

int scandir(const std::string &path);
extern int processfile(const std::string &);

int scanrun(const std::string &path)
{
  if (scandir(path) < 0){
    return -1;
  }
  showinfo();
  std::cout << RUNCOMMAND << std::endl;
  system(RUNCOMMAND);
  return 0;
}


int 
scandir(const std::string &path) 
{
  DIR *dirptr;
  dirptr = ::opendir(path.c_str());
  
  // Some problems or path is not a directory
  if (!dirptr){
    switch (errno)
    {

    case ETXTBSY:
    case EACCES:
    case EPERM:
      // Save permission info and return success
      // return 0;
      perror("opendir: No accsess to dir");
      exit(1);
      break;

    case EAGAIN:
      // try to scandir again?
      perror("opendir: Try to open dir again");
      exit(1);
      //break;

    case ENOENT:
      perror("opendir: Path does not exist or could not be read");
      return -1;

    case ENOTDIR:
      // ok, its file
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
  std::string childdirname;
  struct dirent *entry;
  // HERE
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
      // return -1;
      ;
    }
  }

  ::closedir(dirptr);
  return 0;
}