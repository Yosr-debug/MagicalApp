#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QIntValidator>
#include <QSqlError>
#include <QMessageBox>
#include <QApplication>
#include <QStringList>
#include <QPdfWriter>
#include <QPainter>
#include <QTextStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QLabel>
#include <QtPrintSupport/QPrintDialog>
#include <QPieSeries>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditCIN->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->lineEdit_Num_tel->setValidator( new QIntValidator(00000000, 99999999, this));
    ui->tab_clients->setModel(c.afficher());
    ui->lineEdit_adress_mail->setInputMask("NNNNNNNNNN@AAAAAA.AAA");
    /*QStringList liste;
    liste<<"0"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10";
    ui->comboBoxNbre_visites->addItems(liste);*/
    ui->lineEdit_nom->setInputMask("AAAAAAAAAAAA");
    ui->lineEdit_Prenom->setInputMask("AAAAAAAAAAAA");
    ui->lineEditCIN_chercher->setPlaceholderText(QString("Chercher"));
    ui->lineEdit_path_image->setPlaceholderText(QString("C:\\Users\\yosra\\OneDrive\\Desktop"));
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
    c.setNbre_visites(ui->spinBox_nbre_visite->text().toInt());
    c.setDate(ui->dateEdit->text());
    c.setImage(ui->lineEdit_path_image->text());
    QPixmap p(c.getImage());
    ui->label->setPixmap(p);
    ui->label->show();
    //QString fileName="C:\\Users\\yosra\\OneDrive\\Desktop\\GestionClients\\Photo.jpg";

    bool test1=c.validaEmail( c.getAdresse_mail());
    bool test2=c.validaCIN(c.getCin());
    if(test2==false)
       { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                        QObject::tr("Wrong CIN.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);}
    if(test1==false)
       { QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                        QObject::tr("Wrong Email adress.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);}
    if(test1 && test2)
    {
        bool test=c.ajouter();
    if(test)
      {
        QMessageBox::information(nullptr,QObject::tr(""),
        QObject::tr("Added successfully.\n"
                    "Click cancel to exit."), QMessageBox::Cancel);
        ui->tab_clients->setModel(c.afficher());

        QString res="";
        ui->lineEditCIN->setText(res);
        ui->lineEdit_nom->setText(res);
        ui->lineEdit_Prenom->setText(res);
        ui->lineEdit_Num_tel->setText(res);
        ui->lineEdit_adress_mail->setText(res);

      }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("Error! \n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);

    }

}


void MainWindow::on_pushButton_supprimer_clicked()
{
    Client c1;
    c1.setCin(ui->lineEditCIN->text().toInt());
    bool test=c1.supprimer(c1.getCin());
    if(test)
    {
        QMessageBox::information(nullptr,QObject::tr("Database is open"),
        QObject::tr("Deleted successfully.\n"
                    "Click cancel to exit."), QMessageBox::Cancel);
         ui->tab_clients->setModel(c.afficher());
         QString res="";
         ui->lineEditCIN->setText(res);
         ui->lineEdit_nom->setText(res);
         ui->lineEdit_Prenom->setText(res);
         ui->lineEdit_Num_tel->setText(res);
         ui->lineEdit_adress_mail->setText(res);
         ui->Ajout_nbre_visite->setText(res);
         ui->lineEdit_path_image->setText(res);
         QPixmap p("C:\\Users\\yosra\\OneDrive\\Desktop\\GestionClients\\image_init.png");
         ui->label->setPixmap(p);
         ui->label->show();
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("Error! \n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);

}


void MainWindow::on_tab_clients_clicked(const QModelIndex &index) //supprimer
{
        int cin=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),0)).toInt();
        QString res=QString::number(cin);
        ui->lineEditCIN->setText(res);
        int num_tel=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),5)).toInt();
        QString res1=QString::number(num_tel);
        ui->lineEdit_Num_tel->setText(res1);
        QVariant nom=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),1));
        QString resN=nom.toString();
        ui->lineEdit_nom->setText(resN);
        QVariant prenom=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),2));
        QString resP=prenom.toString();
        ui->lineEdit_Prenom->setText(resP);
        QVariant mail=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),4));
        QString resM=mail.toString();
        ui->lineEdit_adress_mail->setText(resM);
        int nbre_visites=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),6)).toInt();
        ui->spinBox_nbre_visite->setValue(nbre_visites);
        QVariant date=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),3));
        QString resD=date.toString();
        QDate Date = QDate::fromString(resD,"dd/MM/yyyy");
        ui->dateEdit->setDate(Date);
        QVariant image=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),7));
        QString resI=image.toString();
        ui->lineEdit_path_image->setText(resI);
        QPixmap p(resI);
        ui->label->setPixmap(p);
        ui->label->show();
}

