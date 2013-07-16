#include "pygapp.h"

pygApp::pygApp()
{
    title2 = "";
    names = 0;
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ShowContextMenu(QPoint)));
    coder1 = new CodeEditor;
    connect(coder1,SIGNAL(closed()),this,SLOT(changecode()));
}


void pygApp::mousePressEvent(QMouseEvent *event){

    int a,b;
    a = event->pos().x();
    b = event->pos().y();
    this->x = a;
    this->y = b;
}

void pygApp::mouseReleaseEvent(QMouseEvent *event){
    int a,b;
    a = event->pos().x();
    b = event->pos().y();
    createobj(a,b);
}


void pygApp::createobj(int a,int b){
    QString CurrentTool = tool->CurrentTool;
    if(a <= x && b >= y){
        x += a;
        a = x - a;
        x = x - a;
    }
    else if(a >= x && b <= y){
        y += b;
        b = y - b;
        y = y - b;
    }else if(a <= x && b <= y){
        x += a;
        a = x - a;
        x = x - a;
        y += b;
        b = y - b;
        y = y - b;
    }
    if(CurrentTool=="QPushButton"){
        QPushButton1 *c = new QPushButton1(this);
        c->setGeometry(x,y,abs(a-x),abs(b-y));
        c->show();
        c->name = "push" + QString::number(++names);
        c->setText(c->name);
        objlist["QPushButton"][c->name] = c;
        c->text1 = c->name;
        title[c->name] = c->name;
        connect(c,SIGNAL(hided(QString)),this,SLOT(removed(QString)));
        connect(c,SIGNAL(codechanged(QString,QString)),this,SLOT(changecodeobj(QString,QString)));
        connect(c,SIGNAL(textchanged(QString,QString)),this,SLOT(changetitleobj(QString,QString)));
    }
    if(CurrentTool=="QLineEdit"){
        QLineEdit1 *c = new QLineEdit1(this);
        c->setGeometry(x,y,abs(a-x),abs(b-y));
        c->show();
        c->name = "line" + QString::number(++names);
        objlist["QLineEdit"][c->name] = c;
        c->text1 = "";
        title[c->name] = "";
        connect(c,SIGNAL(hided(QString)),this,SLOT(removed(QString)));
        connect(c,SIGNAL(codechanged(QString,QString)),this,SLOT(changecodeobj(QString,QString)));
        connect(c,SIGNAL(textchanged(QString,QString)),this,SLOT(changetitleobj(QString,QString)));
    }
    if(CurrentTool=="QLabel"){
        QLabel1 *c = new QLabel1(this);
        c->setGeometry(x,y,abs(a-x),abs(b-y));
        c->show();
        c->name = "label" + QString::number(++names);
        c->text1 = c->name;
        c->setText(c->name);
        c->setFrameStyle(1);
        objlist["QLabel"][c->name] = c;
        title[c->name] = c->name;
        connect(c,SIGNAL(hided(QString)),this,SLOT(removed(QString)));
        connect(c,SIGNAL(codechanged(QString,QString)),this,SLOT(changecodeobj(QString,QString)));
        connect(c,SIGNAL(textchanged(QString,QString)),this,SLOT(changetitleobj(QString,QString)));
    }
}

void pygApp::ShowContextMenu(const QPoint& pos) // this is a slot
{

    QPoint globalPos = this->mapToGlobal(pos);


    QMenu myMenu;
    myMenu.addAction("Change Code");
    myMenu.addAction("Change Title");
    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        if(selectedItem->text() == "Change Code"){
            coder1->setWindowTitle("initUi()");
            coder1->setPlainText(code);
            coder1->show();
        }
        if(selectedItem->text() == "Change Title"){
            QString text = QInputDialog::getText(this,"Title","Enter your proper title:",QLineEdit::Normal,title2);
            this->setWindowTitle(text);
            title2 = text;
        }
}
}
void pygApp::changecode(){
    code = coder1->code;
}

void pygApp::removed(QString name){
    QStringList b = name.split(QRegExp("(\\ )"));

    objlist[b[1]].remove(b[0]);
}

void pygApp::changecodeobj(QString name,QString code){
    codes[name] = code;
}

void pygApp::changetitleobj(QString text,QString name){
    title[name] = text;
}

/**/
