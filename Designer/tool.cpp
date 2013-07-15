#include "tool.h"
#include <QEvent>
Tool::Tool()
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    QStringList list;
    list << "QPushButton" << "QLineEdit" << "QLabel";
    for(int i = 0;i<list.size() ; i ++){
        QRad *b = new QRad;
        b->setText(list[i]);
        lay->addWidget(b);
        connect(b,SIGNAL(checked1(QString)),this,SLOT(changetool(QString)));

    }
    lay->addStretch(1);
    this->setLayout(lay);
}
void Tool::changetool(QString tool){
    CurrentTool = tool;
}

QRad::QRad(QWidget *parent):
    QRadioButton(parent){

}

QRad::~QRad(){

}
void QRad::mousePressEvent(QMouseEvent *){
        this->setChecked(1);
        QString textt = this->text();
        emit checked1(textt);


}


