#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "QFontDatabase"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("windows");
    MainWindow w;

    QFile file(":/res/material-dark.qss");
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        a.setStyleSheet(styleSheet);
        file.close();
    }

    w.resize(1280,720);
    w.show();
    return a.exec();
}
