#include "salleaudience.h"
#include <string>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QtWidgets>

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
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("dispo"));


    return model;
}
    bool salleaudience::modification()
    {
    QSqlQuery query;

    query.prepare("update SALLEAUDIENCE set ID= :id , NBPLACE=:nbplace , CAMENMARCHE=:camenmarche , DISPO=:dispo where ID = :id )");
    query.bindValue(":id",id);
    query.bindValue(":nbplace",nbplace);
    query.bindValue(":camenmarche",camenmarche);
    query.bindValue(":dispo",dispo);
    return    query.exec();
    }

QSqlQueryModel* salleaudience::trie()
    {
        QSqlQueryModel* model = new QSqlQueryModel();

            model->setQuery("select ID,nbplace,camenmarche,dispo from SALLEAUDIENCE ORDER BY ID asc");

            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbplace"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("camenmarche"));
                        model->setHeaderData(3, Qt::Horizontal, QObject::tr("dispo"));


        return model;
    }

QSqlQueryModel* salleaudience::trie2()
    {
        QSqlQueryModel* model = new QSqlQueryModel();

            model->setQuery("select ID,nbplace,camenmarche,dispo from SALLEAUDIENCE ORDER BY ID desc");

            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbplace"));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("camenmarche"));
                        model->setHeaderData(3, Qt::Horizontal, QObject::tr("dispo"));


        return model;
    }

QSqlQueryModel *salleaudience::recherche(QString id)
{

    QSqlQueryModel *model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM salleaudience WHERE ID LIKE'%"+id+"%'");
        return model;
}


QStringList salleaudience::listedispo(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from SALLEAUDIENCE");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int salleaudience::calcul_dispo(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from SALLEAUDIENCE  WHERE "+val+"=:adresse");
     query.bindValue(":adresse", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}



