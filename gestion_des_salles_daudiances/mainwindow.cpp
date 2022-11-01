#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "salleaudience.h"
#include "connection.h"
#include<QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QIntValidator>
#include <QTabWidget>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableS->setModel(p.affichage());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit->text().toInt();
    int nbplace=ui->lineEdit_2->text().toInt();
    int camenmarche=ui->lineEdit_3->text().toInt();
    QString dispo=ui->lineEdit_4->text();

    salleaudience s(id,nbplace,camenmarche,dispo);

    bool test=s.ajout();
    if(test)
    {
           ui->tableS->setModel(s.affichage());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Ajout effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_pushButton_supprimer_clicked()
{
    int id=ui->lineEdit_5->text().toInt();
       bool test=p.suppression(id);
       if(test)
       {
           ui->tableS->setModel(p.affichage());
           QMessageBox::information(nullptr, QObject::tr("Ok"),
           QObject::tr("Suppression effectuée. \n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
        }
       else

           QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
           QObject::tr("Suppression non effectuée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_update_clicked()
{
    int id=ui->id->text().toInt();
    int nbplace=ui->nb->text().toInt();
    int camenmarche=ui->c->text().toInt();
    QString dispo=ui->dis->text();
        salleaudience p2(id,nbplace,camenmarche,dispo);

        bool test=p2.modification(id,nbplace,camenmarche,dispo);
        if(test)
        {
            //actualiser pour l'affichage
            ui->tableS->setModel(p2.affichage());
                    QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}


