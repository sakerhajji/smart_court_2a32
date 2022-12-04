#include "mainwindow.h"
#include "ui_mainwindow.h"
int a=1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /**************************************saker**********************************************************************/
    int ret=Ar.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< Ar.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<Ar.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(Ar.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
    Ar.write_to_arduino("6");
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
    ui->UpdateBox->setModel(modal) ;
    ui->ardouinoBox->setModel(modal) ;
    /********************************************************eya****************************************************/
    ui->le_id->setValidator(new QIntValidator(0, 999999999, this));
    ui->le_num_tel->setValidator(new QIntValidator(0, 999999999, this));
    ui->table_avocat_2->setModel(A.afficherA());
    ui->table_avocat->setModel(A.afficherA());
    //ui->table_pres->setModel((A.afficherA_arduino()));

    int ret_1 =aav.connect_arduino(); // lancer la connexion à arduino
       switch(ret_1){
       case(0):qDebug()<< "arduino is available and connected to : "<< aav.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<aav.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(aav.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
    /********************************************************eya****************************************************/
        ui->le_num->setValidator( new QIntValidator(1, 999, this));
        ui->tab_juge->setModel(j.afficher(a));
        ui->tab_juge1->setModel(j.afficher(a));
        ui->tab_juge2->setModel(j.afficher(a));
        ui->tab_juge3->setModel(j.afficher(a));
        ui->le_num_2->setValidator( new QIntValidator(1, 999, this));
        /********************************************************aziz****************************************************/
        ui->tableS->setModel(p.affichage());
           ui->lineEdit->setValidator(new QIntValidator(1,999999, this));
           ui->lineEdit_2->setValidator(new QIntValidator(1,999999, this));
           ui->lineEdit_3->setValidator(new QIntValidator(1,999999, this));
           ui->lineEdit_5->setValidator(new QIntValidator(1,999999, this));
           QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                                  QCoreApplication::organizationName(), QCoreApplication::applicationName());

               ui->Map->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
        /********************************************************aziz****************************************************/

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**************************************saker**********************************************************************/

void MainWindow::on_login_clicked()
{
    QString username = ui->user->text() ,u;
    QString password =ui->pwd->text(),p;

    QSqlQuery query;
       if (query.exec("SELECT PRENOM , CIN_P , ROLE FROM PERSONNEL WHERE PRENOM =\'" + username + "\'AND CIN_P="+password+" "))
      { if  (query.next())
            {
               QMessageBox::information(nullptr, QObject::tr("ok"),
                                QObject::tr("login successful.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
           QString role = query.value(2).toString();
            qDebug() << role ;
            if (role == "AJ")
            ui->stackedWidget->setCurrentIndex(1);
            else if (role=="GV")
                ui->stackedWidget->setCurrentIndex(2);
            else if (role=="GG")
                ui->stackedWidget->setCurrentIndex(3);
            else if (role=="GS")
                ui->stackedWidget->setCurrentIndex(4);


           }

          else
           {
               QMessageBox::critical(nullptr, QObject::tr("not OK"),
                           QObject::tr("verifier votre id ou motde pass svp .\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
           }

       }

}
void MainWindow::update_label()
{
    /**************************************saker**********************************************************************/
    data=Ar.read_from_arduino();
    affaire_juridique Af ;


    if(data=="1")

        ui->label_3->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->label_3->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
    else if (data=="H")
    {ui->label_3->setText("Pushed");
    Af.Setnumcas(ui->ardouinoBox->currentText() ) ;
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
        Ar.write_to_arduino("4");
        Af.cryptage();
        p=Af.Getnumcas();
        tmp=p.toUtf8();
        Ar.write_to_arduino(tmp);




   }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("NO delete.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    ui->print_tab_4->setModel(Aff.afficher())  ;
    ui->print_tab_3->setModel(Aff.afficher()) ;
    ui->print_tab_2->setModel(Aff.afficher()) ;
    ui->print_tab->setModel(Aff.afficher()) ;
    ui->print_tab_5->setModel(Aff.afficher()) ;
    /**************************************saker**********************************************************************/

    dataaAV=aav.read_from_arduino();

    if(dataaAV=="v")

    {
        ui->label_access->setText("Porte ouverte , access désormais autorisé  ! "); // si les données reçues de arduino via la liaison série sont égales à 1
        // alors afficher ce qui est écrit
        // ui->table_pres->setModel((A.afficherA_arduino()));
    }


    else if (dataaAV=="n")

    {
        ui->label_access->setText("Attention ! Code erroné !");    // si les données reçues de arduino via la liaison série sont égales à 0
    }
    //alors afficher ce qui est écrit

    else if (dataaAV =="s")
        ui->label_access->setText("L'avocat a dépassé les tentatives d'essais autorisées !  ");
    /*************************************************yesmine*****************************************************/
    QString message , numcas=ui->chercher_2->text();
      reverse(numcas.begin(), numcas.end());
      QSqlQuery query;
            if (query.exec("SELECT REVERSE(PRENOM),REVERSE(NOM) FROM AFFAIRE_JURIDIQUE WHERE numcas= '"+numcas+"\'"))
                   message="Nom : " +query.value(1).toString()+" prenom : " +query.value(0).toString();
                     string s = message.toStdString();
                     const char* p = s.c_str();
      if(data=="z")

        {ui->affiche->setText("debut de stresse ");
     msystemtryicon->showMessage(tr(p),tr("debut de stresse  "));}

      else if (data=="x")

      {ui->affiche->setText("detection en cours ");
       msystemtryicon->showMessage(tr(p),tr("entrain de mantir "));}
      else   if(data=="y")
          msystemtryicon->showMessage(tr(p),tr("debut de detection  "));
     /*************************************************yesmine*****************************************************/
}

void MainWindow::on_Ajouter_clicked()//add
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

 ui->print_tab_2->setModel(Aff.afficher())  ;
 ui->print_tab_4->setModel(Aff.afficher())  ;
 ui->print_tab_3->setModel(Aff.afficher()) ;
 ui->print_tab_2->setModel(Aff.afficher()) ;
 ui->print_tab->setModel(Aff.afficher()) ;
 ui->print_tab_5->setModel(Aff.afficher()) ;



}

void MainWindow::on_afficher_clicked()//print
{
    ui->print_tab->setModel(Aff.afficher()) ;

}

void MainWindow::on_supprimer_clicked()//delete
{

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



void MainWindow::on_Update_clicked()//update
{

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
 ui->UpdateBox->setModel(modal) ;

 /***********************************************************************************************************/

 ui->print_tab_4->setModel(Aff.afficher())  ;



}

void MainWindow::on_search_clicked()//search
{
   QString s = ui->chercher->text() ;
        reverse(s.begin(),s.end()) ;
    ui->print_tab->setModel(Aff.chercher(s)) ;

}

void MainWindow::on_Sort_af_clicked()//sort
{

   QString b = (ui->croissant->isChecked() )?"ASC":"DESC" ;
   QString a = ui->sortBox->currentText() ;
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
       ui->print_tab->setModel(Aff.sortname(a,b) ) ;
}

void MainWindow::on_UpdateBox_currentIndexChanged(const QString &arg1)//update box
{
    QString s= arg1 ;


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
   ui->print_tab->setModel(Aff.chercher(arg1)) ;
}

void MainWindow::on_browseBtn_clicked()
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

    ui->file->setText( fileListString );


}

void MainWindow::on_sendBtn_clicked()
{

  Smtp* smtp = new Smtp("saker.hajji@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");

    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("saker.hajji@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("saker.hajji@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());


}
void   MainWindow::mailSent(QString status)
{

if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
void MainWindow :: on_PDF_clicked()
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
           document->print(&printer);
    cout<<"pdf"<<endl ;
}
 void MainWindow::on_ON_clicked()
{
   Ar.write_to_arduino("1"); //envoyer 1 à arduino
}

void MainWindow::on_OFF_clicked()
{
   Ar.write_to_arduino("0");  //envoyer 0 à arduino
}

/***************************************************************eya**************************************************************/
void MainWindow::on_btn_ajouter_clicked()
{
    int Id_Avocat=ui->le_id->text().toInt();
    QString Nom=ui->le_nomA->text();
    QString Prenom=ui->le_prenomA->text();

    QString  Date_naissance=ui->la_date->text();
    int Numero_telephone=ui->le_num_tel->text().toInt();
    int Nombre_Proces_Gagnes=ui->le_proce->text().toInt();

    Avocat A( Id_Avocat,Nom,Prenom,Date_naissance,Numero_telephone,Nombre_Proces_Gagnes );


    bool test=A.ajouterA();
    if(test)
    {

        ui->table_avocat_2->setModel(A.afficherA());
        ui->table_avocat->setModel(A.afficherA());

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
    int id=ui->le_id_supp->text().toInt();
    bool test = A.supprimerA(id) ;
    QMessageBox msgBox ;

    if (test)
    {
        ui->table_avocat->setModel(A.afficherA());
        ui->table_avocat_2->setModel(A.afficherA());

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

    Avocat A1( Id_Avocat,Nom,Prenom,Date_naissance,Numero_telephone, Nombre_Proces_Gagnes);


    QMessageBox msgBox ;


    bool test= A1.modifierA();
    if(test)
    {
        ui->table_avocat->setModel(A1.afficherA());
        ui->table_avocat_2->setModel(A1.afficherA());


        msgBox.setText("Modification  réussite");

    }

    else
        msgBox.setText("Modification  échouée ");
    msgBox.exec();

}


void MainWindow::on_btn_trouver_clicked()
{


    QString a = ui->Achercher->text();

    ui->table_rechercher->setModel(A.chercherA(a));
}





void MainWindow::on_Achercher_textChanged(const QString &arg1)
{

    ui->table_rechercher->setModel(A.chercherA(arg1));

}



void MainWindow::on_btn_tri_clicked()
{

    QString b = (ui->radioB_croiss->isChecked())?"ASC":"DESC" ;

    int x = ui->comboBoxEYA->currentIndex() ;
    QString a ;
    switch (x)
    {
    case 0 :
        a="NOMBRE_PROCES_GAGNES";
        break ;
    case 1 :
        a="ID_AVOCAT";
        break ;
    case 2 :
        a="NOM";
        break ;

    }
    ui->table_avocat->setModel(A.sort(a,b));
}





void MainWindow::on_pdf_AV_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->table_rechercher->model()->rowCount();
    const int columnCount =ui->table_rechercher->model()->columnCount();


    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("eleve")
        <<  "</head>\n"
        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
        "<h1>Gestion des Avocats</h1>"

        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->table_rechercher->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->table_rechercher->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->table_rechercher->isColumnHidden(column))
            {
                QString data = ui->table_rechercher->model()->data(ui->table_rechercher->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
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
    printer.setOutputFileName("eyaValidation.pdf");
    document->print(&printer);
}

void MainWindow::on_sendBtnAV_clicked()
{

    Smtp* smtp = new Smtp("eya.gadhoumi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("eya.gadhoumi@esprit.tn", ui->rcpt->text(), ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("eya.gadhoumi@esprit.tn", ui->rcpt->text(), ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::on_browseBtnAV_clicked()
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

    ui->file->setText( fileListString );

}

void MainWindow::on_btn_evaluer_clicked()
{
    int x = ui->evaluation->currentIndex();
    switch (x)
    {
    case 0 :
        ui->tab_evaluer->setModel(A.evaluerD());
        break ;
    case 1 :
        ui->tab_evaluer->setModel(A.evaluerM());
        break ;
    case 2 :
        ui->tab_evaluer->setModel(A.evaluerE());
        break ;
    }
}

void MainWindow::BarChartAV()
{
    QSqlQuery q1, q2, q3, q4 ;
    qreal tot=0,c1=0,c2=0, c3= 0;

    q1.prepare("SELECT * FROM AVOCAT");
    q1.exec();

    q2.prepare("SELECT * FROM AVOCAT WHERE NOMBRE_PROCES_GAGNES <=  10 ");
    q2.exec();

    q3.prepare("SELECT * FROM AVOCAT WHERE NOMBRE_PROCES_GAGNES > 10 And NOMBRE_PROCES_GAGNES <= 15 ");
    q3.exec();

    q4.prepare("SELECT * FROM AVOCAT WHERE NOMBRE_PROCES_GAGNES > 15  ");
    q4.exec();

    while (q1.next())
    {
        tot++;
    }
    while (q2.next())
    {
        c1++;
    }
    while (q3.next())
    {
        c2++;
    }
    while (q4.next())
    {
        c3++;
    }




    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;


    QString c1S=QString::number(c1*100);
    QString c2S=QString::number(c2*100);
    QString c3S=QString::number(c3*100);



// Assign names to the set of bars used
    QBarSet *set0 = new QBarSet("Debutant "+c1S+"%");
    QBarSet *set1 = new QBarSet("Moyen "+c2S+"%");
    QBarSet *set2 = new QBarSet("Expert "+c3S+"%");


    // Assign values for each bar
    *set0 << c1;
    *set1 << c2;
    *set2 << c3;




    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    series->append(set0);
    series->append(set1);
    series->append(set2);



    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();

    chart->createDefaultAxes();
    chart->setTitle("Evaluation des Avocats selon le nombre de proces gagnés ");

    // 1. Bar chart
    chart->setAxisX(axis, series);

    // Used to change the palette
    QPalette pal = qApp->palette();

    // Change the color around the chart widget and text
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));

    // Apply palette changes to the application
    qApp->setPalette(pal);


// Used to display the chart
    chartView = new QChartView(chart,ui->avocat_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);

    chartView->show();
}


void MainWindow::on_btn_executer_clicked()
{
    BarChartAV();
}

void MainWindow::on_ajouter_conge_clicked()
{
    int Id_Avocat=ui->id_conge->text().toInt();
    QString Date_Debut =ui->date_debut->text();
    QString Date_Fin =ui->date_fin->text();
    QString  Motif=ui->motif->text();
    conge c (Id_Avocat, Date_Debut, Date_Fin, Motif );


    bool test=c.ajouter_c();
    if(test)
    {

        ui->tab_avocat_conge->setModel(c.afficher_c());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Congé Attribué avec succes \n"
                                             "Click Cancel to exit ."),QMessageBox::Cancel );

    }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok "),
                              QObject::tr("Impossible d'attribuer un Congé  .\n "
                                          "Click Cancel to exit. "), QMessageBox::Cancel );

    }


}
/*****************************************************yasmine***************************************************************************/
void MainWindow::on_yas_ajouter_clicked()
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
    {
        msgbox.setText("echec d'ajout");
        ui->tab_juge1->setModel((j.afficher(a)));
        ui->tab_juge->setModel((j.afficher(a)));
        ui->tab_juge2->setModel((j.afficher(a)));
        ui->tab_juge3->setModel((j.afficher(a)));
    }
    else
    {
        msgbox.setText("ajout avec succe");
        msgbox.exec();
    }

}

void MainWindow::on_yas_supprimer_clicked()
{
    QString c=ui->le_cin_supp->text();
    bool test=j.supprimer(c);
    QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("supprimer avec succe");
        ui->tab_juge3->setModel((j.afficher(a)));
        ui->tab_juge2->setModel((j.afficher(a)));
        ui->tab_juge1->setModel((j.afficher(a)));
        ui->tab_juge->setModel((j.afficher(a)));
    }

    else
        msgbox.setText("echec de suppression");
    msgbox.exec();
}




void MainWindow::on_yas_modifer_clicked()
{
    QString cin=ui->le_cin_2->text();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom_2->text();
    int num=ui->le_num_2->text().toInt();
    int nb=ui->le_nb2->text().toInt();

    Juge m(cin,nom,prenom,num,nb);
    QMessageBox msgbox;
    if(m.chercher(cin)==true)

    {
        bool test=m.modifier();

        if(test==true)
        {
            msgbox.setText("modification avec succe");
            ui->tab_juge2->setModel((m.afficher(a)));
            ui->tab_juge->setModel((m.afficher(a)));
            ui->tab_juge1->setModel((m.afficher(a)));
            ui->tab_juge3->setModel((m.afficher(a)));
        }
        else
            msgbox.setText("echec de modification");
        msgbox.exec();
    }
    else
        msgbox.setText("juge introuvable");
    msgbox.exec();


}

void MainWindow::on_yas_tri1_clicked()
{
    ui->tab_juge->setModel(j.sort_croissant());
}





void MainWindow::on_yas_tri2_clicked()
{
    ui->tab_juge->setModel(j.sort_decroissant());
}

void MainWindow::on_chercher_yas_textChanged(const QString &arg1)
{
    ui->tab_juge->setModel(j.chercher2(arg1));
}

void MainWindow::on_yas_chercher_clicked()
{
    QString s = ui->chercher->text() ;
    ui->tab_juge->setModel(j.chercher2(s));
}




void MainWindow::on_yas_browse_clicked()
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

    ui->file->setText( fileListString );

}

