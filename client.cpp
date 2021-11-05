#include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QObject>
Client::Client()
{
    cin=0;
    nom="";
    prenom="";
    adresse_mail="";
    num_tel=0;
}
Client::Client(int x,QString nom,QString prenom,QString adresse,int y)
{
    cin=x;
    this->nom=nom;
    this->prenom=prenom;
    adresse_mail=adresse;
    num_tel=y;
}
void Client::setCin(int n)
{
    cin=n;
}
void Client::setNom(QString n)
{
    nom=n;
}
void Client::setPrenom(QString n)
{
    prenom=n;
}
void Client::setAdresse_mail(QString n)
{
    adresse_mail=n;
}
void Client::setNum_tel(int n)
{
    num_tel=n;
}

int Client::getCin(){return cin;}
QString Client::getPrenom(){return prenom;}
QString Client::getNom(){return nom;};
QString Client::getAdresse_mail(){return adresse_mail;}
int Client::getNum_tel(){return num_tel;}
bool Client::ajouter()
{
    QSqlQuery query;
    QString cin_s= QString::number(cin);
    QString numtel_s= QString::number(num_tel);
          query.prepare("INSERT INTO CLIENT (CIN, NOM, PRENOM, ADRESSE_MAIL , NUM_TEL) "
                        "VALUES (:CIN, :NOM, :PRENOM, :ADRESSE_MAIL, :NUM_TEL)");
          query.bindValue(":CIN",cin_s);
          query.bindValue(":NOM", nom);
          query.bindValue(":PRENOM", prenom);
          query.bindValue(":ADRESSE_MAIL", adresse_mail);
          query.bindValue(":NUM_TEL", numtel_s);
          if (query.lastError().isValid())
              qDebug() << query.lastError();
         return query.exec();

}


 QSqlQueryModel * Client::afficher()
 {  QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM CLIENT");
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse mail"));
          model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(4, Qt::Horizontal,  QObject::tr("Num telephone"));
          model->setHeaderData(2, Qt::Horizontal,  QObject::tr("Prénom"));
     return model;
 }

bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from CLIENT where CIN=:id) ");
    query.bindValue(0,id);
    return query.exec();
}












