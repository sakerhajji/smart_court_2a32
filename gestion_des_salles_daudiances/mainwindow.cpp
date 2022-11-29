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
    ui->id->setValidator(new QIntValidator(1,999999, this));
    ui->nb->setValidator(new QIntValidator(1,999999, this));
    ui->c->setValidator(new QIntValidator(1,999999, this));
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



void MainWindow::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit->text().toInt();
    int nbplace=ui->lineEdit_2->text().toInt();
    int camenmarche=ui->lineEdit_3->text().toInt();
    QString dispo=ui->lineEdit_4->text();

    salleaudience s(id,nbplace,camenmarche,dispo);

    bool test=s.ajout();
    if(test)
    {
           ui->tableS->setModel(s.affichage());
        QMessageBox::information(nullptr, QObject::tr("Ok"),
        QObject::tr("Ajout effectué. \n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
     }
    else

        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_pushButton_supprimer_clicked()
{
    int id=ui->lineEdit_5->text().toInt();
       bool test=p.suppression(id);
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


void MainWindow::on_update_clicked()
{
    int id=ui->id->text().toInt();
    int nbplace=ui->nb->text().toInt();
    int camenmarche=ui->c->text().toInt();
    QString dispo=ui->dis->text();
        salleaudience p(id,nbplace,camenmarche,dispo);

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



void MainWindow::on_pdfbutton_clicked()
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

void MainWindow::on_tributton_clicked()
{
ui->tableS->setModel(p.trie());
}

void MainWindow::on_trierbutton2_clicked()
{
ui->tableS->setModel(p.trie2());
}


void MainWindow::on_recherchebutton_textChanged(const QString &arg1)
{
    ui->tableS->setModel(p.recherche(arg1));
}








void MainWindow::on_bb_clicked()
{


    QPieSeries *series = new QPieSeries();


        QStringList list=p.listedispo("dispo");



        for (int i =0; i< list.size();i++)
        {
            series->append(list[i],p.calcul_dispo(list[i],"dispo"));

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
        ui->bb->setLayout(mainLayout);
}


void MainWindow::on_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableS);

    //colums to export
    obj.addField(0, "ID", "int");
    obj.addField(1, "nbplace", "int");
    obj.addField(2, "camenmarche", "int");
    obj.addField(3, "dispo", "char(20)");
   /* obj.addField(4, "date de depart", "char(20)");
    obj.addField(5, "pilote", "char(20)");
    obj.addField(5, "avion", "char(20)");*/


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}



void MainWindow::on_pushButton_5_clicked()
{
    A.write_to_arduino("0");  //envoyer 0 à arduino
}

void MainWindow::on_pushButton_6_clicked()
{
    QString ID=ui->lineEdit_6->text();
        QSqlQuery query;
        QByteArray message;
        QString ch;
        query.prepare("select DISPO from SALLEAUDIENCE where ID = "+ID+"");
        if (query.exec())
                            {
                                while(query.next())
                                {
                                 ch =query.value(0).toString();



                                }
                                 message=ch.toUtf8();
                                 A.write_to_arduino("4") ;
                                 A.write_to_arduino(message) ;

    }
}
