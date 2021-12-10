#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include "collaboration.h"
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QEventTransition>
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>

namespace Ui {
class MainWindow;
}
class QSystemTrayIcon ;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
       ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();


    void on_pushButton_ajoutercoll_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_dateEdit_debut_userDateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
     QSystemTrayIcon *mysystem;
     Collaboration tempcollab;
};

#endif // MAINWINDOW_H
