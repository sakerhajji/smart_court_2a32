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
    int id;
    int nbplace;
    int camenmarche;
    QString dispo;

public:
    salleaudience();
    salleaudience(int,int,int,QString);

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
    QSqlQueryModel*recherche(QString id);



};


#endif // SALLEAUDIENCE_H
