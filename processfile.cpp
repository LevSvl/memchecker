#include <tchar.h>
#include<iostream>
#include<errno.h>
#include<fileapi.h>
#include<windows.h>
#include<string.h>
#include"infocollector.h"


void fill_file_size(Node* node,const WIN32_FILE_ATTRIBUTE_DATA& fs_info)
{  
  DWORD64 full_size = fs_info.nFileSizeHigh;
  // get upper 32 bits
  full_size = full_size << 32;
  // get lower 32 bits
  full_size |= fs_info.nFileSizeLow;
  // fill node info
  node->sz = full_size;
}

void 
fill_file_system_info(const WIN32_FILE_ATTRIBUTE_DATA& fs_info)
{
  ;
}

// resolves windows encoding problems
LPCWSTR 
fix_windows_encoding_problems(const std::string &string_ascii)
{

  std::string c_string(string_ascii.begin(),string_ascii.end()); 
  std::wstring w_string(c_string.begin(), c_string.end());

  LPCWSTR string_unicode = w_string.c_str();
  
  return string_unicode;
}

// Executes type, size, part of the full-size on disk
// stores it then inits the AI analyzing-process for file
// stores the result of analyze in ???...???
int processfile(const std::string &file_path)
{

  if (file_path.size() > MAX_PATH){
    return -1;
  }
  // Checks type and stores it as an input to AI   
  WIN32_FILE_ATTRIBUTE_DATA fs_info;
  if ((GetFileAttributesEx(fix_windows_encoding_problems(file_path),
                            GetFileExInfoStandard,
                            &fs_info))==errno)
  {
    return -1;
  }
  // creates Node for file and puts info into it
  Node *current_node = new Node(file_path);
  fill_file_size(current_node,fs_info);
  
  // add info to collector
  if (addinfo(current_node) < 0){
    return -1;
  }
  return 0;
}