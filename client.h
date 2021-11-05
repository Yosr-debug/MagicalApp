#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
private:
    int cin,num_tel;
    QString  nom,prenom,adresse_mail;
public:
    void setCin(int );
    void setNom(QString );
    void setPrenom(QString );
    void setAdresse_mail(QString );
    void setNum_tel(int );
    int getCin();
    QString getNom();
    QString getPrenom();
    QString getAdresse_mail();
    int getNum_tel();
    Client();
    Client(int,QString,QString,QString,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
};

#endif // CLIENT_H
