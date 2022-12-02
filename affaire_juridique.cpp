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
    ETAT_CAS="" ;
    sexe="" ;
    metier ="" ;
    nbenfant ="" ;
}

affaire_juridique::~affaire_juridique()
{
    //dtor
}
affaire_juridique::affaire_juridique(QString numcas ,QString cin,QString nom,QString prenom,QString typecas,QString datecas,QString dateness,QString ETAT_CAS,QString sexe,QString metier,QString nbenfant)
{
    this->numcas =numcas ;
    this->cin=cin ;
    this->nom = nom ;
    this->prenom=prenom ;
    this->typecas=typecas ;
    this->datecas = datecas ;
    this->dateness = dateness ;
    this->ETAT_CAS=ETAT_CAS ;
    this->sexe=sexe ;
    this->metier =metier ;
    this->nbenfant =nbenfant ;

}
bool affaire_juridique :: ajouteraffaire ()
{
    QSqlQuery query;

    query.prepare("INSERT INTO AFFAIRE_JURIDIQUE (NUMCAS,CIN,NOM,PRENOM,TYPECAS,DATECAS,DATENESS,ETAT_CAS,SEXE,METIER,NBENFANT) "
                        "VALUES (:NUMCAS,:CIN,:NOM,:PRENOM,:TYPECAS,:DATECAS,:DATENESS,:ETAT_CAS,:SEXE,:METIER,:NBENFANT)");
          query.bindValue(0,numcas );
          query.bindValue(1,cin);
          query.bindValue(2, nom);
          query.bindValue(3, prenom);
          query.bindValue(4, typecas);
          query.bindValue(5, datecas);
          query.bindValue(6,dateness);
          query.bindValue(7, ETAT_CAS);
          query.bindValue(8, sexe);
          query.bindValue(9, metier);
          query.bindValue(10, nbenfant);

   return  query.exec();
}

