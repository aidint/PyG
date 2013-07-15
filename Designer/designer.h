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
class Designer : public QMainWindow
{
    Q_OBJECT
    QMdiArea *area;
    QMenu *menu1;
    int x,y;
    int numbers;
public:
    Designer(QWidget *parent = 0);
    ~Designer();
    void createchild();
    Tool *tool;
    pygApp *app1;

public slots:
    void save(){
        QMessageBox
    }

};



#endif // DESIGNER_H
