#ifndef JUGE_H
#define JUGE_H
#include<QString>
#include<QSqlQueryModel>
#include <QMessageBox>


class Juge
{
public:
    Juge();
    Juge(QString,QString,QString,int,int);
    QString getcin();
    QString getnom();
    QString getprenom();
    int getnum_bureau();
    int getnb_process_gagner();
    void setcin(QString);
    void setnom(QString);
    void setprenom(QString);
    void setnum_bureau(int);
    void setnb_process_gagner(int);
    bool ajouter();
    QSqlQueryModel*  afficher(int);
    bool supprimer(QString);
    bool modifier();
    bool chercher(QString);
    QSqlQueryModel*  sort_decroissant();
    QSqlQueryModel*  sort_croissant();
    QSqlQueryModel*  chercher2(QString a) ;
    void notifcation();
   QSqlQueryModel* affichercalendrier(QDate);







private:
    QString cin_j,nom,prenom;
    int num_bureau,nb_process_gagner;
};

#endif // JUGE_H
