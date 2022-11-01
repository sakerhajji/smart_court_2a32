#include "salleaudience.h"
#include <string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

salleaudience::salleaudience()
{
dispo="";
id=0;
nbplace=0;
camenmarche=0;
}

salleaudience::salleaudience( int id, int nbplace, int camenmarche,QString dispo)
{
    this->dispo=dispo;
    this->id=id;
    this->nbplace=nbplace;
    this->camenmarche=camenmarche;

}


/*
void setid(int id){this->id=id;}
void setnbplace(int nbplace){this->nbplace=n;}
void setcamenmarche(int camenmarche){this->camenmarche=c;}
void setdispo(QString dispo){dispo=d;}
*/

QString salleaudience::getdispo(){ return dispo;}
int salleaudience::getid(){ return id;}
int salleaudience::getnbplace(){ return nbplace;}
int salleaudience::getcamenmarche(){ return camenmarche;}

void salleaudience::setdispo(QString dispo){this->dispo=dispo; }
void salleaudience::setid(int id){this->id=id; }
void salleaudience::setcamenmarche(int camenmarche){this->camenmarche=camenmarche; }
void salleaudience::setnbplace(int nbplace){this->nbplace=nbplace; }


bool salleaudience::ajout()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString res = QString::number(nbplace);
    QString res1 = QString::number(camenmarche);
    query.prepare("insert into SALLEAUDIENCE (id,nbplace,camenmarche,dispo)"
                  "values (:id,:nbplace,:camenmarche,:dispo)");
    query.bindValue(":id",id_string);
    query.bindValue(":nbplace",res);
    query.bindValue(":camenmarche",res1);
    query.bindValue(":dispo",dispo);
    return query.exec();
}

bool salleaudience::suppression(int id)
{   
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("Delete from SALLEAUDIENCE where ID= :id");
    query.bindValue(":id", id_string);
    return query.exec();
}

QSqlQueryModel * salleaudience::affichage()
{

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from SALLEAUDIENCE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nbplace"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("camenmarche"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("dispo"));


    return model;
}
    bool salleaudience::modification(int id,int nbplace,int camenmarche,QString dispo)
    {
    QSqlQuery query;

    query.prepare("update SALLEAUDIENCE set id= :id, nbplace=:nbplace,camenmarche=:camenmarche,dispo=:dispo where id = :id )");
    query.bindValue(":id",id);
    query.bindValue(":nbplace",nbplace);
    query.bindValue(":camenmarche",camenmarche);
    query.bindValue(":dispo",dispo);
    return    query.exec();
    }

