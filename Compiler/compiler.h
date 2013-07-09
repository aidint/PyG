#ifndef COMPILER_H
#define COMPILER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QtSql>
class compiler : public QMainWindow
{
    Q_OBJECT
private:
    QString eosFile;
    QString pygdbFile;
public:
    compiler(QWidget *parent = 0);
    compiler(QString eos,QString db,QString out,QWidget *parent = 0);
    ~compiler();
    void compile(QString Output);
    QString defaultobj(QString type,QString name);
    QStringList eodb(QString eos);
    QString code_proccess(QString code);

};

#endif // COMPILER_H