void MainWindow::on_tab_clients_doubleClicked(const QModelIndex &index)
{
    int cin=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),0)).toInt();
    QString res=QString::number(cin);
    ui->lineEditCIN_fiche->setText(res);
    int num_tel=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),5)).toInt();
    QString res1=QString::number(num_tel);
    ui->lineEdit_Num_tel_fiche->setText(res1);
    QVariant nom=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),1));
    QString resN=nom.toString();
    ui->lineEdit_nom_fiche->setText(resN);
    QVariant prenom=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),2));
    QString resP=prenom.toString();
    ui->lineEdit_Prenom_fiche->setText(resP);
    QVariant mail=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),4));
    QString resM=mail.toString();
    ui->lineEdit_adress_mail_fiche->setText(resM);
    int nbre_visites=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),6)).toInt();
    ui->spinBox_nbre_visite_fiche->setValue(nbre_visites);
    QVariant date=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),3));
    QString resD=date.toString();
    QDate Date = QDate::fromString(resD,"dd/MM/yyyy");
    ui->dateEdit_fiche->setDate(Date);
    QVariant image=ui->tab_clients->model()->data(ui->tab_clients->model()->index(ui->tab_clients->currentIndex().row(),7));
    QString resI=image.toString();
    ui->lineEdit_image->setText(resI);
    QPixmap p(resI);
    ui->label_2->setPixmap(p);
    ui->label_2->show();
}


