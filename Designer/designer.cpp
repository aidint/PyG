#include "designer.h"
#include "qdebug.h"
Designer::Designer(QWidget *parent)
    : QMainWindow(parent)
{
    numbers = 0;
    setWindowTitle("PyG Designer");
    area = new QMdiArea(this);
    setCentralWidget(area);
    menu1 = menuBar()->addMenu("&File");
    QAction *save = new QAction("&Save", this);
    connect(save,SIGNAL(triggered()),this,SLOT(save()));
    menu1->addAction(save);

    createchild();
    tool = new Tool;
    tool->setWindowTitle("Objects");
    QMdiSubWindow* subWindow = area->addSubWindow(tool);
    subWindow->setGeometry(0,0,190,this->height());
    app1->tool = tool;

}
Designer::~Designer()
{
    
}

void Designer::createchild(){
    app1 = new pygApp;
    QMdiSubWindow* subWindow = area->addSubWindow(app1);
    subWindow->resize(400,400);


}
