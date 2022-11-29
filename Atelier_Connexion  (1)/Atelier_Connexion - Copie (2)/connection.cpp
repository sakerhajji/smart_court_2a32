#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projetA32");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("yasmine15");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
