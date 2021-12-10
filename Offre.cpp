#include "Offre.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QrCode.hpp>

Offre::Offre()
{
    this->id_off="";
    this->nom_off="";
    this->cin=0;
    this->date_off="";
    this->duree="";
}
Offre::Offre(QString id_off,QString nom_off,int cin,QString date_off,QString duree)
{
    this->id_off=id_off;
    this->nom_off=nom_off;
     this->cin=cin;
    this->date_off=date_off;
    this->duree=duree;



}
bool Offre::ajouter_Off()
{
    QSqlQuery query;
    query.prepare("INSERT INTO offres (id_off,date_off,cin,duree,nom_off) VALUES (:id_off,:date_off,:cin,:duree,:nom_off)");
    query.bindValue(":id_off",id_off);
    query.bindValue(":date_off",date_off);
    query.bindValue(":cin",cin);
    query.bindValue(":duree",duree);
    query.bindValue(":nom_off",nom_off);
    return query.exec();
}
QSqlQueryModel * Offre::afficher_Off()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from Offres");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_off"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom_off"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_off"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));
        return model;
}
bool Offre::modifier_Off(QString id_off,QString nom_off,QString date_off,QString duree)
{
    QSqlQuery query;
    query.prepare("UPDATE offres SET id_off = :id_off,nom_off = :nom_off,date_off = :date_off,duree = :duree  WHERE id_off= :id_off ");
    query.bindValue(":id_off",id_off);
    query.bindValue(":nom_off",nom_off);
    query.bindValue(":date_off",date_off);
    query.bindValue(":duree",duree);
    return    query.exec();
}
bool Offre::supprimer_Off(QString idd)
{
    QSqlQuery query;

    query.prepare("Delete from offres where id_off = :id ");
    query.bindValue(":id", idd);
    return    query.exec();
}

QSqlQueryModel * Offre::rechercher(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM offres where ID_OFF like '%"+a+"%' ||'%' OR DATE_OFF like '%"+a+"%' ||'%' OR CIN like '%"+a+"%' ||'%' OR DUREE like '%"+a+"%'");
    query.bindValue(":id",a);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_off"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_off"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));
    return model;
}

QSqlQueryModel* Offre::tri()
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT* FROM offres ORDER BY DATE_OFF");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_off"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_off"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("duree"));

    return model;
}
