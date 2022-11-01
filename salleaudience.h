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

    /*int getid(){return  id;}
    int getnbplace(){return  nbplace;}
    int getcamenmarche(){return  camenmarche;}
    QString getdispo(){return   dispo;}*/

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
    bool modification(int id,int nbplace,int camenmarche,QString dispo);
};

#endif // SALLEAUDIENCE_H
