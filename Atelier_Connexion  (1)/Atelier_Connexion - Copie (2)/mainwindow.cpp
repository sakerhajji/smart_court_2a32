#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"juge.h"
#include<QMessageBox>
#include<QIntValidator>

int a=1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_num->setValidator( new QIntValidator(1, 999, this));
    ui->tab_juge->setModel(j.afficher(a));
    ui->le_num_2->setValidator( new QIntValidator(1, 999, this));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString cin=ui->le_cin->text();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int num=ui->le_num->text().toInt();
    int nb=ui->le_nb->text().toInt();

    Juge j(cin,nom,prenom,num,nb);
    bool test=j.ajouter();
    QMessageBox msgbox;
    if(test)
    {msgbox.setText("echec d'ajout");
         ui->tab_juge->setModel((j.afficher(a)));}
    else
    {msgbox.setText("ajout avec succe");
        msgbox.exec();}

}

void MainWindow::on_bt_supprimer_clicked()
{
    Juge j1;
            QString c=ui->le_cin_supp->text();
    bool test=j1.supprimer(c);
    QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("supprimer avec succe");
        ui->tab_juge->setModel((j1.afficher(a)));}

    else
    msgbox.setText("echec de suppression");
        msgbox.exec();
}




void MainWindow::on_modiferbutton_clicked()
{
    QString cin=ui->le_cin_2->text();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom_2->text();
    int num=ui->le_num_2->text().toInt();
    int nb=ui->le_nb2->text().toInt();

    Juge m(cin,nom,prenom,num,nb);
    QMessageBox msgbox;
    if(m.chercher(cin)==true)

    {bool test=m.modifier();

    if(test==true)
    {msgbox.setText("modification avec succe");
         ui->tab_juge->setModel((m.afficher(a)));}
    else
    msgbox.setText("echec de modification");
        msgbox.exec();
    }
    else
        msgbox.setText("juge introuvable");
            msgbox.exec();


}

void MainWindow::on_radioButton_clicked()
{
    ui->tab_juge->setModel(j.sort_croissant());
}





void MainWindow::on_radioButton_2_clicked()
{
    ui->tab_juge->setModel(j.sort_decroissant());
}

void MainWindow::on_chercher_textChanged(const QString &arg1)
{
    ui->tab_juge->setModel(j.chercher2(arg1));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString s = ui->chercher->text() ;
    ui->tab_juge->setModel(j.chercher2(s));
}




