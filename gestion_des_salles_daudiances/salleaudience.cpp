#include "salleaudience.h"
#include <string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QtWidgets>

SALLE_AUDIENCE::SALLE_AUDIENCE()
{
DISPONIBILTE="";
ID_SALLE=0;
NOMBRE_PLACES_TOTAL=0;
NOMBRES_CAMER_ACTIVEES=0;
}

SALLE_AUDIENCE::SALLE_AUDIENCE( int ID_SALLE, int NOMBRE_PLACES_TOTAL, int NOMBRES_CAMER_ACTIVEES,QString DISPONIBILTE)
{
    this->DISPONIBILTE=DISPONIBILTE;
    this->ID_SALLE=ID_SALLE;
    this->NOMBRE_PLACES_TOTAL=NOMBRE_PLACES_TOTAL;
    this->NOMBRES_CAMER_ACTIVEES=NOMBRES_CAMER_ACTIVEES;

}


QString SALLE_AUDIENCE::getdispo(){ return DISPONIBILTE;}
int SALLE_AUDIENCE::getid(){ return ID_SALLE;}
int SALLE_AUDIENCE::getnbplace(){ return NOMBRE_PLACES_TOTAL;}
int SALLE_AUDIENCE::getcamenmarche(){ return NOMBRES_CAMER_ACTIVEES;}

void SALLE_AUDIENCE::setdispo(QString DISPONIBILTE){this->DISPONIBILTE=DISPONIBILTE; }
void SALLE_AUDIENCE::setid(int ID_SALLE){this->ID_SALLE=ID_SALLE; }
void SALLE_AUDIENCE::setcamenmarche(int NOMBRES_CAMER_ACTIVEES){this->NOMBRES_CAMER_ACTIVEES=NOMBRES_CAMER_ACTIVEES; }
void SALLE_AUDIENCE::setnbplace(int NOMBRE_PLACES_TOTAL){this->NOMBRE_PLACES_TOTAL=NOMBRE_PLACES_TOTAL; }


bool SALLE_AUDIENCE::ajout()
{
    QSqlQuery query;
    QString id_string = QString::number(ID_SALLE);
    QString res = QString::number(NOMBRE_PLACES_TOTAL);
    QString res1 = QString::number(NOMBRES_CAMER_ACTIVEES);
    query.prepare("insert into SALLE_AUDIENCE (ID_SALLE,NOMBRE_PLACES_TOTAL,NOMBRES_CAMER_ACTIVEES,DISPONIBILTE)"
                  "values (:ID_SALLE,:NOMBRE_PLACES_TOTAL,:NOMBRES_CAMER_ACTIVEES,:DISPONIBILTE)");
    query.bindValue(":ID_SALLE",id_string);
    query.bindValue(":NOMBRE_PLACES_TOTAL",res);
    query.bindValue(":NOMBRES_CAMER_ACTIVEES",res1);
    query.bindValue(":DISPONIBILTE",DISPONIBILTE);
    return query.exec();
}

bool SALLE_AUDIENCE::suppression(int ID_SALLE)
{

    int idd;
        QSqlQuery query,query1;
        QString id_string=QString::number(ID_SALLE);

        query.prepare(" select ID_SALLE from SALLE_AUDIENCE where ID_SALLE=:ID_SALLE");
        query.bindValue(":ID_SALLE", id_string);
        query.exec();
        while(query.next())
      {

       idd=query.value(0).toInt();
       }
        if (idd!=ID_SALLE) {  QMessageBox::critical(nullptr, QObject::tr("supp impossible"),
       QObject::tr("le ID_SALLE taper n'existe pas"), QMessageBox::Cancel); }
        else {
            query1.prepare("Delete from SALLE_AUDIENCE where ID_SALLE= :ID_SALLE");
            query1.bindValue(":ID_SALLE", ID_SALLE);
            QMessageBox::information(nullptr, QObject::tr("suppression reussit"),
               QObject::tr("suppression reussit"), QMessageBox::Cancel);


       }
        return  query1.exec();
}

QSqlQueryModel * SALLE_AUDIENCE::affichage()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from SALLE_AUDIENCE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_SALLE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMBRE_PLACES_TOTAL"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOMBRES_CAMER_ACTIVEES"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DISPONIBILTE"));


    return model;
}
    bool SALLE_AUDIENCE::modification()
    {
        int idd;
            QSqlQuery query,query1;
            QString id_string=QString::number(ID_SALLE);

            query.prepare(" select ID_SALLE from SALLE_AUDIENCE where ID_SALLE=:ID_SALLE");
            query.bindValue(":ID_SALLE", id_string);
            query.exec();
            while(query.next())
          {

           idd=query.value(0).toInt();
           }
        if (idd!=ID_SALLE) {  QMessageBox::critical(nullptr, QObject::tr("modification impossible"),
       QObject::tr("ID n'existe pas"), QMessageBox::Cancel); }
        else {
    query1.prepare("update SALLE_AUDIENCE set ID_SALLE= :ID_SALLE , NOMBRE_PLACES_TOTAL=:NOMBRE_PLACES_TOTAL , NOMBRES_CAMER_ACTIVEES=:NOMBRES_CAMER_ACTIVEES , DISPONIBILTE=:DISPONIBILTE where ID_SALLE = :ID_SALLE ");
    query1.bindValue(":ID_SALLE",ID_SALLE);
    query1.bindValue(":NOMBRE_PLACES_TOTAL",NOMBRE_PLACES_TOTAL);
    query1.bindValue(":NOMBRES_CAMER_ACTIVEES",NOMBRES_CAMER_ACTIVEES);
    query1.bindValue(":DISPONIBILTE",DISPONIBILTE);
    QMessageBox::information(nullptr, QObject::tr("modification reussit"),
       QObject::tr("modification reussit"), QMessageBox::Cancel);

        }
         return  query1.exec();
    }

QSqlQueryModel* SALLE_AUDIENCE::trie()
    {
        QSqlQueryModel* model = new QSqlQueryModel();

            model->setQuery("select ID_SALLE,NOMBRE_PLACES_TOTAL,NOMBRES_CAMER_ACTIVEES,DISPONIBILTE from SALLE_AUDIENCE ORDER BY ID_SALLE asc");

            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SALLE"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMBRE_PLACES_TOTAL"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRES_CAMER_ACTIVEES"));
                        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DISPONIBILTE"));


        return model;
    }

QSqlQueryModel* SALLE_AUDIENCE::trie2()
    {
        QSqlQueryModel* model = new QSqlQueryModel();

            model->setQuery("select ID_SALLE,NOMBRE_PLACES_TOTAL,NOMBRES_CAMER_ACTIVEES,DISPONIBILTE from SALLE_AUDIENCE ORDER BY ID_SALLE desc");

            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_SALLE"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOMBRE_PLACES_TOTAL"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRES_CAMER_ACTIVEES"));
                        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DISPONIBILTE"));


        return model;
    }

QSqlQueryModel *SALLE_AUDIENCE::recherche(QString ID_SALLE)
{

    QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM SALLE_AUDIENCE WHERE ID_SALLE LIKE'%"+ID_SALLE+"%'");
        return model;
}


QStringList SALLE_AUDIENCE::listedispo(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from SALLE_AUDIENCE");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int SALLE_AUDIENCE::calcul_dispo(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from SALLE_AUDIENCE  WHERE "+val+"=:adresse");
     query.bindValue(":adresse", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}



