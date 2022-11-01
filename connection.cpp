#include "connection.h"
#include <QSqlDatabase>

Connection::Connection(){}
bool Connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("test_juridique"); //insérer le nom de la source de ODBC
db.setUserName("system"); //insérer nom de l'utilisateur
db.setPassword("system"); //insérer mot de passe de cet utilisateur
if (db.open()) test=true;
return test;
}
void Connection::closeconnection(){db.close();}
