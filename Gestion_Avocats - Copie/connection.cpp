#include "connection.h"
#include<QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Gestion_Avocat");
//test.bd
db.setUserName("Eya");//inserer nom de l'utilisateur
db.setPassword("Eya");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
 return  test;
}

//void Connection:: closeConnection(){db.close();  }