void MainWindow::on_yas_send_clicked()
{
    Smtp* smtp = new Smtp("grata.yasmine@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("grata.yasmine@esprit.tn", ui->yas_rcpt->text(), ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("grata.yasmine@esprit.tn", ui->yas_rcpt->text(), ui->subject->text(),ui->msg->toPlainText());
}



void MainWindow::on_yas_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tab_juge->model()->rowCount();
    const int columnCount =ui->tab_juge->model()->columnCount();


    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("eleve")
        <<  "</head>\n"
        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
        "<h1>Liste des Evenements</h1>"

        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tab_juge->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_juge->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tab_juge->isColumnHidden(column))
            {
                QString data = ui->tab_juge->model()->data(ui->tab_juge->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
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
    printer.setOutputFileName("mypdffile.pdf");
    document->print(&printer);

}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

    ui->tab_juge_2->setModel(j.affichercalendrier(date));

}





void MainWindow::on_yas_done_clicked()
{
    QDate q;
    QMessageBox msgbox;
    QSqlQuery query;
    QDate datenow = QDate::currentDate() ;
    QString date = datenow.toString("dd/MM/yyyy") ;
    query.prepare("delete from AFFAIRE_JURIDIQUE where DATECAS =\'"+date+"\'");


    query.exec();
    if(query.exec())
    {
        msgbox.setText("journee termine");
        ui->tab_juge_2->setModel(j.affichercalendrier(q));
    }

    else
        msgbox.setText("echec de suppression");
    msgbox.exec();
}

