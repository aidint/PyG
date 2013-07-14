#ifndef DESIGNER_H
#define DESIGNER_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QMenuBar>
class Designer : public QMainWindow
{
    Q_OBJECT
    QMdiArea *area;
    QMenu *menu1;
public:
    Designer(QWidget *parent = 0);
    ~Designer();
};

#endif // DESIGNER_H
