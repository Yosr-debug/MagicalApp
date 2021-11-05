#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QIntValidator>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditCIN->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->lineEdit_Num_tel->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->tab_clients->setModel(c.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonajouter_clicked()
{
    Client c;
    c.setCin(ui->lineEditCIN->text().toInt());
    c.setPrenom(ui->lineEdit_Prenom->text());
    c.setNom(ui->lineEdit_nom->text());
    c.setAdresse_mail(ui->lineEdit_adress_mail->text());
    c.setNum_tel(ui->lineEdit_Num_tel->text().toInt());
    bool test=c.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("database is open"),
        QObject::tr("Added successfully.\n"
                    "Click cancel to exit."), QMessageBox::Cancel);
        ui->tab_clients->setModel(c.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_pushButton_supprimer_clicked()
{
    Client c1;
    c1.setCin(ui->lineEditCIN_2->text().toInt());
    bool test=c1.supprimer(c1.getCin());
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("database is open"),
        QObject::tr("Deleted successfully.\n"
                    "Click cancel to exit."), QMessageBox::Cancel);
         ui->tab_clients->setModel(c.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                              QObject::tr("Connection failed.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
}