void MainWindow::on_yas_verifier_clicked()
{
    QString message, numcas=ui->chercher_2->text();
    reverse(numcas.begin(), numcas.end());
    QSqlQuery query;

    if (query.exec ("SELECT REVERSE(PRENOM),REVERSE(NOM) FROM AFFAIRE_JURIDIQUE WHERE numcas= '"+numcas+"\'") )
    {
        if  (query.next())
        {
            message="Nom : " +query.value(1).toString()+" prenom : " +query.value(0).toString();
            string s = message.toStdString();
            const char* p = s.c_str();
            msystemtryicon->showMessage(tr("notification"),tr(p));
        }
        else msystemtryicon->showMessage(tr("notification"),tr("identifiant introuvable"));
    }
}

/*****************************************************yasmine***************************************************************************/
/*****************************************************aziz***************************************************************************/
void MainWindow::on_pushButton_ajouter_AZ_clicked()
{
    int ID_SALLE=ui->lineEdit->text().toInt();
    int NOMBRE_PLACES_TOTAL=ui->lineEdit_2->text().toInt();
    int NOMBRES_CAMER_ACTIVEES=ui->lineEdit_3->text().toInt();
    QString DISPONIBILTE=ui->lineEdit_4->text();

    SALLE_AUDIENCE s(ID_SALLE,NOMBRE_PLACES_TOTAL,NOMBRES_CAMER_ACTIVEES,DISPONIBILTE);

    bool test=s.ajout();
    if(test)
    {
        ui->tableS->setModel(s.affichage());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Ajout effectué. \n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("ajout impossible"),
                              QObject::tr("le ID taper existe déja"), QMessageBox::Cancel);
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }
}



