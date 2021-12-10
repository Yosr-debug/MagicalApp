#ifndef COLLABORATION_H
#define COLLABORATION_H

#include <QString>
#include <QString>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDir>

class Collaboration
{
public:
    Collaboration();
    Collaboration(int,QString,QString,QString,QString,QString);
    bool ajouter_collab();
       QSqlQueryModel * afficher_collab();
       bool supprimer_collab(int);
       bool modifier_collab(int);
       QSqlQueryModel * triercroi();

       QSqlQueryModel * trierdeccroi();
       QSqlQueryModel* recherche(QString);
       int getcodecollab();
              QString getnomcollaborateur(){return nom_collaborateur;};
              QString gettypecollab(){return type_collab;};
              QString getbudget(){return budget;};
              QString getdatedebut(){return datedebut;};
              QString getdatefin(){return datefin;};
              void setcodecollab(int);
              void setnomcollaborateur(QString);
              void settypecollab(QString);
              void setbudget(QString);
              void setdatedebut(QString);
              void setdatefin(QString);

private:
              int code_collab;
              QString nom_collaborateur,type_collab,budget,datedebut,datefin;


};

#endif // COLLABORATION_H
