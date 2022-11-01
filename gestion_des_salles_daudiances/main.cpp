#include "mainwindow.h"
#include<QMessageBox>
#include<QObject>
#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c; // une seul instance de la classe connection
    bool test=c.createconnection();//Etablir la connexion
    MainWindow w;

    if(test)//Si la connexion est établie
    {
     w.show();
     QMessageBox::information(nullptr, QObject::tr("data base is open"),
     QObject::tr("connexion successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else//Si la connexion a échoué
        QMessageBox::critical(nullptr, QObject::tr("data base is not open"),
        QObject::tr("connexion failed.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