void MainWindow::on_pushButtonModifier_clicked()
{
    int cin = ui->lineEditCIN->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString prenom = ui->lineEdit_Prenom->text();
    int num_tel = ui->lineEdit_Num_tel->text().toInt();
    QString mail =ui->lineEdit_adress_mail->text();
    int  nbre_visites=ui->spinBox_nbre_visite->text().toInt();
    QString date=ui->dateEdit->text();
    QString image=ui->lineEdit_path_image->text();
    QPixmap p(c.getImage());
    ui->label->setPixmap(p);
    ui->label->show();
    Client c(cin,nom,prenom,mail,num_tel,nbre_visites,date,image);
    if(cin==0)
       {
              QMessageBox::information(nullptr,QObject::tr("Ajouter un client"),QObject::tr("Merci de remplir les champs"),QMessageBox::Ok);
       }
     else
            {bool test1=c.validaEmail( c.getAdresse_mail());
        if(test1)

      { bool test=c.modifier(cin,num_tel,nom,prenom,mail,nbre_visites,date,image);
       if(test)
        {
                   QMessageBox::information(nullptr, QObject::tr("modifier un client "),
                                            QObject::tr("Modified successfully.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tab_clients->setModel(c.afficher());
       QString res="";
       ui->lineEditCIN->setText(res);
       ui->lineEdit_nom->setText(res);
       ui->lineEdit_Prenom->setText(res);
       ui->lineEdit_Num_tel->setText(res);
       ui->lineEdit_adress_mail->setText(res);
        ui->Ajout_nbre_visite->setText(res);
        ui->lineEdit_path_image->setText(res);
       }
               else
                  { QMessageBox::critical(nullptr, QObject::tr("Modifier un client "),
                                         QObject::tr("Error !\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
                   }

    }
     else {QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                      QObject::tr("Wrong Email adress.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
                }

}
}



void MainWindow::on_lineEditCIN_chercher_textChanged()
{

    Client c;
    QString A=ui->lineEditCIN_chercher->text();
    ui->tab_clients->setModel(c.rechercher(A));
    if(A=="")
            ui->tab_clients->setModel(c.afficher());
}


void MainWindow::on_pushButtonTri_clicked()
{
    /*Client c;
    QString A=ui->lineEdit_tri->text();
    ui->tab_clients->setModel(c.tri(A));*/

    QString y;
          if(ui->radioButtonCIN->isChecked())
          {y=" ";

            ui->tab_clients->setModel(c.tricin(y));
    }else if (ui->radioButtonNom->isChecked()) {
              y=" ";

                ui->tab_clients->setModel(c.trinom(y));


    }else if (ui->radioButtonPrenom->isChecked())
          {
              y=" ";

                ui->tab_clients->setModel(c.triprenom(y));
          }
}

void MainWindow::on_pushButtonEffacer_clicked()
{
    QString res="";
    ui->lineEditCIN->setText(res);
    ui->lineEdit_nom->setText(res);
    ui->lineEdit_Prenom->setText(res);
    ui->lineEdit_Num_tel->setText(res);
    ui->lineEdit_adress_mail->setText(res);
    ui->spinBox_nbre_visite->setValue(0);
    QString date_string = "01/01/2000";
    QDate Date = QDate::fromString(date_string,"dd/MM/yyyy");
    ui->dateEdit->setDate(Date);
    ui->lineEdit_path_image->setText(res);
}



void MainWindow::on_pushButtonImprimer_clicked()
{
    QPdfWriter pdf("C:\\Users\\yosra\\OneDrive\\Desktop\\GestionClients\\pdf_table_clients.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 25));
                          painter.drawText(950,1100,"Table Clients");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 15));
                          //painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(100,100,7300,2600);
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(200,3300,"CIN CLIENT");
                          painter.drawText(1300,3300,"NOM ");
                          painter.drawText(2100,3300,"PRENOM ");
                          painter.drawText(3200,3300,"DATE DE NAISSANCE");
                          painter.drawText(5300,3300,"ADRESSE MAIL");
                          painter.drawText(7400,3300,"NUM TEL");
                          painter.drawText(8600,3300,"NUM VISITES");
                          int aux=ui->lineEditCIN->text().toInt();
                          QString aux1=QString::number(aux);
                          QSqlQuery query;
                          query.prepare("select * from CLIENT ");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1300,i,query.value(1).toString());
                              painter.drawText(2100,i,query.value(2).toString());
                              painter.drawText(3200,i,query.value(3).toString());
                              painter.drawText(5300,i,query.value(4).toString());
                              painter.drawText(7400,i,query.value(5).toString());
                              painter.drawText(8600,i,query.value(6).toString());

                             i = i + 500;
                          }
                          QMessageBox::information(nullptr, QObject::tr("PDF Enregistré!"),
                                      QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pushButtonImprimer_fiche_clicked()
{
    QPdfWriter pdf("C:\\Users\\yosra\\OneDrive\\Desktop\\GestionClients\\pdf_fiche_client.pdf");
                      QPainter painter(&pdf);
                          painter.setPen(Qt::blue);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(3000,1400,"Fiche Client");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 20));
                          //painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(100,100,7300,2600);
                          QString image=ui->lineEdit_image->text();
                          //QString s="C:\\Users\\yosra\\OneDrive\\Desktop\\GestionClients\\Photo.jpg";
                          painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap(image));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 13));
                          painter.drawText(500,4400,"CIN ");
                          painter.drawText(500,4800,"NOM ");
                          painter.drawText(500,5200,"PRENOM ");
                          painter.drawText(500,5600,"DATE DE NAISSANCE");
                          painter.drawText(500,6000,"ADRESSE MAIL");
                          painter.drawText(500,6400,"NUM TEL");
                          painter.drawText(500,6800,"NUM VISITES");
                          int aux=ui->lineEditCIN_fiche->text().toInt();
                          QString aux1=QString::number(aux);
                          QSqlQuery query;
                          query.prepare("select * from CLIENT where (CIN  LIKE '%"+aux1+"%')");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(3500,4400,query.value(0).toString());
                              painter.drawText(3500,4800,query.value(1).toString());
                              painter.drawText(3500,5200,query.value(2).toString());
                              painter.drawText(3500,5600,query.value(3).toString());
                              painter.drawText(3500,6000,query.value(4).toString());
                              painter.drawText(3500,6400,query.value(5).toString());
                              painter.drawText(3500,6800,query.value(6).toString());

                          }
                          QMessageBox::information(nullptr, QObject::tr("PDF Enregistré!"),
                                      QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pushButtonStats_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                             model->setQuery("select * from CLIENT where NOMBRE_VISITES <2 ");
                             float age=model->rowCount();
                             model->setQuery("select * from CLIENT where NOMBRE_VISITES between 2 and 5 ");
                             float agee=model->rowCount();
                             model->setQuery("select * from CLIENT where NOMBRE_VISITES >5 ");
                             float ageee=model->rowCount();
                             float total=age+agee+ageee;
                             QString a=QString("Moins de 2 visites "+QString::number((age*100)/total,'f',2)+"%" );
                             QString b=QString("Entre 2 et 5 visites "+QString::number((agee*100)/total,'f',2)+"%" );
                             QString c=QString("Plus que 5 visites "+QString::number((ageee*100)/total,'f',2)+"%" );
                             QPieSeries *series = new QPieSeries();
                             series->append(a,age);
                             series->append(b,agee);
                             series->append(c,ageee);
                     if (age!=0)
                     {QPieSlice *slice = series->slices().at(0);
                      slice->setLabelVisible();
                      slice->setPen(QPen());}
                     if ( agee!=0)
                     {
                              // Add label, explode and define brush for 2nd slice
                              QPieSlice *slice1 = series->slices().at(1);
                              //slice1->setExploded();
                              slice1->setLabelVisible();
                     }
                     if(ageee!=0)
                     {
                              // Add labels to rest of slices
                              QPieSlice *slice2 = series->slices().at(2);
                              //slice1->setExploded();
                              slice2->setLabelVisible();
                     }
                             // Create the chart widget
                             QChart *chart = new QChart();
                             // Add data to chart with title and hide legend
                             chart->addSeries(series);
                             chart->setTitle("Statistiques sur le nombre de visites des clients "+ QString::number(total));
                             chart->legend()->hide();
                             // Used to display the chart
                             QChartView *chartView = new QChartView(chart);
                             chartView->setRenderHint(QPainter::Antialiasing);
                             chartView->resize(1000,500);
                             chartView->show();
}