QSqlQueryModel*  affaire_juridique ::  afficher ()
{
    QSqlQueryModel* model=new QSqlQueryModel() ;
    model->setQuery("SELECT REVERSE (NUMCAS),REVERSE(CIN),REVERSE (NOM),REVERSE (PRENOM),REVERSE(TYPECAS),REVERSE(DATECAS),REVERSE(DATENESS)"
                    ",REVERSE(ETAT_CAS),REVERSE(SEXE),REVERSE(METIER),REVERSE(NBENFANT)   FROM AFFAIRE_JURIDIQUE ");
          model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Numero de cas"));
          model->setHeaderData(1, Qt::Horizontal, QObject:: tr ("Cin"));
          model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject:: tr ("Prenom"));
          model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Type cas"));
          model->setHeaderData(5, Qt::Horizontal, QObject:: tr ("Date Cas"));
          model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Date de naissance"));
          model->setHeaderData(7, Qt::Horizontal, QObject:: tr ("Etat de cas "));
          model->setHeaderData(8, Qt::Horizontal, QObject:: tr ("sexe"));
          model->setHeaderData(9, Qt::Horizontal, QObject:: tr ("Metier"));
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

  bool affaire_juridique ::  Update_afffaire ()
  {
      QSqlQuery query;
      query.prepare(" UPDATE AFFAIRE_JURIDIQUE SET CIN = :CIN , NOM = :NOM , PRENOM = :PRENOM , TYPECAS = :TYPECAS , DATECAS = :DATECAS ,DATENESS = :DATENESS ,ETAT_CAS = :ETAT_CAS , SEXE = :SEXE , METIER = :METIER ,NBENFANT = :NBENFANT  WHERE NUMCAS = :NUMCAS" );

      query.bindValue(":CIN",cin);
      query.bindValue(":NOM", nom);
      query.bindValue(":PRENOM", prenom);
      query.bindValue(":TYPECAS", typecas);
      query.bindValue(":DATECAS", datecas);
      query.bindValue(":DATENESS",dateness);
      query.bindValue(":ETAT_CAS", ETAT_CAS);
      query.bindValue(":SEXE", sexe);
      query.bindValue(":METIER", metier);
      query.bindValue(":NBENFANT", nbenfant);
      query.bindValue(":NUMCAS",numcas );

      return  query.exec();
  }
  QSqlQueryModel*  affaire_juridique ::  chercher (QString a)
  {
      reverse(a.begin(), a.end());

      QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery(" SELECT REVERSE (NUMCAS),REVERSE(CIN),REVERSE (NOM),REVERSE (PRENOM),REVERSE(TYPECAS),REVERSE(DATECAS),REVERSE(DATENESS)"
                          ",REVERSE(ETAT_CAS),REVERSE(SEXE),REVERSE(METIER),REVERSE(NBENFANT) "
                          " from AFFAIRE_JURIDIQUE WHERE (NUMCAS LIKE '%"+a+"%' OR CIN LIKE '%"+a+"%' OR PRENOM LIKE '%"+a+"%' OR NOM LIKE '%"+a+"%' "
              "OR TYPECAS LIKE '%"+a+"%' OR DATECAS LIKE '%"+ a +"%' OR DATENESS LIKE '%"+a+"%' OR ETAT_CAS LIKE '%"+a+"%' "
              "OR SEXE LIKE '%"+a+"%' OR METIER LIKE '%"+a+"%' OR NBENFANT LIKE '%"+a+"%'  ) ");

            model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Numero de cas"));
            model->setHeaderData(1, Qt::Horizontal, QObject:: tr ("Cin"));
            model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Nom"));
            model->setHeaderData(3, Qt::Horizontal, QObject:: tr ("Prenom"));
            model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Type cas"));
            model->setHeaderData(5, Qt::Horizontal, QObject:: tr ("Date Cas"));
            model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Date de naissance"));
            model->setHeaderData(7, Qt::Horizontal, QObject:: tr ("Etat de Cas"));
            model->setHeaderData(8, Qt::Horizontal, QObject:: tr ("sexe"));
            model->setHeaderData(9, Qt::Horizontal, QObject:: tr ("Metier"));
            model->setHeaderData(10, Qt::Horizontal, QObject:: tr ("Nobre d'enfants"));



      return model ;

  }



  QSqlQueryModel*  affaire_juridique ::  sortname(QString a , QString b)
  {

      QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("  SELECT REVERSE (NUMCAS),REVERSE(CIN),REVERSE (NOM),REVERSE (PRENOM),REVERSE(TYPECAS),REVERSE(DATECAS),REVERSE(DATENESS)"
                          ",REVERSE(ETAT_CAS),REVERSE(SEXE),REVERSE(METIER),REVERSE(NBENFANT) FROM AFFAIRE_JURIDIQUE ORDER BY "+a+" "+b+"  ");

            model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Numero de cas"));
            model->setHeaderData(1, Qt::Horizontal, QObject:: tr ("Cin"));
            model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Nom"));
            model->setHeaderData(3, Qt::Horizontal, QObject:: tr ("Prenom"));
            model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Type cas"));
            model->setHeaderData(5, Qt::Horizontal, QObject:: tr ("Date Cas"));
            model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Date de naissance"));
            model->setHeaderData(7, Qt::Horizontal, QObject:: tr ("Etat de cas "));
            model->setHeaderData(8, Qt::Horizontal, QObject:: tr ("sexe"));
            model->setHeaderData(9, Qt::Horizontal, QObject:: tr ("Metier"));
            model->setHeaderData(10, Qt::Horizontal, QObject:: tr ("Nombre d'enfants"));



      return model ;

  }
  void affaire_juridique:: cryptage ()
  {
      reverse(numcas.begin(), numcas.end());
      reverse(cin.begin(), cin.end());
      reverse(nom.begin(), nom.end());
      reverse(prenom.begin(), prenom.end());
      reverse(typecas.begin(), typecas.end());
      reverse(datecas.begin(), datecas.end());
      reverse(dateness.begin(), dateness.end());
      reverse(ETAT_CAS.begin(), ETAT_CAS.end());
      reverse(sexe.begin(), sexe.end());
      reverse(metier.begin(), metier.end());
      reverse(nbenfant.begin(), nbenfant.end());

  }
   bool affaire_juridique :: Update_cas ()
   {
       QSqlQuery query;
       query.prepare(" UPDATE AFFAIRE_JURIDIQUE SET ETAT_CAS = :ETAT_CAS   WHERE NUMCAS = :NUMCAS" );
       query.bindValue(":ETAT_CAS", ETAT_CAS);
       query.bindValue(":NUMCAS",numcas );
       return query.exec();
   }


