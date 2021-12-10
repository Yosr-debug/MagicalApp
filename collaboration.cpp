#include "collaboration.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Collaboration::Collaboration()
{
    code_collab=0;
    nom_collaborateur="";
    type_collab="";
    budget="";
    datedebut="";
    datefin="";
}

Collaboration::Collaboration(int c,QString n,QString p,QString d,QString l,QString e)
{
    code_collab=c;
    nom_collaborateur=n;
    type_collab=p;
    budget=d;
    datedebut=l;
    datefin=e;

}
bool Collaboration::ajouter_collab()
{
    QSqlQuery query;
    QString code_collabs=QString::number(code_collab);
    query.prepare("INSERT INTO COLLAB(CODE_COLLAB, NOM_COLLABORATEUR, TYPE_COLLAB, BUDGET, DATEDEBUT, DATEFIN)"
                  "VALUES(:code_collab, :nom_collaborateur, :type_collab, :budget, :datedebut, :datefin)");

    query.bindValue(":code_collab",code_collabs);
    query.bindValue(":nom_collaborateur",nom_collaborateur);
    query.bindValue(":type_collab",type_collab);
    query.bindValue(":budget",budget);
    query.bindValue(":datedebut",datedebut);
    query.bindValue(":datefin",datefin);

    return query.exec();
}
QSqlQueryModel * Collaboration::afficher_collab()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Collab");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("CODE_COLLAB"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("NOM_COLLABORATEUR"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("TYPE_COLLAB"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("BUDGET"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("DATEDEBUT"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("DATEFIN"));
    return model;
}
bool Collaboration::supprimer_collab(int idc)
 {
     QSqlQuery query;
     QString res=QString::number(idc);
     query.prepare("delete from COLLAB where CODE_COLLAB= :id");
     query.bindValue(":id",res);
     return query.exec();
 }

 bool Collaboration::modifier_collab(int idd) //modifier collab
 {
     QSqlQuery query;
     QString res=QString::number(idd);
     query.prepare("Update COLLAB set CODE_COLLAB = :id , NOM_COLLABORATEUR = :nom_collaborateur , TYPE_COLLAB = :type_collab , BUDGET = :budget , DATEDEBUT = :datedebut , DATEFIN = :datefin  where code_collab = :id ");
     query.bindValue(":id", res);
     query.bindValue(":code_collab",code_collab);
     query.bindValue(":nom_collaborateur",nom_collaborateur);
     query.bindValue(":type_collab",type_collab);
     query.bindValue(":budget",budget);
     query.bindValue(":datedebut",datedebut);
     query.bindValue(":datefin",datefin);

     return query.exec();
 }
 QSqlQueryModel *Collaboration::recherche(QString code_collab)
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from COLLAB where code_collab LIKE '"+code_collab+"%' or nom_collaborateur LIKE '"+code_collab+"%' or type_collab LIKE '"+code_collab+"%'");


        model->setHeaderData(0, Qt::Horizontal, QObject::tr("CODE COLLABORATEUR"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM COLLAB"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE COLLAB"));

    return model;
        }
  QSqlQueryModel *Collaboration::triercroi() //ml A-Z NOM
  {
      QSqlQuery * q = new  QSqlQuery ();
             QSqlQueryModel * model = new  QSqlQueryModel ();
             q->prepare("SELECT * FROM collab order by NOM_COLLABORATEUR ASC");
             q->exec();
             model->setQuery(*q);
             return model;

  }
  QSqlQueryModel *Collaboration::trierdeccroi() //ml A-Z NOM
  {
      QSqlQuery * q = new  QSqlQuery ();
             QSqlQueryModel * model = new  QSqlQueryModel ();
             q->prepare("SELECT * FROM collab order by NOM_COLLABORATEUR DESC");
             q->exec();
             model->setQuery(*q);
             return model;
  }
