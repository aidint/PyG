#ifndef PYGAPP_H
#define PYGAPP_H
#include "tool.h"
#include "qpushbutton1.h"
#include "qlineedit1.h"
#include "qlabel1.h"
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLineEdit>
#include <QMap>
#include <QPainter>
#include <QLineF>
#include <QPaintEngine>
class pygApp : public QWidget
{
    Q_OBJECT
    int names;
    int x,y;
public:
    pygApp();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void createobj(int a,int b);
    QMap<QString,QMap<QString,QWidget *> > objlist; //objlist["QPushButton"]["push1"] = pushbutton'
    QMap<QString,QString> codes; //code["push1"] = "self.setOpacity(0.8)"
    Tool *tool;
    QString code;
    CodeEditor *coder1;
public slots:
    void ShowContextMenu(const QPoint & pos);
    void changecode();
};

#endif // PYGAPP_H
