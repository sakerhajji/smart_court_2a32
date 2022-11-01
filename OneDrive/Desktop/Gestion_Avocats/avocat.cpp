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


int Avocat:: getId_Avocat(){return Id_Avocat ; }
QString Avocat::getNom() { return Nom ; }
QString Avocat:: getPrenom(){ return Prenom ; }
QString Avocat:: getDate_naissance() { return Date_naissance ; }
int Avocat :: getNumero_telephone() { return Numero_telephone ; }
int Avocat :: getNombre_Proces_Gagnes(){return Nombre_Proces_Gagnes ; }

void Avocat ::  setId_Avocat(int Id_Avocat ) {this->Id_Avocat=Id_Avocat ;  }
void Avocat :: setNom(QString Nom){ this->Nom=Nom ; }
void Avocat ::setPrenom(QString Prenom){this->Prenom=Prenom;  }
void Avocat ::setDate_naissance(QString Date_naissance ){this->Date_naissance=Date_naissance; }
void Avocat :: setNumero_telephone(int  Numero_telephone ){ this->Numero_telephone=Numero_telephone ;  }
void Avocat ::setNombre_proces_gagnes(int Nombre_Proces_Gagnes) { this->Nombre_Proces_Gagnes=Nombre_Proces_Gagnes ;  }

bool Avocat:: ajouter()
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

QSqlQueryModel* Avocat :: afficher()
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

bool Avocat ::  supprimer(int Id_Avocat)
{

    QSqlQuery query;

   query.prepare("DELETE from  avocat where Id_Avocat = :Id_Avocat" ) ;
          query.bindValue(0, Id_Avocat );


         return  query.exec();




}

bool Avocat :: modifier (  )
{
QSqlQuery query ;
QString  Id_Avocat_String=QString :: number(Id_Avocat);
QString  Numero_telephone_string=QString:: number(Numero_telephone);
QString  Nombre_Proces_Gagnes_string=QString:: number(Nombre_Proces_Gagnes);

query.prepare(" Update avocat set  Id_Avocat= :Id_Avocat , Nom = :name , Prenom= :Prename , Date_naissance = :birth ,   Numero_telephone = :number , Nombre_Proces_Gagnes= :cases where Id_Avocat= :Id_Avocat  ");
query.bindValue(":Id_Avocat ",Id_Avocat_String  );
query.bindValue(":name ",Nom );
query.bindValue(":Prename ",Prenom);
query.bindValue(":birth ",Date_naissance   );
query.bindValue(":number ",Numero_telephone_string );
query.bindValue(":cases  ", Nombre_Proces_Gagnes_string );





return query.exec();
}


