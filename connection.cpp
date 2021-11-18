#include "connection.h"

Connection::Connection(){}
bool Connection::createconnection()
{
   db=QSqlDatabase::addDatabase("QODBC");
   bool test=false;
   db.setDatabaseName("Gestion_clients");
   db.setUserName("yosr");// yosr
   db.setPassword("esprit18");//esprit18

if (db.open()) test=true;
return test;
}

