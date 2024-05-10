#include"infocollector.h"
// Голова связного списка узлов
Infocollector* headcollector = new(Infocollector);

Infocollector::Infocollector()
{
  Infocollector::node = nullptr;
  Infocollector::next = nullptr;
}

Node::Node(std::string fpath)
{
  Node::fpath = fpath;
}

// Добавить узел в конец списка
int addinfo(Node* node)
{
  Infocollector *p = headcollector;
  for (;p->next; ){
    p = p->next;
  }

  if (p == headcollector && !headcollector->node){
    p->node = node;
    return 0;
  }

  Infocollector *pnew = new Infocollector;
  pnew->node = node;
  p->next = pnew;

  return 0;
}

// Вывести информацию о каждом узле в списке 
void showinfo()
{
  Infocollector *p = headcollector;
  while (p->next){
    Node *n = p->node;
    std::cout<< n->fpath << "  " << "bytes:  " << n->sz << std::endl; 
    p = p->next;
  }
}
