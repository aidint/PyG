#ifndef DESIGNER_H
#define DESIGNER_H
#include "pygapp.h"
#include "tool.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QMdiSubWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QtSql>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QProgressBar>
#include <QIcon>
class Designer : public QMainWindow
{
    Q_OBJECT
    QMdiArea *area;
    QMenu *menu1,*menu2;
    int x,y;
    int numbers;
    bool saved;
    QString pygdbfile;
    QString eodbfile;
public:
    Designer(QWidget *parent = 0);
    ~Designer();
    void createchild();
    Tool *tool;
    pygApp *app1;

public slots:
    void save();
    void compile();

};



#endif // DESIGNER_H
