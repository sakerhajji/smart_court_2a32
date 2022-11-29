#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "affaire_juridique.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

{
        logintest = true ;
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).

     A.write_to_arduino("6");
}


}

MainWindow::~MainWindow()
{
    A.write_to_arduino("5");
    cout<<"good bay\n" ;

    delete ui;

}

void MainWindow::update_label()
{
    data=A.read_from_arduino();
    affaire_juridique Af ;


    if(data=="1")

        ui->label_3->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->label_3->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
    else if (data=="H")
    {ui->label_3->setText("Pushed");
    Af.Setnumcas(ui->comboBox_3->currentText() ) ;
    QString p = "reporter";
    Af.SetETAT_CAS(p)  ;
    Af.cryptage();
    QByteArray tmp ;
    bool test = Af.Update_cas() ;

  if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("Il y a quelque chose de dangereux le cas  reporter.\n"
                                "Click Cancel pour sorti."), QMessageBox::Cancel);
        A.write_to_arduino("4");
        Af.cryptage();
        p=Af.Getnumcas();
        tmp=p.toUtf8();
        A.write_to_arduino(tmp);




   }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("NO delete.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::on_Ajouter_clicked()//add
{


/***********************************************************************************************************/
    if (!logintest){
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
af.cryptage();
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

 ui->print_tab_2->setModel(Aff.afficher())  ;}

}

void MainWindow::on_afficher_clicked()//print
{
    if (!logintest)ui->print_tab->setModel(Aff.afficher()) ;

}

void MainWindow::on_supprimer_clicked()//delete
{
    if (!logintest){
    affaire_juridique aff1 ;
    aff1.Setnumcas(ui->NUMcas->text() ) ;
    aff1.cryptage();

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

}



void MainWindow::on_Update_clicked()//update
{
    if (!logintest){
/***********************************************************************************************************/
QString numcas=ui->NumCas_2->text() ;
QString cin=ui->Cin_2->text() ;
QString nom=ui->Nom_2->text();
QString prenom =ui->Prenom_2->text();
QString typecas=ui->TypeCas_2->text();
QString datecas=ui->DateCas_2->text();
QString dateness=ui->DateNass_2->text();
QString etat=ui->Etat_2->text();
QString sexe=ui->Sexe_2->text();
QString metier=ui->Metier_2->text();
QString nbenfant=ui->NbEnf_2->text();
affaire_juridique af ( numcas , cin, nom, prenom, typecas, datecas, dateness, etat, sexe, metier, nbenfant) ;
af.cryptage();
 bool test=af.Update_afffaire();
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
 QSqlQueryModel * modal=new QSqlQueryModel() ;
 QSqlQuery  qry ;
 qry.prepare("SELECT REVERSE (NUMCAS) FROM AFFAIRE_JURIDIQUE ") ;
 qry.exec() ;
 modal->setQuery(qry) ;
 ui->comboBox_2->setModel(modal) ;

 /***********************************************************************************************************/

 ui->print_tab_4->setModel(Aff.afficher())  ;
}


}

void MainWindow::on_pushButton_3_clicked()//search
{
    if (!logintest)
    {QString s = ui->chercher->text() ;
        reverse(s.begin(),s.end()) ;
    ui->print_tab->setModel(Aff.chercher(s)) ;}

}

void MainWindow::on_pushButton_clicked()//sort
{
    if (!logintest){
   QString b = (ui->croissant->isChecked() )?"ASC":"DESC" ;
   QString a = ui->comboBox->currentText() ;
   string str= a.toStdString();
       if (str=="Numero de cas") a="NUMCAS" ;
       if (str=="Cin") a="CIN" ;
       if (str=="Nom") a="NOM" ;
       if (str=="Prenom") a="NOM" ;
       if (str=="Type cas") a="NOM" ;
       if (str=="Date Cas") a="NOM" ;
       if (str=="Date de naissance") a="NOM" ;
       if (str=="Etat") a="NOM" ;
       if (str=="Metier") a="NOM" ;
       if (str=="sexe") a="NOM" ;
       if (str=="Nobre d'enfants") a="NOM" ;
       ui->print_tab->setModel(Aff.sortname(a,b) ) ;}
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)//update box
{
    QString s= arg1 ;
   if (!logintest)
    //QString numcas=ui->comboBox_2->currentText() ;

   reverse(s.begin(),s.end()) ;
   { QSqlQuery qry ;
    qry.prepare("SELECT REVERSE (NUMCAS),REVERSE(CIN),REVERSE (NOM),REVERSE (PRENOM),REVERSE(TYPECAS),REVERSE(DATECAS),REVERSE(DATENESS)"
                ",REVERSE(ETAT_CAS),REVERSE(SEXE),REVERSE(METIER),REVERSE(NBENFANT)FROM AFFAIRE_JURIDIQUE WHERE NUMCAS ="+s+"") ;
    QString numcas ;
    if (qry.exec() )
    {

        while (qry.next())
        {
             ui->NumCas_2->setText(qry.value(0).toString()) ;

             ui->Cin_2->setText(qry.value(1).toString()) ;
             ui->Nom_2->setText(qry.value(2).toString());
             ui->Prenom_2->setText(qry.value(3).toString());
             ui->TypeCas_2->setText(qry.value(4).toString());
             ui->DateCas_2->setText(qry.value(5).toString());
             ui->DateNass_2->setText(qry.value(6).toString());
             ui->Etat_2->setText(qry.value(7).toString());
             ui->Sexe_2->setText(qry.value(8).toString());
             ui->Metier_2->setText(qry.value(9).toString());
             ui->NbEnf_2->setText(qry.value(10).toString());
        }
    }
   }
    }

void MainWindow::on_chercher_textChanged(const QString &arg1)
{
   if (!logintest) ui->print_tab->setModel(Aff.chercher(arg1)) ;
}

void MainWindow::on_browseBtn_clicked()
{
    if (!logintest)
    {

    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );}


}

void MainWindow::on_sendBtn_clicked()
{

   if (!logintest) {Smtp* smtp = new Smtp("saker.hajji@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");

    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("saker.hajji@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("saker.hajji@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());}


}
void   MainWindow::mailSent(QString status)
{
if (!logintest)
{if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();}
}
void MainWindow :: on_pushButton_4_clicked()
{
    if (!logintest)
    {
    QString strStream;
                   QTextStream out(&strStream);
                   const int rowCount = ui->print_tab->model()->rowCount();
                   const int columnCount =ui->print_tab->model()->columnCount();


                   out <<  "<html>\n"
                           "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg("eleve")
                           <<  "</head>\n"
                           "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                               " <h1> votre cas en pdf </h1> <hr>"

                               "<table border=0 cellspacing=0 cellpadding=2>\n";

                   // headers
                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->print_tab->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->print_tab->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";
                       // data table
                          for (int row = 0; row < rowCount; row++) {
                              out << "<tr>";
                              for (int column = 0; column < columnCount; column++) {
                                  if (!ui->print_tab->isColumnHidden(column)) {
                                      QString data = ui->print_tab->model()->data(ui->print_tab->model()->index(row, column)).toString().simplified();
                                      out << QString("<td bkcolor=2>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                  }
                              }
                              out << "</tr>\n";
                          }
                          out <<  "</table>\n"
                              "</body>\n"
                              "</html>\n";



           QTextDocument *document = new QTextDocument();
           document->setHtml(strStream);


           //QTextDocument document;
           //document.setHtml(html);
           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setOutputFileName("saker.pdf");
           document->print(&printer); }
}




void MainWindow::on_login_clicked()
{
    cout<<logintest<<endl ;
    QString id =ui->id->text(),password=ui->password->text() ;
    logintest =  (id=="admin"&&password=="admin")? false : true ;
    cout<<logintest<<endl;
    if (!logintest)
    {
        A.write_to_arduino("3");
        ui->print_tab_4->setModel(Aff.afficher())  ;
        ui->print_tab_3->setModel(Aff.afficher()) ;
        ui->print_tab_2->setModel(Aff.afficher()) ;
        ui->print_tab->setModel(Aff.afficher()) ;
        ui->print_tab_5->setModel(Aff.afficher()) ;

        QSqlQueryModel * modal=new QSqlQueryModel() ;
        QSqlQuery  qry ;
        qry.prepare("SELECT REVERSE (NUMCAS) FROM AFFAIRE_JURIDIQUE ") ;
        qry.exec() ;
        modal->setQuery(qry) ;
        ui->comboBox_2->setModel(modal) ;
        ui->comboBox_3->setModel(modal) ;
        QMessageBox::information(nullptr, QObject::tr("ok"),
                         QObject::tr("login successful.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else
         QMessageBox::critical(nullptr, QObject::tr("not OK"),
                     QObject::tr("verifier votre id ou motde pass svp .\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_ON_clicked()
{
   A.write_to_arduino("1"); //envoyer 1 à arduino
}

void MainWindow::on_OFF_clicked()
{
   A.write_to_arduino("0");  //envoyer 0 à arduino
}


