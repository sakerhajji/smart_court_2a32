#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avocat.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include<QtDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   ui->le_id->setValidator(new QIntValidator(0, 99999999, this));
   ui->le_num_tel->setValidator(new QIntValidator(0, 999999999, this));
  ui->table_avocat->setModel(A.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_btn_ajouter_clicked()
{
    int Id_Avocat=ui->le_id->text().toInt();
    QString Nom=ui->le_nom->text();
    QString Prenom=ui->le_prenom->text();

     QString  Date_naissance=ui->la_date->text();
    int Numero_telephone=ui->le_num_tel->text().toInt();
     int Nombre_Proces_Gagnes=ui->le_proce->text().toInt();

    Avocat A( Id_Avocat ,Nom ,Prenom,Date_naissance,Numero_telephone, Nombre_Proces_Gagnes);


    bool test=A.ajouter();
    if(test)
    {

        ui->table_avocat->setModel(A.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("Ajout effectué \n"
                    "Click Cancel to exit ."),QMessageBox::Cancel );


      }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok "),
                       QObject::tr("Ajout non effectué .\n "
                                   "Click Cancel to exit. "), QMessageBox::Cancel );



    }


}

void MainWindow::on_btn_supprimer_clicked()
{
    Avocat A1 ;
    A1.setId_Avocat(ui->le_id_supp->text().toInt());
    bool test = A1.supprimer(A1.getId_Avocat() ) ;
    QMessageBox msgBox ;

    if (test)
         { ui->table_avocat->setModel(A.afficher());
        msgBox.setText("Suppression réussite");

    }

    else
        msgBox.setText("Suppression échouée ");
    msgBox.exec();
}

void MainWindow::on_btn_modifier_clicked()
{
int Id_Avocat = ui->id_modif->text().toInt() ;
QString Nom=ui->nom_2->text();
QString Prenom=ui->prenom_2->text();
QString  Date_naissance=ui->date_2->text();
int  Numero_telephone=ui->le_nv_num->text().toInt();
int Nombre_Proces_Gagnes=ui->le_nv_nbr->text().toInt();

Avocat A( Id_Avocat ,Nom ,Prenom,Date_naissance,Numero_telephone, Nombre_Proces_Gagnes);


QMessageBox msgBox ;


bool test= A.modifier ();
if(test)
{ ui->table_avocat->setModel(A.afficher());
             msgBox.setText("Modification  réussite");

}

else
      msgBox.setText("Modification  échouée ");
        msgBox.exec();

}
