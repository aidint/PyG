#include "QPushButton1.h"

QPushButton1::QPushButton1(QWidget *parent) :
    QPushButton(parent)
{
    this->type1 = "QPushButton";
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ShowContextMenu(QPoint)));
    coder1 = new CodeEditor;
    connect(coder1,SIGNAL(closed()),this,SLOT(changecode()));
}

void QPushButton1::ShowContextMenu(const QPoint& pos) // this is a slot
{

    QPoint globalPos = this->mapToGlobal(pos);


    QMenu myMenu;
    myMenu.addAction("Remove");
    myMenu.addAction("Name");
    myMenu.addAction("Change Code");
    myMenu.addAction("Change Text");
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
        if(selectedItem->text() == "Change Text"){
            QString text = QInputDialog::getText(this,"Text","Enter your proper text:",QLineEdit::Normal,text1);
            this->setText(text);
            text1 = text;
            emit textchanged(text,this->name);
        }
    }

}

void QPushButton1::changecode(){
    code = coder1->code;
    emit codechanged(this->name,this->code);
}

void QPushButton1::hide1(){
    hide();
    emit hided(this->name + " " + this->type1);
}