void MainWindow::on_pushButton_supprimer_AZ_clicked()
{
    int ID_SALLE=ui->lineEdit_5->text().toInt();
    bool test=p.suppression(ID_SALLE);
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


void MainWindow::on_updateBtnAZ_clicked()
{
    int ID_SALLE=ui->id->text().toInt();
    int NOMBRE_PLACES_TOTAL=ui->nb->text().toInt();
    int NOMBRES_CAMER_ACTIVEES=ui->c->text().toInt();
    QString DISPONIBILTE=ui->dis->text();
    SALLE_AUDIENCE p(ID_SALLE,NOMBRE_PLACES_TOTAL,NOMBRES_CAMER_ACTIVEES,DISPONIBILTE);

    bool test=p.modification();
    if(test)
    {
        //actualiser pour l'affichage
        ui->tableS->setModel(p.affichage());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("modification effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                              QObject::tr("modification non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pdfbuttonAZ_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableS->model()->rowCount();
    const int columnCount = ui->tableS->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        //     "<align='right'> " << datefich << "</align>"
        "<center> <H1>listes des salles </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableS->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableS->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableS->isColumnHidden(column))
            {
                QString data = ui->tableS->model()->data(ui->tableS->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);

}

void MainWindow::on_tributtonAZ_clicked()
{
    ui->tableS->setModel(p.trie());
}

void MainWindow::on_trier2AZ_clicked()
{
    ui->tableS->setModel(p.trie2());
}











void MainWindow::on_statbtnAZ_clicked()
{


    QPieSeries *series = new QPieSeries();


    QStringList list=p.listedispo("DISPONIBILTE");



    for (int i =0; i< list.size(); i++)
    {
        series->append(list[i],p.calcul_dispo(list[i],"DISPONIBILTE"));

    }
    QPieSlice *slice = series->slices().at(1);
    slice->setLabelVisible();
    slice->setExploded();


    QtCharts::QChart *chart =new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques");
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartview=new QChartView(chart);
    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(chartview,0,0);
    ui->statbtnAZ->setLayout(mainLayout);
}


void MainWindow::on_excelAZ_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                       tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableS);

    //colums to export
    obj.addField(0, "ID_SALLE", "int");
    obj.addField(1, "NOMBRE_PLACES_TOTAL", "int");
    obj.addField(2, "NOMBRES_CAMER_ACTIVEES", "int");
    obj.addField(3, "DISPONIBILTE", "char(20)");

    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                );
    }
}



