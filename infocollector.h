#pragma once
#include<iostream>

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
