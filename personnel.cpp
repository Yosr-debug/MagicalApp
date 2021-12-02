#include "personnel.h"
#include <QDebug>
#include <iostream>
#include <list>
#include <QString>

personnel::personnel()
{
     cin="";
     nom="";
     prenom="";
     salaire="";
     poste="";
     adresse="";
     num_tel="";
     age="";

}
personnel::personnel(QString cin,QString nom,QString prenom,QString salaire,QString poste,QString adresse,QString age,QString num_tel){

    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->salaire=salaire;
    this->poste=poste;
    this->adresse=adresse;
    this->age=age;
    this->num_tel=num_tel;

}
void personnel::setcin(QString cin1)
{cin=cin1;
}
void personnel::setnom(QString nom)
{this->nom=nom;}
void personnel::setprenom(QString prenom)
{this->prenom=prenom;}
void personnel::setage(QString age)
{this->age=age;}
void personnel::setsalaire(QString salaire)
{this->salaire=salaire;}
QString personnel::getcin(){return cin;}
QString personnel::getnom(){return nom;}
QString personnel::getprenom(){return prenom;}
QString personnel::getsalaire(){return salaire;}
QString personnel::getposte(){return poste;}
QString personnel::getnumtel(){return num_tel;}
QString personnel::getadresse(){return adresse;}
QString personnel::getage(){return age;}


bool personnel::ajouter()
{
    QSqlQuery query;

    query.prepare("insert into personnel (cin,nom,prenom,salaire,poste,adresse,age,num_tel) VALUES (:cin,:nom,:prenom,:salaire,:poste,:adresse,:age,:num_tel)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":poste",poste);
    query.bindValue(":adresse",adresse);
    query.bindValue(":age",age);
    query.bindValue(":num_tel",num_tel);


      return query.exec();
}

QSqlQueryModel * personnel::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from personnel");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("num_tel"));



    return model;
}
bool personnel::modifier(QString cin,QString salaire,QString nom,QString prenom,QString poste,QString num_tel,QString adresse,QString age)
{
    QSqlQuery query;
    query.prepare("update personnel set cin=:cin,nom=:nom,prenom=:prenom,salaire=:salaire,poste=:poste,num_tel=:num_tel,adresse=:adresse, age=:age where cin=:cin");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":poste",poste);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":adresse",adresse);
    query.bindValue(":age",age);

    return query.exec();
}


bool personnel::supprimer(QString cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM personnel WHERE cin = :cin ");
    query.bindValue(":cin", cin);

    return  query.exec();
}

QSqlQueryModel * personnel::chercher(QString nom,QString salaire,QString poste)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * from personnel where nom like :nom OR salaire like :salaire OR poste like :poste ");
    query.bindValue(":nom",nom);
    query.bindValue(":salaire",salaire);
    query.bindValue(":poste",poste);

    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("num_tel"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("age"));

    return model;
}
QSqlQueryModel* personnel::trie(QString index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select *FROM personnel ORDER BY age  ");
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("num_tel"));



    return model;
}
QSqlQueryModel* personnel::trie_salaire(QString index)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    if(index == 0)
    {
        model->setQuery("select *FROM personnel ORDER BY salaire  ");
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("num_tel"));

    return model;
}

