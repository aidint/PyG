#ifndef QLINEEDIT1_H
#define QLINEEDIT1_H

#include <QLineEdit>
#include <QWidget>
#include <QMenu>
#include <QMessageBox>
#include "codeeditor.h"

class QLineEdit1 : public QLineEdit
{
    Q_OBJECT
public:
    QLineEdit1(QWidget *parent = 0);
    QString name,code,type1,text1;
    CodeEditor *coder1;
    void hide1();
signals:
    void hided(QString);
    void codechanged(QString,QString);
    void textchanged(QString,QString);
public slots:
    void ShowContextMenu(const QPoint& pos);
    void changecode();
};

#endif // QLINEEDIT1_H
