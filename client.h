#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>
#include <QDate>

class Client
{
private:
    int cin,num_tel,nbre_visites;
    QString  nom,prenom,adresse_mail,date,image;
public:
    void setCin(int );
    void setNbre_visites(int );
    void setNom(QString );
    void setPrenom(QString );
    void setAdresse_mail(QString );
    void setNum_tel(int );
    void setDate(QString);
    void setImage(QString);
    QString getImage();
    int  getNbre_visites();
    QString getDate();
    int getCin();
    QString getNom();
    QString getPrenom();
    QString getAdresse_mail();
    int getNum_tel();
    Client();
    Client(int,QString,QString,QString,int,int,QString,QString);
    bool validaEmail(QString );
    bool ajouter();
    QSqlQueryModel * afficherCIN();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,int,QString,QString,QString,int,QString,QString);
    QSqlQueryModel * rechercher (const QString &aux);
    QSqlQueryModel * tri(const QString &critere);
    QSqlQueryModel * tricin(QString y);
    QSqlQueryModel * trinom(QString y);
    QSqlQueryModel * triprenom(QString y);
    bool validaCIN(int);
};

#endif // CLIENT_H
