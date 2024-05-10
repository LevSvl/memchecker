#include <tchar.h>
#include<errno.h>
#include<fileapi.h>
#include<windows.h>
#include"infocollector.h"

extern int addinfo(Node* node);

void fill_file_size(Node* node,const WIN32_FILE_ATTRIBUTE_DATA& fs_info)
{  
  DWORD64 full_size = fs_info.nFileSizeHigh;
  // Верхние 2 байта
  full_size = full_size << 32;
  // Нижние 2 байта
  full_size |= fs_info.nFileSizeLow;
  // Сохранить в node
  node->sz = full_size;
}

void 
fill_file_system_info(const WIN32_FILE_ATTRIBUTE_DATA& fs_info)
{
  ;
}

// Исправления проблем с кодировкой
LPCWSTR 
fix_windows_encoding_problems(const std::string &string_ascii)
{

  std::string c_string(string_ascii.begin(),string_ascii.end()); 
  std::wstring w_string(c_string.begin(), c_string.end());

  LPCWSTR string_unicode = w_string.c_str();
  
  return string_unicode;
}

// Извлекает всю необходимую информацию о файле,
// затем сохраняет в node
int processfile(const std::string &file_path)
{

  if (file_path.size() > MAX_PATH){
    return -1;
  }
  // Получить метаданные о файле 
  WIN32_FILE_ATTRIBUTE_DATA fs_info;
  if ((GetFileAttributesEx(fix_windows_encoding_problems(file_path),
                            GetFileExInfoStandard,
                            &fs_info))==errno)
  {
    return -1;
  }
  // Создать node и cохранить метаданные
  Node *current_node = new Node(file_path);
  fill_file_size(current_node,fs_info);
  
  // Добавить node к общему списку
  if (addinfo(current_node) < 0){
    return -1;
  }
  return 0;
}