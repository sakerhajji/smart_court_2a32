#include "affaire_juridique.h"

affaire_juridique::affaire_juridique()
{
    numcas = "" ;
    cin="" ;
    nom ="" ;
    prenom="" ;
    typecas="" ;
    datecas = "" ;
    dateness ="" ;
    etat="" ;
    sexe="" ;
    metier ="" ;
    nbenfant ="" ;
}

affaire_juridique::~affaire_juridique()
{
    //dtor
}
affaire_juridique::affaire_juridique(QString numcas ,QString cin,QString nom,QString prenom,QString typecas,QString datecas,QString dateness,QString etat,QString sexe,QString metier,QString nbenfant)
{
    this->numcas =numcas ;
    this->cin=cin ;
    this->nom = nom ;
    this->prenom=prenom ;
    this->typecas=typecas ;
    this->datecas = datecas ;
    this->dateness = dateness ;
    this->etat=etat ;
    this->sexe=sexe ;
    this->metier =metier ;
    this->nbenfant =nbenfant ;

}
bool affaire_juridique :: ajouteraffaire ()
{
    QSqlQuery query;

    query.prepare("INSERT INTO AFFAIRE_JURIDIQUE (NUMCAS,CIN,NOM,PRENOM,TYPECAS,DATECAS,DATENESS,ETAT,SEXE,METIER,NBENFANT) "
                        "VALUES (:NUMCAS,:CIN,:NOM,:PRENOM,:TYPECAS,:DATECAS,:DATENESS,:ETAT,:SEXE,:METIER,:NBENFANT)");
          query.bindValue(0,numcas );
          query.bindValue(1,cin);
          query.bindValue(2, nom);
          query.bindValue(3, prenom);
          query.bindValue(4, typecas);
          query.bindValue(5, datecas);
          query.bindValue(6,dateness);
          query.bindValue(7, etat);
          query.bindValue(8, sexe);
          query.bindValue(9, metier);
          query.bindValue(10, nbenfant);

   return  query.exec();
}

QSqlQueryModel*  affaire_juridique ::  afficher ()
{
    QSqlQueryModel* model=new QSqlQueryModel() ;
    model->setQuery("SELECT * FROM AFFAIRE_JURIDIQUE ");
          model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Numero de cas"));
          model->setHeaderData(1, Qt::Horizontal, QObject:: tr ("Cin"));
          model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject:: tr ("Prenom"));
          model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Type cas"));
          model->setHeaderData(5, Qt::Horizontal, QObject:: tr ("Date Cas"));
          model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Date de naissance"));
          model->setHeaderData(7, Qt::Horizontal, QObject:: tr ("Etat"));
          model->setHeaderData(8, Qt::Horizontal, QObject:: tr ("Metier"));
          model->setHeaderData(9, Qt::Horizontal, QObject:: tr ("sexe"));
          model->setHeaderData(10, Qt::Horizontal, QObject:: tr ("Nobre d'enfants"));



    return model ;

}

 bool affaire_juridique :: supprimer_afffaire (QString x )
 {
     QSqlQuery query;
     query.prepare("DELETE FROM   AFFAIRE_JURIDIQUE WHERE NUMCAS = :NUMCAS" );
     query.bindValue(0,x );

     return  query.exec();



 }

  bool affaire_juridique ::  Update_afffaire ( QString x , QString y)
  {
      QSqlQuery query;
      query.prepare(" UPDATE AFFAIRE_JURIDIQUE SET DATECAS=:datecas  WHERE NUMCAS = :numcas" );
      query.bindValue(":datecas",x );
      query.bindValue(":numcas",y );
      return  query.exec();
  }
