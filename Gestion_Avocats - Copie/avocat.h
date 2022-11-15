#ifndef AVOCAT_H
#define AVOCAT_H
#include <QString>
#include <QSqlQueryModel>
//#include <bits/stdc++.h>
//using namespace std ;
class Avocat
{
public:
    Avocat();
    Avocat( int , QString , QString , QString, int  , int) ;
    //int getId_Avocat(){return Id_Avocat ;}
    QString getNom(){return Nom ;}
    QString getPrenom() {return Prenom ;}
    QString getDate_naissance(){return Date_naissance ;}
    int getNumero_telephone (){return Numero_telephone ;}
    int getNombre_Proces_Gagnes(){return Nombre_Proces_Gagnes ;}

    void setId_Avocat(int val ) {Id_Avocat =val ;}
    void setNom(QString val){Nom =val ;}
    void setPrenom(QString val){Prenom =val ;}
    void setDate_naissance(QString val){Date_naissance =val ;}
    void setNumero_telephone(int val){Numero_telephone =val ;}
    void setNombre_proces_gagnes(int val ){Nombre_Proces_Gagnes =val ;}
    bool ajouter();
    bool supprimer(int Id_Avocat );
    QSqlQueryModel* afficher();
    bool  modifier () ;
    QSqlQueryModel*  chercher(QString a  );
    QSqlQueryModel*  sort(QString a , QString b) ;
    QSqlQueryModel*  evaluerD();
    QSqlQueryModel*  evaluerM();
    QSqlQueryModel*  evaluerE();

private :
    int Id_Avocat , Nombre_Proces_Gagnes, Numero_telephone   ;
    QString Nom , Prenom ,  Date_naissance ;
};
#endif // AVOCAT_H
