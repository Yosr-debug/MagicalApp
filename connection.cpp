#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet2a");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("rinorino9");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}
