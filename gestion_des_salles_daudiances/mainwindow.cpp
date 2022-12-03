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

#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>
#include <QSqlQuery>
#include <exportexcelobject.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableS->setModel(p.affichage());
    ui->lineEdit->setValidator(new QIntValidator(1,999999, this));
    ui->lineEdit_2->setValidator(new QIntValidator(1,999999, this));
    ui->lineEdit_3->setValidator(new QIntValidator(1,999999, this));
    ui->ID_SALLE->setValidator(new QIntValidator(1,999999, this));
    ui->NOMBRE_PLACES_TOTAL->setValidator(new QIntValidator(1,999999, this));
    ui->NOMBRES_CAMER_ACTIVEES->setValidator(new QIntValidator(1,999999, this));
    ui->lineEdit_5->setValidator(new QIntValidator(1,999999, this));
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());

        ui->Map->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
    int ret=A.connect_arduino();
             switch (ret) {
             case(0):qDebug()<<"arduino is available and connect to:"<<A.getarduino_port_name();
                 break;
             case(1):qDebug()<<"arduino is available but not connected to:"<<A.getarduino_port_name();
                 break;
             case(-1):qDebug()<<"arduino is not available";

             }
             QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


}

MainWindow::~MainWindow()
{
    delete ui;

}



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
{QMessageBox::critical(nullptr, QObject::tr("ajout impossible"),
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
    int ID_SALLE=ui->ID_SALLE->text().toInt();
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
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
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
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tableS->isColumnHidden(column)) {
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



        for (int i =0; i< list.size();i++)
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
    A.write_to_arduino("0");  //envoyer 0 à arduino
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
       {      QMessageBox::information(nullptr, QObject::tr("vérification en cours"),
                                       QObject::tr("vérification réussite"), QMessageBox::Cancel);
                query.prepare("select DISPONIBILTE from SALLE_AUDIENCE where ID_SALLE = "+ID_SALLE+"");
        if (query.exec())

                            {
                                while(query.next())
                                {
                                 ch =query.value(0).toString();

                                }

                                 message=ch.toUtf8();
                                 A.write_to_arduino("4") ;
                                 A.write_to_arduino(message) ;

    }}
        else  {  QMessageBox::critical(nullptr, QObject::tr("pas de vérification"),
                                                    QObject::tr("ID n'existe pas"), QMessageBox::Cancel); }
}

void MainWindow::on_TrouverAZIZ_textChanged(const QString &arg1)
{
     ui->tableS->setModel(p.recherche(arg1));
}
