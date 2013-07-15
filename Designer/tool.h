#ifndef TOOL_H
#define TOOL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QMessageBox>
class QRad : public QRadioButton
{
    Q_OBJECT
public:
    QRad(QWidget *parent = 0);
    ~QRad();
    void mousePressEvent(QMouseEvent *);
signals:
    void checked1(QString text1);
};


class Tool : public QWidget
{
    Q_OBJECT
public:
    Tool();
    QString CurrentTool;
signals:
    
public slots:
    void changetool(QString tool);
};

#endif // TOOL_H
