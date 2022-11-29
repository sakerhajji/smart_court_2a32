#include "personnels.h"
#include <QSqlQuery>
#include<QDebug>
#include<QObject>

personnels::personnels(int id,QString nom,QString prenom,int age,QString adresse)
{
    this->id=id;
     this->nom=nom;
     this->prenom=prenom;
     this->age=age;
     this->adresse=adresse;

}
bool personnels::ajouter()
{
   QString res=QString ::number(id);
   QString res2=QString ::number(age);
      QSqlQuery query;

    query.prepare("INSERT INTO personnels (id, nom, prenom,age,adresse) "
                     "VALUES (:id, :nom, :prenom,:age,:adresse)");
      //creation des variables liees
    query.bindValue(":id", res);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
         query.bindValue(":age", res2);
       query.bindValue(":adresse", adresse);


       return query.exec(); //exec() envoie la requete pour l'executeur
}
bool personnels::supprimer(int id)
{
    QSqlQuery query;


       query.prepare("delete from personnels where id=:id");
       query.bindValue(0, id);


       query.exec();

}
QSqlQueryModel*personnels::afficher()
{

     QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id,nom,prenom,age,adresse  FROM personnels where archiver=0");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));

return model;
}
bool personnels::modifier()
{
    QString res=QString ::number(id);
    QString res2=QString ::number(age);
     QSqlQuery query;

query.prepare("update personnels set id= :id, nom= :nom, prenom= :prenom,age=:age,adresse=:adresse where id =:id ");
query.bindValue(":id", res);
   query.bindValue(":nom", nom);
   query.bindValue(":prenom", prenom);
   query.bindValue(":age",res2);
   query.bindValue(":adresse",adresse);

return    query.exec();
}

void personnels::archiver(int id)
{
    QString res=QString ::number(id);
     QSqlQuery query;

query.prepare("UPDATE PERSONNELS set archiver= :val where id =:id ");
query.bindValue(":id", res);
   query.bindValue(":val", 1);


   query.exec();
}
QSqlQueryModel*personnels::afficher_historique()
{

     QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id,nom,prenom,age,adresse  FROM personnels where archiver=1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));

return model;
}
QSqlQueryModel * personnels::affichertriAZ()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * from personnels order by prenom Asc");
return model;
}
QSqlQueryModel * personnels::affichertriZA()
{   QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("SELECT * from personnels order by prenom DESC");
return model;
}
QSqlQueryModel *personnels::rechercher(QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM personnels WHERE id LIKE'"+rech+"%'");
    return model;


}
QSqlQueryModel *personnels::recherchernom(QString nom)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM personnels WHERE nom LIKE'"+nom+"%'");
    return model;
}

QStringList personnels::listeadresses(QString var){
    QSqlQuery query;
    query.prepare("select DISTINCT("+var+") from personnels");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int personnels::calcul_adresses(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from personnels  WHERE "+val+"=:adresse");
     query.bindValue(":adresse", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}
