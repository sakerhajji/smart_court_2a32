#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avocat.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQueryModel>
#include<QtDebug>
#include "smtp.h"
#include <QSqlQuery>
#include "arduino.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->le_id->setValidator(new QIntValidator(0, 999999999, this));
    ui->le_num_tel->setValidator(new QIntValidator(0, 999999999, this));
    ui->table_avocat_2->setModel(A.afficher());
    ui->table_avocat->setModel(A.afficher());

    int ret=a.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).

    //for email tab
    //connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
   // connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
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

    Avocat A( Id_Avocat ,Nom ,Prenom,Date_naissance ,Numero_telephone,Nombre_Proces_Gagnes );


    bool test=A.ajouter();
    if(test)
    {

        ui->table_avocat_2->setModel(A.afficher());
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
    int id=ui->le_id_supp->text().toInt();
    bool test = A.supprimer(id) ;
    QMessageBox msgBox ;

    if (test)
         { ui->table_avocat->setModel(A.afficher());
        ui->table_avocat_2->setModel(A.afficher());

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

 Avocat A1( Id_Avocat ,Nom ,Prenom,Date_naissance,Numero_telephone, Nombre_Proces_Gagnes);


QMessageBox msgBox ;


bool test= A1.modifier();
if(test)
{ ui->table_avocat->setModel(A1.afficher());
  ui->table_avocat_2->setModel(A1.afficher());


             msgBox.setText("Modification  réussite");

}

else
      msgBox.setText("Modification  échouée ");
        msgBox.exec();

}


void MainWindow::on_btn_trouver_clicked()
{


    QString a = ui->Achercher->text();

    ui->table_rechercher->setModel(A.chercher(a));
}





void MainWindow::on_Achercher_textChanged(const QString &arg1)
{

    ui->table_rechercher->setModel(A.chercher(arg1));

}



void MainWindow::on_btn_tri_clicked()
{

    QString b = (ui->radioB_croiss->isChecked())?"ASC":"DESC" ;

    int x = ui->comboBox->currentIndex() ;
    QString a ;
    switch (x) {
    case 0 :a="NOMBRE_PROCES_GAGNES"; break ;
    case 1 :a="ID_AVOCAT"; break ;
    case 2 :a="NOM";break ;

    }
    ui->table_avocat->setModel(A.sort(a,b));
}





void MainWindow::on_pdf_clicked()
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
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->table_rechercher->isColumnHidden(column)) {
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

void MainWindow::on_sendBtn_clicked()
{

    Smtp* smtp = new Smtp("eya.gadhoumi@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("eya.gadhoumi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("eya.gadhoumi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
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

void MainWindow::on_btn_evaluer_clicked()
{
    int x = ui->evaluation->currentIndex();
    switch (x)
    {
    case 0 : ui->tab_evaluer->setModel(A.evaluerD());break ;
    case 1 : ui->tab_evaluer->setModel(A.evaluerM());break ;
    case 2 :ui->tab_evaluer->setModel(A.evaluerE());break ;
    }
}

void MainWindow::BarChart()
{
QSqlQuery q1 , q2 , q3 , q4 ;
qreal tot=0,c1=0,c2=0, c3= 0;

q1.prepare("SELECT * FROM AVOCAT");
q1.exec();

q2.prepare("SELECT * FROM AVOCAT WHERE NOMBRE_PROCES_GAGNES <=  10 ");
q2.exec();

q3.prepare("SELECT * FROM AVOCAT WHERE NOMBRE_PROCES_GAGNES > 10 And NOMBRE_PROCES_GAGNES <= 15 ");
q3.exec();

q4.prepare("SELECT * FROM AVOCAT WHERE NOMBRE_PROCES_GAGNES > 15  ");
q4.exec();

while (q1.next()){tot++;}
while (q2.next()){c1++;}
while (q3.next()){c2++;}
while (q4.next()){c3++;}




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
     BarChart();
}

void MainWindow::on_ajouter_conge_clicked()
{
    int Id_Avocat=ui->id_conge->text().toInt();
    QString Date_Debut =ui->date_debut->text();
    QString Date_Fin =ui->date_fin->text();
    QString  Motif=ui->motif->text();
    conge c (Id_Avocat, Date_Debut , Date_Fin , Motif );


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


void MainWindow::update_label()
{
    dataa=a.read_from_arduino();

    if(dataa=="v")

        ui->label_access->setText("Porte ouverte , access désormais autorisé  ! "); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ce qui est écrit

    else if (dataa=="n")

        ui->label_access->setText("Attention ! Code erroné !");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ce qui est écrit

    else if (dataa =="s")
        ui->label_access->setText("L'avocat a dépassé les tentatives d'essais autorisées !  ");

}


