#ifndef QPushButton1_H
#define QPushButton1_H

#include <QPushButton>
#include <QWidget>
#include <QMenu>
#include <QMessageBox>
#include "codeeditor.h"


class QPushButton1 : public QPushButton
{
    Q_OBJECT

public:
    QPushButton1(QWidget *parent = 0);
    QString name,code,type = "QPushButton";
    CodeEditor *coder1;
    void hide1();
signals:
    void hided(QString);
public slots:
    void ShowContextMenu(const QPoint& pos);
    void changecode();
};

#endif // QPushButton1_H
