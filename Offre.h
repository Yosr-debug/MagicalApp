#ifndef OFFRE_H
#define OFFRE_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>


class Offre
{
private:
    QString id_off;
    QString nom_off;
    int cin;
    QString date_off;
    QString duree;



public:
    Offre();
    Offre(QString, QString, int, QString, QString);

    bool ajouter_Off();
    QSqlQueryModel * afficher_Off();

    bool supprimer_Off(QString);

    bool modifier_Off(QString,QString,QString, QString);

    QSqlQueryModel * rechercher(QString);

    QSqlQueryModel* tri();


};
#endif //
