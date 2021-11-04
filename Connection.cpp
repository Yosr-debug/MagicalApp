#include "connection.h"

connection::connection()
{

}bool connection::createconnection()
{
   db=QSqlDatabase::addDatabase("QODBC");
   bool test=false;
   db.setDatabaseName("test-bd");
   db.setUserName("system");
   db.setPassword("harrypotter");

if (db.open()) test=true;
return test;
}
