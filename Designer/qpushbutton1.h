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
    QString name,code;
    CodeEditor *coder1;
signals:
    
public slots:
    void ShowContextMenu(const QPoint& pos);
    void changecode();
};

#endif // QPushButton1_H