void MainWindow::on_btnVersArduinoAZ_clicked()
{
    Ar.write_to_arduino("A");  //envoyer 0 à arduino
}

void MainWindow::on_btnVerifAZ_clicked()
{
    QString ID_SALLE=ui->lineEdit_6->text();
    QSqlQuery query;
    QByteArray message;
    QString ch;
    int idd,id2;
    id2=ui->lineEdit_6->text().toInt();
    QSqlQuery query1;


    query1.prepare("select ID_SALLE from SALLE_AUDIENCE where ID_SALLE=:ID_SALLE");
    query1.bindValue(":ID_SALLE", ID_SALLE);
    query1.exec();
    while(query1.next())
    {

        idd=query1.value(0).toInt();
    }

    if(idd==id2)
    {
        QMessageBox::information(nullptr, QObject::tr("vérification en cours"),
                                 QObject::tr("vérification réussite"), QMessageBox::Cancel);
        query.prepare("select DISPONIBILTE from SALLE_AUDIENCE where ID_SALLE = "+ID_SALLE+"");
        if (query.exec())

        {
            while(query.next())
            {
                ch =query.value(0).toString();

            }

            message=ch.toUtf8();
            Ar.write_to_arduino("B") ;
            Ar.write_to_arduino(message) ;

        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("pas de vérification"),
                              QObject::tr("ID n'existe pas"), QMessageBox::Cancel);
    }
}

void MainWindow::on_TrouverAZIZ_textChanged(const QString &arg1)
{
    ui->tableS->setModel(p.recherche(arg1));
}
/*****************************************************aziz***************************************************************************/





