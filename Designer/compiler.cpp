#include "compiler.h"

compiler::compiler(QWidget *parent)
    : QMainWindow(parent)
{
    valid = true;
    QStringList pygdb = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("pygdb File (*.pygdb)"));
    if(pygdb.size() == 0) valid = false;
    QStringList eos = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("eodb File (*.eodb)"));
    if(eos.size() == 0) valid = false;
    if(valid){
    this->pygdbFile = pygdb[0];
    this->eosFile = eos[0];
    QString out = QInputDialog::getText(this,"Output","Output File name:");

    compile(out);
    }
    else{
        QMessageBox a;
        a.setText("No Compile can be completed, no file given");
        a.exec();
    }
}
compiler::compiler(QString eos,QString db,QString out,QWidget *parent)
    : QMainWindow(parent)
{
    this->eosFile = eos;
    this->pygdbFile = db;
    compile(out);
}

compiler::~compiler()
{

}

void compiler::compile(QString Output){
    QFile file1(Output);
    if(!file1.open(QFile::WriteOnly | QFile::Text)){
           QMessageBox a;
           a.setText(file1.errorString());
           a.exec();
           return;
    }
    QTextStream out(&file1);
    QFile base("default/default.dfp");

    if(!base.open(QFile::ReadOnly | QFile::Text)){
           QMessageBox a;
           a.setText("Error");
           a.exec();
           return;
    }
    QTextStream default1(&base);
    while (!default1.atEnd()) {
            QString line = default1.readLine();
            out << line << endl;
    }
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(this->pygdbFile);
    if(!db.open()){
        QMessageBox a;
        a.setText(db.lastError().text());
        a.exec();
    }

    QSqlQuery objects("SELECT * FROM objects;");
    while(objects.next()){
        QString result = defaultobj(objects.value(1).toString(),objects.value(2).toString());
        out << "        "+result<<endl;
    }
    //definition part completed
    QStringList proplist = eodb(this->eosFile);
    for(int i = 0;i<proplist.size();i++){
        out << "        " + proplist[i]<<endl;
    }

    QSqlDatabase external = QSqlDatabase::addDatabase("QSQLITE");
    external.setDatabaseName(this->pygdbFile);
    external.open();
    QSqlQuery exter("SELECT * FROM initcode");
    exter.next();

    QStringList handle23 = exter.value(0).toString().split(QRegExp("(\\\n)"));
    for(int i = 0;i < handle23.size();i++){
        handle23[i] = "        " + handle23[i];
    }
    foreach(QString i,handle23){
        out << i << endl;
    }

    //setting part completed

    QFile base2("default/defaultmid.dfp");

    if(!base2.open(QFile::ReadOnly | QFile::Text)){
           QMessageBox a;
           a.setText("Error");
           a.exec();
           return;
    }
    out << "        self.eventer()" << endl;
    QTextStream default2(&base2);
    while (!default2.atEnd()) {
            QString line = default2.readLine();
            out << line << endl;
    }
    //initUi() completed
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(this->pygdbFile);
    if(!db.open()){
        QMessageBox a;
        a.setText(db.lastError().text());
        a.exec();
    }
    QSqlQuery events("select * from code",db);
    QStringList eventer;
    while(events.next()){
        QString name = events.value(1).toString();
        QString event = events.value(2).toString();
        QString code = events.value(3).toString();
        QString handle;
        if(name!="self") handle = "self.";
        else handle = "";
        QRegExp rx("(\\[|\\])");
        out << "    def " + name + "_" + event.split(rx).at(0) + "(self,";
        QString function = name + "_" + event.split(rx).at(0);
        if(event.split(rx).size() > 1){
            QRegExp parax("(\\,)");
            QStringList para = event.split(rx).at(1).split(parax);
            for(int i = 1;i <= para.size();i++){
                out << para[i-1] << QString::number(i);
            }
        }
        out << "):" << endl;
        eventer << handle + name + "." + event + ".connect(self." + function + ")";


        QStringList codelist = code.split(QRegExp("(\\\n)"));
        for(int i=0;i<codelist.size();i++) out << "        " + code_proccess(codelist[i]) << endl;
    }
    out << "    def eventer(self):" << endl;
    for(int i = 0;i < eventer.size(); i++){
        out << "        " + eventer[i] << endl;
    }
    out << "        pass";
    //codes part completed
    QFile base3("default/defaultlast.dfp");

    if(!base3.open(QFile::ReadOnly | QFile::Text)){
           QMessageBox a;
           a.setText("Error");
           a.exec();
           return;
    }
    QTextStream default3(&base3);
    while (!default3.atEnd()) {
            QString line = default3.readLine();
            out << line << endl;
    }

}

QString compiler::defaultobj(QString type,QString name){
    QSqlDatabase d;
    d = QSqlDatabase::addDatabase("QSQLITE");
    d.setDatabaseName("defaultobj/"+type+".dodb");
    if(!d.open()){
        QMessageBox a;
        a.setText(d.lastError().text());
        a.exec();

    }

    QSqlQuery b("select code from def;");
    b.next();

    QString result = b.value(0).toString();
    QStringList c;
    c << result;
    c.replaceInStrings("%s","self."+name);
    d.close();
    return c[0];
}

QStringList compiler::eodb(QString eos){
    QStringList result;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(eos);
    if(!db.open()){
        QMessageBox a;
        a.setText(db.lastError().text());
        a.exec();
    }

    QSqlQuery t("SELECT name FROM sqlite_master WHERE type = 'table';",db);
    QStringList tables;
    while(t.next()){
        QString name = t.value(0).toString();
        tables << name;
    }
    db.close();
    QString v;
    for(int i=0;i<tables.size();i++){
        QString name = tables[i];
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(this->pygdbFile);
        db.open();
        QSqlQuery handleq("select type from objects where name = '" + name + "';",db);
        handleq.next();
        v = handleq.value(0).toString();
        if(name=="self"){
            v = "self";
        }
        db.close();


        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(eos);
        if(!db.open()){
            QMessageBox a;
            a.setText(db.lastError().text());
            a.exec();
        }

        QSqlQuery u("select * from "+name,db);


        while(u.next()){
            QString prop = u.value(0).toString();
            QString value = u.value(1).toString();


            QSqlDatabase handle = QSqlDatabase::addDatabase("QSQLITE");
            handle.setDatabaseName("defaultobj/"+v+".dodb");
            handle.open();
            QSqlQuery h("select code from prop where name = '" + prop + "';",handle);
            h.next();
            QString code = h.value(0).toString();
            handle.close();

            QStringList k;
            k << code;

            k.replaceInStrings("%s",value);

            if(v=="self")result << name + "." + k[0];
            else result << "self." + name + "." + k[0];
        }

    }


    return result;
}

QString compiler::code_proccess(QString code){
    return code;
}
