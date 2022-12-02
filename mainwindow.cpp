#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"juge.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QPrinter>
#include <QPainter>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableWidget>
#include<QSystemTrayIcon>




int a=1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    msystemtryicon = new QSystemTrayIcon(this);
    msystemtryicon->setIcon(QIcon(":/myappico.png"));
    msystemtryicon->setVisible(true);

    ui->le_num->setValidator( new QIntValidator(1, 999, this));
    ui->tab_juge->setModel(j.afficher(a));
    ui->tab_juge1->setModel(j.afficher(a));
    ui->tab_juge2->setModel(j.afficher(a));
    ui->tab_juge3->setModel(j.afficher(a));
    ui->le_num_2->setValidator( new QIntValidator(1, 999, this));
    int ret=A.connect_arduino(); // lancer la connexion Ã  arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite Ã  la reception du signal readyRead (reception des donnÃ©es).



}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    {msgbox.setText("echec d'ajout");
         ui->tab_juge1->setModel((j.afficher(a)));
    ui->tab_juge->setModel((j.afficher(a)));
    ui->tab_juge2->setModel((j.afficher(a)));
    ui->tab_juge3->setModel((j.afficher(a)));}
    else
    {msgbox.setText("ajout avec succe");
        msgbox.exec();}

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
    ui->tab_juge->setModel((j.afficher(a)));}

    else
    msgbox.setText("echec de suppression");
        msgbox.exec();
}

/*void MainWindow::on_yas_supprimer_clicked()
{
    Juge j1;
            QString c=ui->le_cin_supp->text();
    bool test=j1.supprimer(c);
    QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("supprimer avec succe");
        ui->tab_juge3->setModel((j1.afficher(a)));
    ui->tab_juge2->setModel((j1.afficher(a)));
    ui->tab_juge1->setModel((j1.afficher(a)));
    ui->tab_juge->setModel((j1.afficher(a)));}

    else
    msgbox.setText("echec de suppression");
        msgbox.exec();
}*/




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

    {bool test=m.modifier();

    if(test==true)
    {msgbox.setText("modification avec succe");
         ui->tab_juge2->setModel((m.afficher(a)));
    ui->tab_juge->setModel((m.afficher(a)));
    ui->tab_juge1->setModel((m.afficher(a)));
    ui->tab_juge3->setModel((m.afficher(a)));}
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

void MainWindow::on_chercher_textChanged(const QString &arg1)
{
    ui->tab_juge->setModel(j.chercher2(arg1));
}

void MainWindow::on_yas_chercher_clicked()
{
    QString s = ui->chercher->text() ;
    ui->tab_juge->setModel(j.chercher2(s));
}






/*void MainWindow::on_undoView_viewportEntered()
{
    if(a==1)
        QMessageBox::critical(nullptr, QObject::tr("notification "),
                    QObject::tr("attention au bruit\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}*/

/*void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index==4)
        ui->tab_juge->hide();
}*/

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
        smtp->sendMail("grata.yasmine@esprit.tn", ui->yas_rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("grata.yasmine@esprit.tn", ui->yas_rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->yas_rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
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
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_juge->isColumnHidden(column)) {
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

    QDate selectedDate = ui->calendarWidget->selectedDate();
ui->tab_juge_2->setModel(j.affichercalendrier(selectedDate));





}

void MainWindow::update_label()
{
    data=A.read_from_arduino();


    QString message , numcas=ui->chercher_2->text();
    QSqlQuery query;
           query.exec("SELECT PRENOM , NOM FROM AFFAIRE_JURIDIQUE WHERE num_cas="+numcas+"");

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


}



void MainWindow::on_yas_done_clicked()
{QDate q;
QMessageBox msgbox;
    QSqlQuery query;
    query.prepare("delete from essaie where DATE1 like (sysdate)");

     query.exec();
     if(query.exec())
     {
         msgbox.setText("journee termine");
         ui->tab_juge_2->setModel(j.affichercalendrier(q));}

     else
     msgbox.setText("echec de suppression");
         msgbox.exec();
}

void MainWindow::on_yas_verifier_clicked()
{
    QString message , numcas=ui->chercher_2->text();
    QSqlQuery query;
           if (query.exec("SELECT PRENOM , NOM FROM AFFAIRE_JURIDIQUE WHERE num_cas="+numcas+""));
          { if  (query.next())
                {
                   message="Nom : " +query.value(1).toString()+" prenom : " +query.value(0).toString();
                   string s = message.toStdString();
                   const char* p = s.c_str();
                   msystemtryicon->showMessage(tr("notification"),tr(p));
               }
               else msystemtryicon->showMessage(tr("notification"),tr("identifiant introuvable"));
           }



/* QString cin_j=ui->chercher_2->text();

     QSqlQuery query;
 Juge j1;
     QByteArray message;

     QString ch,o;



     query.prepare("select nom,prenom from VOLS where CIN_J = "+cin_j+"");
     if (query.exec())
                         {
                             while(query.next())

                              ch =query.value(0).toString();
                               o=query.value(1).toString();

                             ui->hhhh->addItem(ch);

           }*/
}

