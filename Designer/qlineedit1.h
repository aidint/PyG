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
    QString name,code,type = "QLineEdit";
    CodeEditor *coder1;
    void hide1();
signals:
    void hided(QString);
public slots:
    void ShowContextMenu(const QPoint& pos);
    void changecode();
};

#endif // QLINEEDIT1_H
