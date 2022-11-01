#ifndef AVOCAT_H
#define AVOCAT_H

#include <QString>
#include <QSqlQueryModel>
class Avocat
{
public:
    Avocat();
    Avocat( int , QString , QString , QString, int  , int) ;
    int getId_Avocat();
    QString getNom();
    QString getPrenom();
    QString getDate_naissance();
    int getNumero_telephone ();
    int getNombre_Proces_Gagnes();

    void setId_Avocat(int);
    void setNom(QString);
    void setPrenom(QString);
    void setDate_naissance(QString);
    void setNumero_telephone(int);
    void setNombre_proces_gagnes(int);
    bool ajouter();
    bool supprimer(int Id_Avocat );
    QSqlQueryModel* afficher();
    bool modifier ();


private :
    int Id_Avocat , Nombre_Proces_Gagnes, Numero_telephone   ;
    QString Nom , Prenom ,  Date_naissance ;
};
#endif // AVOCAT_H
