#include "connection.h"

Connection::Connection(){}
bool Connection::createconnection()
{
   db=QSqlDatabase::addDatabase("QODBC");
   bool test=false;
   db.setDatabaseName("Gestion_clients");
   db.setUserName("system");
   db.setPassword("yosr2002");

if (db.open()) test=true;
return test;
}

