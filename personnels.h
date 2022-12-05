#ifndef PERSONNELS_H
#define PERSONNELS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class personnels
{
    QString nom,prenom,adresse;
    int  id,age;

public:
    //constructeurs
     personnels(){}
     personnels(int,QString,QString,int,QString);
 //gettters
     QString getnom(){return nom;}
     QString getprenom(){return prenom;}
     QString getadresse(){return adresse;}
     int getid(){return id;}
     int getage(){return age;}

    //setters
     void setnom(QString n){nom=n;}
     void setprenom(QString p){prenom=p;}
     void settypebagage(QString ad){adresse=ad;}
     void setid(int id){this->id=id;}
      void setpoids(int a){this->age=a;}

      //fonctionnalites de bases relatives à l'entité personnels
      bool ajouterp();
      QSqlQueryModel * afficherp();
      bool supprimerp(int);
      bool modifierp();
      void archiverp(int id);
QSqlQueryModel * afficher_historiquep();
QSqlQueryModel*affichertriAZp();
QSqlQueryModel * affichertriZAp();
QSqlQueryModel * rechercherp(QString);
QSqlQueryModel *recherchernomp(QString nom);
int calcul_adressesp(QString adresse,QString var);
QStringList listeadressesp(QString val);

 };

#endif // PERSONNELS_H
