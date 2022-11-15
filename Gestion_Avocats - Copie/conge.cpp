#include "conge.h"
#include "avocat.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
conge::conge()
{
    Date_Debut="";
    Date_Fin="";
    Motif="";

}

conge :: conge( int Id_Avocat , QString Date_Debut , QString Date_Fin , QString Motif)
{
this->Id_Avocat =Id_Avocat;
this->Date_Debut= Date_Debut ;
this->Date_Fin= Date_Fin ;
this->Motif = Motif ;
}

bool conge :: ajouter_c()
{
    QSqlQuery query;
    QString Id_Avocat_string=QString:: number(Id_Avocat);


          query.prepare("INSERT INTO conge  (ID_AVOCAT ,DATE_DEBUT,DATE_FIN , MOTIF ) "
                        "VALUES (:id, :beginD, :endD, :why )");
          query.bindValue(0, Id_Avocat_string );
          query.bindValue(1,  Date_Debut);

          query.bindValue(2,  Date_Fin);
          query.bindValue(3, Motif  );
            return  query.exec();
}

QSqlQueryModel* conge :: afficher_c()
{

    QSqlQueryModel* model= new QSqlQueryModel();


    model->setQuery("SELECT  ID_AVOCAT , Nom , PRENOM ,DATE_DEBUT , DATE_FIN , MOTIF "
                    "FROM AVOCAT  "
                    "NATURAL JOIN CONGE  ");



     model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
     model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Debut du congé "));
     model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Fin du congé "));
     model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Motif "));

    return model ;



}
