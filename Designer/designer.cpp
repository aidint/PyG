#include "designer.h"

Designer::Designer(QWidget *parent)
    : QMainWindow(parent)
{
    area = new QMdiArea;
    setCentralWidget(area);
    menu1 = menuBar()->addMenu("&File");
    menu1->addAction("Save");
}

Designer::~Designer()
{
    
}
