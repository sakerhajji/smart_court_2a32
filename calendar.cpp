#include "calendar.h"
#include "ui_calendar.h"
#include "juge.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QtDebug>
#include<QObject>
#include <QMessageBox>
#include"connection.h"


calendar::calendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calendar)
{
    ui->setupUi(this);
}

calendar::~calendar()
{
    delete ui;
}



void calendar::on_buttonBox_accepted()
{
    QString nom=ui->evenement->text();
    QString date1=ui->dateEdit->text();



    QSqlQuery query;
    query.prepare("INSERT INTO essaie (date1,nom) "
                  "VALUE (:nom, :date1)");

    query.bindValue(":nom",nom);
    query.bindValue(":date1",date1);
    query.exec();

    if(query.exec())
        {QMessageBox::information(nullptr, QObject::tr("calender is open"),
                    QObject::tr("ajout en succes.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);};

}
