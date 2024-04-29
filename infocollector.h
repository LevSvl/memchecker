#pragma once
#include<iostream>



#define DIRID 1
#define FILEID 2

struct Node{
  int nodeid;
  std::string fpath;
  char* filetype;
  int nodeclass;
  unsigned long sz;

  Node(std::string);
};

struct Infocollector
{
  Node* node;
  Infocollector* next;

  Infocollector();
};

// defs 
//  processfile.cpp
int addinfo(Node* node);
//  scanrun.cpp
void showinfo();