#include "juge.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QtDebug>
#include<QObject>
#include <QMessageBox>


Juge::Juge()
{
cin_j="";
nom=prenom="";
num_bureau=0;
nb_process_gagner=0;

}
Juge::Juge(QString c,QString n,QString p,int b,int d)
{
cin_j=c;
nom=n;
prenom=p;
num_bureau=b;
nb_process_gagner=d;
}
QString Juge::getcin(){return cin_j;};
QString Juge:: getnom(){return nom;};
QString Juge::getprenom(){return prenom;};
int Juge::getnum_bureau(){return num_bureau;};
int Juge::getnb_process_gagner(){return nb_process_gagner;};
void Juge::setcin(QString c){cin_j=c;};
void Juge::setnom(QString n){nom=n;};
void Juge::setprenom(QString p){prenom=p;};
void Juge::setnum_bureau(int b){num_bureau=b;};
void Juge::setnb_process_gagner(int d){nb_process_gagner=d;};

bool Juge::ajouter()
{


    QString num_strings=QString::number(num_bureau);
    QString nb_strings=QString::number(nb_process_gagner);
    QSqlQuery query;
    query.prepare("INSERT INTO juge (cin_j, nom,prenom,num_bureau,nb_process_gagner) "
                  "VALUES (:id, :forename, :surname, :bureau, :nb)");
    query.bindValue(":id", cin_j);
    query.bindValue(":forename", nom);
    query.bindValue(":surname", prenom);
    query.bindValue(":bureau",num_strings);
    query.bindValue(":nb",nb_strings);

    return query.exec();}

bool Juge::supprimer(QString cin_j)
{

    QSqlQuery query;
    query.prepare("delete from juge where cin_j= :cin_j");
    query.bindValue(":cin_j", cin_j);
    return query.exec();


}

QSqlQueryModel* Juge::afficher(int a)
{QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT* FROM juge");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_bureau"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nb_process_gagner"));

    if(a==1)
        QMessageBox::critical(nullptr, QObject::tr("notification "),
                    QObject::tr("attention au bruit\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

return model;
}


bool Juge::chercher(QString cin)
{bool test;
    QSqlQuery query;
    query.prepare("SELECT * FROM juge WHERE CIN_j LIKE'%"+cin+"%'");
    query.bindValue(":cin_j", cin);
    query.exec();
    if(query.exec())
   return test=true;
    else
         return test=false;
}


bool Juge::modifier()
{

    QSqlQuery query;
    QString num=QString::number(num_bureau);
    QString nb=QString::number(nb_process_gagner);

    query.prepare("update juge set cin_j= :cin_j, nom= :nom, prenom= :prenom , num_bureau= :num_bureau , nb_process_gagner= :nb_process_gagner where cin_j= :cin_j");
    query.bindValue(":cin_j",cin_j);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":num_bureau",num);
    query.bindValue(":nb_process_gagner",nb);

    return query.exec();

}

QSqlQueryModel* Juge::sort_decroissant()
{QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT* FROM juge order by nom desc");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_bureau"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nb_process_gagner"));

return model;
}

QSqlQueryModel* Juge::sort_croissant()
{QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT* FROM juge order by nom asc");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_bureau"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("nb_process_gagner"));

return model;
}

QSqlQueryModel* Juge :: chercher2(QString a)
{



   QSqlQueryModel* model= new QSqlQueryModel();


model->setQuery("select * from JUGE WHERE (CIN_J LIKE '%"+a+"%' OR NOM LIKE '%"+a+"%' OR PRENOM LIKE '%"+a+"%' OR NB_PROCESS_GAGNER LIKE '%"+a+"%' "
              "OR NUM_BUREAU LIKE '%"+a+"%') ");

model->setHeaderData(0, Qt::Horizontal,QObject::tr("identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_bureau"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("nb_process_gagner"));

  return model ;
}



