#ifndef AFFAIRE_JURIDIQUE_H
#define AFFAIRE_JURIDIQUE_H
#include<QString>
#include <iostream>
#include <QSqlQuery>
#include <QtDebug>
#include <QApplication>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QObject>


using namespace std;

class affaire_juridique
{
public:
    affaire_juridique();
    affaire_juridique(QString numcas,QString cin,QString nom,QString prenom,QString typecas,QString datecas,QString dateness,QString ETAT_CAS,QString sexe,QString metier,QString nbenfant);
    virtual ~affaire_juridique();

    QString Getnumcas()
    {
        return numcas;
    }
    void Setnumcas(QString val)
    {
        numcas = val;
    }
    QString Getcin()
    {
        return cin;
    }
    void Setcin(QString val)
    {
        cin = val;
    }
    QString Getnom()
    {
        return nom;
    }
    void Setnom(QString val)
    {
        nom = val;
    }
    QString Getprenom()
    {
        return prenom;
    }
    void Setprenom(QString val)
    {
        prenom = val;
    }
    QString Gettypecas()
    {
        return typecas;
    }
    void Settypecas(QString val)
    {
        typecas = val;
    }
    QString Getdatecas()
    {
        return datecas;
    }
    void Setdatecas(QString val)
    {
        datecas = val;
    }
    QString Getdateness()
    {
        return dateness;
    }
    void Setdateness(QString val)
    {
        dateness = val;
    }
    QString GetETAT_CAS()
    {
        return ETAT_CAS;
    }
    void SetETAT_CAS(QString val)
    {
        ETAT_CAS = val;
    }
    QString Getsexe()
    {
        return sexe;
    }
    void Setsexe(QString val)
    {
        sexe = val;
    }
    QString Getmetier()
    {
        return metier;
    }
    void Setmetier(QString val)
    {
        metier = val;
    }
    QString Getnbenfant()
    {
        return nbenfant;
    }
    void Setnbenfant(QString val)
    {
        nbenfant = val;
    }
    bool ajouteraffaire () ;
    QSqlQueryModel * afficher () ;
    bool supprimer_afffaire ( QString x) ;
    bool Update_afffaire () ;
    QSqlQueryModel * chercher (QString) ;
    QSqlQueryModel * sortname (QString, QString) ;
    void cryptage () ;
    bool Update_cas () ;



protected:

private:
    QString numcas;
    QString cin;
    QString nom;
    QString prenom;
    QString typecas;
    QString datecas;
    QString dateness;
    QString ETAT_CAS;
    QString sexe;
    QString metier;
    QString nbenfant;
};

#endif // AFFAIRE_JURIDIQUE_H
