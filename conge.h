#ifndef CONGE_H
#define CONGE_H
#include <QString>
#include <QSqlQueryModel>
#include "avocat.h"

class conge
{
public:
    conge();
    conge( int,  QString , QString , QString) ;
    int getId_Avocat ;
    QString getDate_Debut(){return Date_Debut ;}
    QString getDate_Fin() {return Date_Fin;}
    QString getMotif(){return Motif ;}

    void setDate_Debut(QString val){Date_Debut =val ;}
    void setDate_Fin(QString val){Date_Fin =val ;}
    void setMotif(QString val){Motif =val ;}
    bool ajouter_c();
    QSqlQueryModel* afficher_c();



private :
QString Date_Debut ;
QString Date_Fin ;
QString Motif ;
int Id_Avocat ;
};

#endif // CONGE_H
