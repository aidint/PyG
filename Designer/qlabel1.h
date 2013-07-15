#ifndef QLabel1_H
#define QLabel1_H

#include <QLabel>
#include <QWidget>
#include <QMenu>
#include <QMessageBox>
#include "codeeditor.h"

class QLabel1 : public QLabel
{
    Q_OBJECT
public:
    QLabel1(QWidget *parent = 0);
    QString name,code;
    CodeEditor *coder1;
signals:

public slots:
    void ShowContextMenu(const QPoint& pos);
    void changecode();
};

#endif // QLabel1_H
