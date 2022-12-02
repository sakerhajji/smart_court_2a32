#include "avocat.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Avocat::Avocat()
{
   Id_Avocat =0;
   Nom="";
   Prenom="";
   Date_naissance="";
   Numero_telephone= 0;
   Nombre_Proces_Gagnes=0;

 }

Avocat:: Avocat( int Id_Avocat , QString Nom  , QString Prenom  , QString Date_naissance, int Numero_telephone  , int Nombre_Proces_Gagnes  )
{this->Id_Avocat=Id_Avocat ;
 this->Nom=Nom ;
    this->Prenom=Prenom;
    this->Date_naissance=Date_naissance;
    this->Numero_telephone= Numero_telephone ;
    this->Nombre_Proces_Gagnes=Nombre_Proces_Gagnes ;
 }




bool Avocat:: ajouterA()
{
  //bool teest=false ;
  QSqlQuery query;
  QString Id_Avocat_string=QString:: number(Id_Avocat);
  QString Numero_telephone_string=QString:: number(Numero_telephone);
  QString Nombre_Proces_Gagnes_string=QString:: number(Nombre_Proces_Gagnes);


        query.prepare("INSERT INTO avocat (ID_AVOCAT ,NOM,PRENOM , DATE_NAISSANCE ,NOMBRE_PROCES_GAGNES,NUMERO_TELEPHONE) "
                      "VALUES (:id, :forename, :surname, :dateofbirth , :cases , :number)");
        query.bindValue(0, Id_Avocat_string );
        query.bindValue(1,  Nom);

        query.bindValue(2,  Prenom);
        query.bindValue(3,Date_naissance  );
        query.bindValue(4, Nombre_Proces_Gagnes_string );
        query.bindValue(5, Numero_telephone_string );

       return  query.exec();
}

QSqlQueryModel* Avocat :: afficherA()
{

QSqlQueryModel* model= new QSqlQueryModel();

model->setQuery("SELECT* FROM avocat ");
 model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
 model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
 model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Naissance"));
 model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Proces gagnes"));
 model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Telephone "));

return model ;

}

bool Avocat ::  supprimerA(int Id_Avocat)
{

    QSqlQuery query;

   query.prepare("DELETE from  avocat where Id_Avocat = :Id_Avocat" ) ;
          query.bindValue(0, Id_Avocat );


         return  query.exec();


}

/*************************************************************/

bool Avocat ::  modifierA()
  {
      QSqlQuery query;
      QString Id_Avocat_string=QString:: number(Id_Avocat);
      QString Numero_telephone_string=QString:: number(Numero_telephone);
      QString Nombre_Proces_Gagnes_string=QString:: number(Nombre_Proces_Gagnes);
      query.prepare(" UPDATE avocat SET NOM=:NOM , PRENOM=:PRENOM , DATE_NAISSANCE=:DATE_NAISSANCE , NOMBRE_PROCES_GAGNES =:NOMBRE_PROCES_GAGNES ,NUMERO_TELEPHONE =:NUMERO_TELEPHONE     WHERE ID_AVOCAT = :ID_AVOCAT" );
      query.bindValue(":NOM", Nom);
      query.bindValue(":PRENOM", Prenom);
      query.bindValue(":DATE_NAISSANCE", Date_naissance);
      query.bindValue(":NOMBRE_PROCES_GAGNES",Nombre_Proces_Gagnes_string);
      query.bindValue(":NUMERO_TELEPHONE", Numero_telephone_string);
      query.bindValue(":ID_AVOCAT",Id_Avocat_string );

      return  query.exec();

/*************************************************************/
}
QSqlQueryModel* Avocat :: chercherA(QString a)
{



   QSqlQueryModel* model= new QSqlQueryModel();


model->setQuery("select * from avocat WHERE (ID_AVOCAT LIKE '%"+a+"%' OR NOM LIKE '%"+a+"%' OR PRENOM LIKE '%"+a+"%' "
              "OR DATE_NAISSANCE LIKE '%"+a+"%') ");

   model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Naissance"));
   model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Proces gagnes"));
   model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Telephone "));

  return model ;

}
/***************************************************/
QSqlQueryModel*  Avocat ::  sort(QString a , QString b)
  {

      QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM avocat ORDER BY "+a+" "+b+" ");

          model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Naissance"));
          model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Proces gagnes"));
          model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Telephone "));



      return model ;


}
QSqlQueryModel* Avocat :: evaluerM( )
{

    QSqlQueryModel *model=new QSqlQueryModel();

   model->setQuery("SELECT * FROM avocat where  NOMBRE_PROCES_GAGNES > 10 and NOMBRE_PROCES_GAGNES <= 15  ");

    model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Proces gagnes"));
    model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Telephone "));

return model ;



}
QSqlQueryModel* Avocat :: evaluerD()
{
    QSqlQueryModel *model=new QSqlQueryModel();

   model->setQuery("SELECT * FROM avocat where  NOMBRE_PROCES_GAGNES <= 10");

    model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Proces gagnes"));
    model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Telephone "));
    return model ;
}
QSqlQueryModel* Avocat :: evaluerE()
{
    QSqlQueryModel *model=new QSqlQueryModel();

   model->setQuery("SELECT * FROM avocat where  NOMBRE_PROCES_GAGNES > 15");

    model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Proces gagnes"));
    model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Telephone "));
    return model ;

}

QSqlQueryModel * Avocat :: afficherA_arduino()
{
    QSqlQueryModel* model= new QSqlQueryModel();

    model->setQuery("SELECT* FROM avocat WHERE ID_AVOCAT = 11822123556 ");
     model->setHeaderData(0, Qt::Horizontal, QObject :: tr("Identifiant"));
     model->setHeaderData(1, Qt::Horizontal, QObject :: tr("Nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject :: tr("Prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject :: tr("Naissance"));
     model->setHeaderData(4, Qt::Horizontal, QObject :: tr("Proces gagnes"));
     model->setHeaderData(5, Qt::Horizontal, QObject :: tr("Telephone "));

    return model ;
}





