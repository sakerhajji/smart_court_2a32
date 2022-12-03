#ifndef SALLEAUDIENCE_H
#define SALLEAUDIENCE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>

class salleaudience
{
private:
    int ID_SALLE;
    int NOMBRE_PLACES_TOTAL;
    int NOMBRES_CAMER_ACTIVEES;
    QString DISPONIBILTE;

public:
    SALLE_AUDIENCE();
    SALLE_AUDIENCE(int,int,int,QString);

    QStringList listedispo(QString var) ;
   int calcul_dispo(QString adresse,QString val);
    int getid();
    int getnbplace();
    int getcamenmarche();
    QString getdispo();

    void setid(int);
    void setnbplace(int);
    void setcamenmarche(int);
    void setdispo(QString);

    bool ajout();
    bool suppression(int);
    QSqlQueryModel * affichage();
    bool modification();
    QSqlQueryModel* trie();
    QSqlQueryModel* trie2();
    QSqlQueryModel*recherche(QString ID_SALLE);



};


#endif // SALLEAUDIENCE_H
