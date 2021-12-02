#ifndef PERSONNEL_H
#define PERSONNEL_H

#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class personnel
{
public:
    personnel();
    personnel(QString cin,QString salaire,QString nom,QString prenom,QString poste,QString num_tel,QString Adresse,QString age );

     QString getcin();
     QString getnom();
     QString getprenom();
     QString getsalaire();
     QString getposte();
     QString getnumtel();
     QString getadresse();
     QString getage();
     void setcin(QString);
     void setnom(QString);
     void setprenom(QString);
     void setadresse(QString);
     void setsalaire(QString);
     void setposte(QString);
     void setnumtel(QString);
     void setage(QString);

     bool modifier(QString,QString,QString,QString,QString,QString,QString,QString);
      bool ajouter();
      QSqlQueryModel * afficher();
      bool supprimer(QString);
      QSqlQueryModel *chercher(QString nom,QString salaire,QString poste);

      QSqlQueryModel* trie(QString);
      QSqlQueryModel* trie_salaire(QString index);
      void on_QRcodecom_pressed();

 private :
    QString cin;
    QString nom ;
    QString prenom;
    QString poste;
    QString adresse;
    QString salaire;
    QString num_tel;
    QString age;

};

#endif // PERSONNEL_H
