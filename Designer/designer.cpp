#include "designer.h"
#include "qdebug.h"
#include "compiler.h"
Designer::Designer(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowIcon(QIcon("main.ico"));

    saved = false;
    this->resize(600,544);
    numbers = 0;
    setWindowTitle("PyG Designer");
    area = new QMdiArea(this);
    setCentralWidget(area);




    menu1 = menuBar()->addMenu("&File");
    menu2 = menuBar()->addMenu("&Compile");
    QAction *save = new QAction("&Save", this);
    QAction *Compile = new QAction("&Compile", this);
    QAction *exit = new QAction("&Exit",this);
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));
    connect(save,SIGNAL(triggered()),this,SLOT(save()));
    connect(Compile,SIGNAL(triggered()),this,SLOT(compile()));
    menu1->addAction(save);
    menu1->addAction(exit);
    menu2->addAction(Compile);






    createchild();
    tool = new Tool;
    tool->setWindowTitle("Objects");
    QMdiSubWindow* subWindow = area->addSubWindow(tool);
    subWindow->setGeometry(0,0,190,520);
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

void Designer::save(){
    QProgressBar *prog = new QProgressBar(this);
    prog->setValue(0);
    prog->setTextVisible(0);
    prog->setGeometry(this->width()-150,this->height()-15,150,15);
    prog->setMaximum(100);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "Untitled.pygpro",
                               tr("PyG Project (*.pygpro)"));
    QString name = fileName.split(QRegExp("(\\.)")).at(0);
    QFile b(fileName);
    if(!b.open(QFile::WriteOnly | QFile::Text)){
           QMessageBox a;
           a.setText(b.errorString());
           a.exec();
           return;
    }
    QTextStream out(&b);
    out << name << ".pygdb" << endl << name << ".eodb";
    QSqlDatabase a1 = QSqlDatabase::addDatabase("QSQLITE");
    a1.setDatabaseName(name+".pygdb");
    a1.open();

    ///////pygdb
    prog->show();
    QSqlQuery createtable("CREATE TABLE objects(ID NUMERIC,type TEXT,name TEXT);",a1);
    createtable.exec("CREATE TABLE code (ID NUMERIC,name TEXT,event TEXT,code TEXT);");
    createtable.exec("CREATE TABLE initcode (code TEXT);");
    QMap<QString,QMap<QString,QWidget *> > k = app1->objlist;

    QList<QString> listofkeys = k.keys();
    int count = 0;
    foreach(QString s,listofkeys){
        QList<QString> t = k[s].keys();
        foreach(QString j,t){
            count++;
            createtable.exec("INSERT INTO objects VALUES(" + QString::number(count) +",'" + s +"','"+j+"');");
        }
    }
    prog->setValue(20);
    QMap<QString,QString> c = app1->codes;
    count = 0;
    foreach(QString name,c.keys()){
        count++;
        QString handle = c[name];
        if (c[name] == "") handle = "pass";
        createtable.exec("INSERT INTO code VALUES("+QString::number(count)+",'"+name
                         +"','clicked','"+c[name]+"');");
    }
    createtable.exec("INSERT INTO initcode VALUES('"+app1->code+"');");
    a1.close();
    prog->setValue(40);
    ///////eodb
    QSqlDatabase a2 = QSqlDatabase::addDatabase("QSQLITE");
    a2.setDatabaseName(name+".eodb");
    a2.open();

    QSqlQuery createit(a2);
    foreach(QString s,listofkeys){//s = "QPushButton","QLineEdit",....
        QList<QString> t = k[s].keys();
        foreach(QString j,t){//j = "push1","line2","line3",...
            createit.exec("CREATE TABLE " + j + " (property TEXT,value TEXT);");
            //size:
            int h = app1->objlist[s][j]->size().height();
            int w = app1->objlist[s][j]->size().width();
            createit.exec("INSERT INTO " + j + " VALUES('size','"+QString::number(w)+","+QString::number(h)+"');");
            //place:
            int x = app1->objlist[s][j]->x();
            int y = app1->objlist[s][j]->y();
            createit.exec("INSERT INTO " + j + " VALUES('place','"+QString::number(x)+","+QString::number(y)+"');");
            //text:
            createit.exec("INSERT INTO " + j + " VALUES('text','\""+app1->title[j]+"\"');");
        }
    }
    prog->setValue(90);
    createit.exec("CREATE TABLE self (property TEXT,value TEXT);");
    int h = app1->size().height();
    int w = app1->size().width();
    createit.exec("INSERT INTO self VALUES('size','"+QString::number(w)+","+QString::number(h)+"');");
    createit.exec("INSERT INTO self VALUES('title','\""+app1->title2+"\"');");

    saved = true;
    pygdbfile = name + ".pygdb";
    eodbfile = name + ".eodb";
    prog->setValue(100);
    prog->close();
}

void Designer::compile(){
    if(!saved){
        QMessageBox a;
        a.setText("Save the project first");
        a.exec();
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "Untitled.py",
                               tr("Python Executive (*.py)"));
    compiler c(this->eodbfile,this->pygdbfile,fileName);
    c.show();

}
