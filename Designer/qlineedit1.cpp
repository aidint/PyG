#include "qlineedit1.h"

QLineEdit1::QLineEdit1(QWidget *parent) :
    QLineEdit(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ShowContextMenu(QPoint)));
    coder1 = new CodeEditor;
    connect(coder1,SIGNAL(closed()),this,SLOT(changecode()));
    this->setReadOnly(1);
}

void QLineEdit1::ShowContextMenu(const QPoint& pos) // this is a slot
{

    QPoint globalPos = this->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction("Remove");
    myMenu.addAction("Name");
    myMenu.addAction("Change Code");
    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        if(selectedItem->text() == "Remove"){
            this->hide1();
        }
        if(selectedItem->text() == "Name"){
            QMessageBox v;
            v.setText(this->name);
            v.exec();
        }
        if(selectedItem->text() == "Change Code"){
            coder1->setWindowTitle(this->name + ".clicked()");
            coder1->setPlainText(code);
            coder1->show();

        }
    }

}

void QLineEdit1::changecode(){
    code = coder1->code;
}


void QLineEdit1::hide1(){
    hide();
    emit hided(this->name);
}
