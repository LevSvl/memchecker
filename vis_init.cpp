#include"infocollector.h"
#include"visimpl.h"

extern Infocollector* headcollector;

void vis_init()
{   
    Vis* abstractvisobj = new VisImp;
    abstractvisobj->vis_init();
}