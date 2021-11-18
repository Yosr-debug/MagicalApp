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
    date="";
    nbre_visites=0;
    image="";
}
Client::Client(int x,QString nom,QString prenom,QString adresse,int y,int n,QString s,QString ima)
{
    cin=x;
    this->nom=nom;
    this->prenom=prenom;
    adresse_mail=adresse;
    num_tel=y;
    nbre_visites=n;
    date=s;
    image=ima;
}
void Client::setImage(QString n)
{
    image=n;
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
void Client::setDate(QString n)
{
    date=n;
}
void Client::setNbre_visites(int  n)
{
    nbre_visites=n;
}
QString Client::getImage(){return image;}
int Client::getCin(){return cin;}
int Client::getNbre_visites(){return nbre_visites;}
QString Client::getPrenom(){return prenom;}
QString Client::getDate(){return date;}
QString Client::getNom(){return nom;};
QString Client::getAdresse_mail(){return adresse_mail;}
int Client::getNum_tel(){return num_tel;}

bool Client::validaEmail(QString emai)
{
    ;
    bool test = true;

    qDebug() << emai;
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    if(!regex.match(emai).hasMatch())
    {
        test = false;
    }

    return test;
}

bool Client::validaCIN(int Cin)
{
    ;
    bool test = true;
    QString cin_s= QString::number(Cin);
    qDebug() << cin_s;
    QRegularExpression regex("[0-9]{8}$");

    if(!regex.match(cin_s).hasMatch())
    {
        test = false;
    }

    return test;
}

bool Client::ajouter()
{
    QSqlQuery query;
    QString cin_s= QString::number(cin);
    QString numtel_s= QString::number(num_tel);
    QString nbre= QString::number(nbre_visites);
    QString nbre_visites;
          query.prepare("INSERT INTO CLIENT (CIN, NOM, PRENOM,DATE_DE_NAISSANCE, ADRESSE_MAIL , NUM_TEL,NOMBRE_VISITES, IMAGE) "
                        "VALUES (:CIN, :NOM, :PRENOM, :DATE_DE_NAISSANCE, :ADRESSE_MAIL, :NUM_TEL, :NOMBRE_VISITES, :IMAGE)");
          query.bindValue(":CIN",cin_s);
          query.bindValue(":NOM", nom);
          query.bindValue(":PRENOM", prenom);
          query.bindValue(":DATE_DE_NAISSANCE", date);
          query.bindValue(":ADRESSE_MAIL", adresse_mail);
          query.bindValue(":NUM_TEL", numtel_s);
          query.bindValue(":NOMBRE_VISITES", nbre);
          query.bindValue(":IMAGE", image);
          if (query.lastError().isValid())
              qDebug() << query.lastError();
         return query.exec();

}
/*
QSqlQueryModel * Client::afficherCIN()
{  QSqlQueryModel *model=new QSqlQueryModel();
         model->setQuery("SELECT CIN FROM CLIENT");
         model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
    return model;
}*/

 QSqlQueryModel * Client::afficher()
 {  QSqlQueryModel *model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM CLIENT");
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse mail"));
          model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
          model->setHeaderData(5, Qt::Horizontal,  QObject::tr("Num téléphone"));
          model->setHeaderData(2, Qt::Horizontal,  QObject::tr("Prénom"));
          model->setHeaderData(6, Qt::Horizontal,  QObject::tr("Nombre de visites"));
          model->setHeaderData(7, Qt::Horizontal,  QObject::tr("Path image"));
     return model;
 }

bool Client::supprimer(int id)
{
    QSqlQuery query;
    QString id_s= QString::number(id);
    query.prepare("Delete from CLIENT where CIN=:id");
    query.bindValue(":id",id_s);
    return query.exec();
}


bool Client::modifier(int cin,int num_tel,QString nom,QString prenom,QString mail,int  nbre_visites,QString date,QString image)
{
    QSqlQuery query;
    QString id_string= QString::number(cin);
    QString num_tel_string= QString::number(num_tel);
    query.prepare("update CLIENT set CIN=:cin,NOM=:nom,PRENOM=:prenom,DATE_DE_NAISSANCE=:date,ADRESSE_MAIL=:mail,NUM_TEL=:num_tel,NOMBRE_VISITES=:nbre_visites, IMAGE=:image  where CIN=:cin");
    query.bindValue(":cin",id_string);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",mail);
    query.bindValue(":num_tel",num_tel_string);
    query.bindValue(":nbre_visites",nbre_visites);
    query.bindValue(":date",date);
    query.bindValue(":image",image);
    return query.exec();
}
QSqlQueryModel * Client::rechercher (const QString &aux)

{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from CLIENT where ((CIN || NOM || PRENOM || DATE_DE_NAISSANCE || ADRESSE_MAIL || NUM_TEL || NOMBRE_VISITES) LIKE '%"+aux+"%')");
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse mail"));
    model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(5, Qt::Horizontal,  QObject::tr("Num telephone"));
    model->setHeaderData(2, Qt::Horizontal,  QObject::tr("Prénom"));
    model->setHeaderData(6, Qt::Horizontal,  QObject::tr("Nombre de visites"));


    return model;
}

QSqlQueryModel *  Client::tri(const QString &critere)
{
    QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("select * from CLIENT order by "+critere+"");
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse mail"));
   model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
   model->setHeaderData(5, Qt::Horizontal,  QObject::tr("Num telephone"));
   model->setHeaderData(2, Qt::Horizontal,  QObject::tr("Prénom"));
   model->setHeaderData(6, Qt::Horizontal,  QObject::tr("Nombre de visites"));
    return model;
}


QSqlQueryModel * Client::tricin(QString y)
{



    QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM CLIENT ORDER BY CIN"+y);
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse mail"));
         model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
         model->setHeaderData(5, Qt::Horizontal,  QObject::tr("Num telephone"));
         model->setHeaderData(2, Qt::Horizontal,  QObject::tr("Prénom"));
         model->setHeaderData(6, Qt::Horizontal,  QObject::tr("Nombre de visites"));

    return  model;



}
QSqlQueryModel * Client::trinom(QString y)
{
    QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM CLIENT ORDER BY Nom"+y);
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse mail"));
         model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
         model->setHeaderData(5, Qt::Horizontal,  QObject::tr("Num telephone"));
         model->setHeaderData(2, Qt::Horizontal,  QObject::tr("Prénom"));
         model->setHeaderData(6, Qt::Horizontal,  QObject::tr("Nombre de visites"));

    return  model;
}
QSqlQueryModel * Client::triprenom(QString y)
{
    QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM CLIENT ORDER BY PRENOM"+y);
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse mail"));
         model->setHeaderData(0, Qt::Horizontal,  QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
         model->setHeaderData(5, Qt::Horizontal,  QObject::tr("Num telephone"));
         model->setHeaderData(2, Qt::Horizontal,  QObject::tr("Prénom"));
         model->setHeaderData(6, Qt::Horizontal,  QObject::tr("Nombre de visites"));

    return  model;
}




