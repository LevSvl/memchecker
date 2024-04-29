#include<iostream>

extern int scanrun(const std::string&);

int 
main(int argc, char* argv[])
{
  if (argc < 2){
    return 1;
  }
  
  for (int i = 1; i < argc; i++){
    if (scanrun(argv[i]) < 0){
      return 1;
    }
  }
  return 0;
}