#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"personnels.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include<QPrinter>
#include <QSqlRecord>
#include "QrCode.hpp"
#include"arduino.h"
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id -> setValidator (new QIntValidator(0, 999999, this));

    ui->tablepp->setModel(p.afficher());


    /*************************** Arduino************************/


            int ret=A.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
             //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
             //le slot update_label suite à la reception du signal readyRead (reception des données).




   QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(rechEmploy()));

}

MainWindow::~MainWindow()
{
    delete ui;
}




/******************************** PARtie arduino *****************************************/
void MainWindow::rechEmploy()
{
    data.append(A.read_from_arduino());
     data= data.append(A.read_from_arduino());
QString ch= data.append(A.read_from_arduino());

     QSqlQueryModel *model=new QSqlQueryModel();

     model->setQuery("select * from personnels where id=  '"+ch+"'");
     QSqlRecord sr = model->record(0);
     QString code= sr.value(3).toString();

if (code!=""){
QString  message="ID : "+sr.value(0).toString()+"\nNom : "+sr.value(1).toString()+"\nPrenom : "+sr.value(2).toString();
     QMessageBox::information(this,"Personnel existant  " , message ,QMessageBox::Ok);


}
else {
    QMessageBox::critical(nullptr, QObject::tr("Personnel n'existe pas"),
             QObject::tr(data,"Personnel n'existe pas.\n"
                         "click cancel to exit . ") , QMessageBox::Cancel);
}

}

/******************************************************/
void MainWindow::on_ajouter_clicked()
{
    //recuperation des information saisis dans les 5 champs
   int id=ui->id->text().toInt();
   QString nom=ui->nom->text();
   QString prenom=ui->prenom->text();
   int age=ui->age->text().toInt();
   QString adresse=ui->adresse->text();


   personnels p(id,nom,prenom,age,adresse);
   bool test=p.ajouter();
   if(test)
   { QMessageBox::information(nullptr, QObject::tr("ok"),
                           QObject::tr("ajout effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
ui->tablepp->setModel(p.afficher());
   }

   else//si requete non executé
               QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("ajout non effectuée\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_supprimer_clicked()
{
    personnels p1; p1.setid(ui->id_supp->text().toInt());
    bool test=p1.supprimer(p1.getid());
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("supprimer avec succes");
        ui->tablepp->setModel(p.afficher());
    }
                else
        msgBox.setText("echec de supprimer");
    msgBox.exec();

}

void MainWindow::on_update_clicked()
{
    int id=ui->id2->text().toInt();
    QString nom=ui->nom2->text();
    QString prenom=ui->prenom2->text();
    int age=ui->age2->text().toInt();
    QString adresse=ui->adresse2->text();

    personnels p(id,nom,prenom,age,adresse);
    bool test=p.modifier();
        if(test)
        {
            //actualiser pour l'affichage
            ui->tablepp->setModel(p.afficher());
                    QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_clicked()
{
    int id= ui->lineEdit_archive->text().toInt();
    p.archiver(id);
    ui->tablepp->setModel(p.afficher());

}

void MainWindow::on_pushButton_2_clicked()
{
     ui->tablepp->setModel(p.afficher_historique());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tablepp->setModel(p.afficher());

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tablepp->setModel(p.affichertriAZ());

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tablepp->setModel(p.affichertriZA());

}

//void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)


void MainWindow::on_rechercher_button_clicked()
{
    QString rech =ui->idrech->text();
        ui->tablepp->setModel(p.rechercher(rech));
}



void MainWindow::on_pushButton_6_clicked()
{
    QString strStream;
                                        QTextStream out(&strStream);

                                        const int rowCount = ui->tablepp->model()->rowCount();
                                        const int columnCount = ui->tablepp->model()->columnCount();

                                        out <<  "<html>\n"
                                            "<head>\n"
                                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                            <<  QString("<title>%1</title>\n").arg("strTitle")
                                            <<  "</head>\n"
                                            "<body bgcolor=#ffffff link=#5000A0>\n"

                                           //     "<align='right'> " << datefich << "</align>"
                                            "<center> <H1>listes des personnels </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                        // headers
                                        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                        for (int column = 0; column < columnCount; column++)
                                            if (!ui->tablepp->isColumnHidden(column))
                                                out << QString("<th>%1</th>").arg(ui->tablepp->model()->headerData(column, Qt::Horizontal).toString());
                                        out << "</tr></thead>\n";

                                        // data table
                                        for (int row = 0; row < rowCount; row++) {
                                            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                            for (int column = 0; column < columnCount; column++) {
                                                if (!ui->tablepp->isColumnHidden(column)) {
                                                    QString data = ui->tablepp->model()->data(ui->tablepp->model()->index(row, column)).toString().simplified();
                                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                }
                                            }
                                            out << "</tr>\n";
                                        }
                                        out <<  "</table> </center>\n"
                                            "</body>\n"
                                            "</html>\n";

                                  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                                   QPrinter printer (QPrinter::PrinterResolution);
                                    printer.setOutputFormat(QPrinter::PdfFormat);
                                   printer.setPaperSize(QPrinter::A4);
                                  printer.setOutputFileName(fileName);

                                   QTextDocument doc;
                                    doc.setHtml(strStream);
                                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                    doc.print(&printer);














}

void MainWindow::on_qrcodegen_clicked()
{
    int tabeq=ui->tablepp->currentIndex().row();
           QVariant idd=ui->tablepp->model()->data(ui->tablepp->model()->index(tabeq,0));
           QString id= idd.toString();
           QSqlQuery qry;
           qry.prepare("select * from PERSONNELS where ID=:id");
           qry.bindValue(":ID",id);
           qry.exec();
              QString nom,prenom,adresse,ide;

           while(qry.next()){

               id=qry.value(1).toString();
               nom=qry.value(2).toString();
               prenom=qry.value(3).toString();
               adresse=qry.value(4).toString();


           }
           ide=QString(id);
                  ide="ID:"+id+"NOM:"+nom+"PRENOM:"+prenom,"ADRESSE:"+adresse;
           QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

           // Read the black & white pixels
           QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
           for (int y = 0; y < qr.getSize(); y++) {
               for (int x = 0; x < qr.getSize(); x++) {
                   int color = qr.getModule(x, y);  // 0 for white, 1 for black

                   // You need to modify this part
                   if(color==0)
                       im.setPixel(x, y,qRgb(254, 254, 254));
                   else
                       im.setPixel(x, y,qRgb(0, 0, 0));
               }
           }
           im=im.scaled(200,200);
           ui->qrcodecommande->setPixmap(QPixmap::fromImage(im));

}

void MainWindow::on_pushButton_7_clicked()
{

    QPieSeries *series11 = new QPieSeries();


     QStringList list11=p.listeadresses("age");


     for (int i =0; i< list11.size();i++)
     {
         series11->append(list11[i],p.calcul_adresses(list11[i],"age"));



     }

     QPieSlice *slice11 = series11->slices().at(1);
     slice11->setLabelVisible();
     slice11->setExploded();
     QPieSlice *slice1 = series11->slices().at(2);
     slice1->setLabelVisible();
     slice1->setExploded();

     QtCharts::QChart *chart11 =new QtCharts::QChart();
     chart11->addSeries(series11);
     chart11->setTitle("Statistiques");
     chart11->setAnimationOptions(QChart::AllAnimations);
     QChartView *chartview11=new QChartView(chart11);
     QGridLayout *mainLayout11=new QGridLayout();
     mainLayout11->addWidget(chartview11,0,0);
     ui->label_12->setLayout(mainLayout11);
}
