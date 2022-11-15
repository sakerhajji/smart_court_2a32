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
    Smtp* smtp = new Smtp("grata.yasmine@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("grata.yasmine@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("grata.yasmine@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
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


void MainWindow::on_pdf_clicked()
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




void MainWindow::on_pushButton_3_clicked()
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

void MainWindow::on_pushButton_4_clicked()
{
msystemtryicon->showMessage(tr("notification"),tr("il ya beaucoup du bruit dans la salle  "));
}
