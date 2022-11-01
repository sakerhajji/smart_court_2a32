#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "affaire_juridique.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ajouter_clicked()
{
    /***********************************************************************************************************/
QString numcas=ui->NumCas->text() ;
QString cin=ui->Cin->text() ;
QString nom=ui->Nom->text();
QString prenom =ui->Prenom->text();
QString typecas=ui->TypeCas->text();
QString datecas=ui->DateCas->text();
QString dateness=ui->DateNass->text();
QString etat=ui->Etat->text();
QString sexe=ui->Sexe->text();
QString metier=ui->Metier->text();
QString nbenfant=ui->NbEnf->text();
affaire_juridique af ( numcas , cin, nom, prenom, typecas, datecas, dateness, etat, sexe, metier, nbenfant) ;
 bool test=af.ajouteraffaire();
 if(test)
 {
     QMessageBox::information(nullptr, QObject::tr("ok"),
                 QObject::tr("add successful.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}
 else
     QMessageBox::critical(nullptr, QObject::tr("not OK"),
                 QObject::tr("NO add.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

 /***********************************************************************************************************/

 ui->print_tab_2->setModel(Aff.afficher())  ;

}

void MainWindow::on_afficher_clicked()
{
    ui->print_tab->setModel(Aff.afficher()) ;

}

void MainWindow::on_supprimer_clicked()
{
    affaire_juridique aff1 ;
    aff1.Setnumcas(ui->NUMcas->text() ) ;

    bool test = aff1.supprimer_afffaire( aff1.Getnumcas() ) ;
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("delete successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

   }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("NO delete.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    ui->print_tab_3->setModel(Aff.afficher()) ;

}

void MainWindow::on_pushButton_13_clicked()
{
    affaire_juridique aff ;
    aff.Setnumcas(ui->numCasup->text()) ;
    aff.Setdatecas(ui->datecas->text()) ;
    bool test = aff.Update_afffaire(aff.Getdatecas(), aff.Getnumcas()) ;
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Update successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

   }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("NO Update.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    ui->print_tab_4->setModel(Aff.afficher()) ;


}
