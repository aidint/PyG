#include "compiler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication b(argc, argv);
    compiler w;
    QMessageBox a;
    a.setText("Created;");
    a.exec();
    w.close();
    return b.exec();
}
