#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collaboration.h"
#include "notification.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSystemTrayIcon>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QIntValidator>
#include <QValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      ui->tableView->setModel(tempcollab.afficher_collab());
      ui->lineEdit_code_collab->setValidator(new QIntValidator(0,99999999,this));
      mysystem = new QSystemTrayIcon(this);
      mysystem ->setIcon(QIcon(":/logo.png"));
      mysystem ->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
   /* int code_collab=ui->le_codecollab->text().toInt();
    QString collab=ui->le_collab->text();
    QString type_collab=ui->le_type_collab->text();
    Collaboration C(code_collab,collab,type_collab);*/
}

void MainWindow::on_pushButton_ajoutercoll_clicked() //AJOUTER
{    notification n;
    int code_collab=ui->lineEdit_code_collab->text().toInt();
        QString nom_collaborateur=ui->lineEdit_nom_collaborateur->text();
        QString type_collab=ui->lineEdit_type_collab->text();
        QString budget=ui->lineEdit_budget->text();
        QString datedebut=ui->dateEdit_debut->date().toString();
        QString datefin=ui->dateEdit_fin->date().toString();


            Collaboration c(code_collab,nom_collaborateur,type_collab,budget,datedebut,datefin);
            bool test=c.ajouter_collab();
            if(test)
            {n.setPopupText("Une Collaboration a ete ajoutee");
                n.show();
                mysystem->showMessage(tr("Notification"),tr("Il y a un ajout d'une collaboration"));
                ui->tableView->setModel(tempcollab.afficher_collab());
                QMessageBox::information(nullptr, QObject::tr("Ajout"),
                            QObject::tr("Ajout avec succés.\n" "Click Cancel to exit."), QMessageBox::Cancel);

            }
             else
                QMessageBox::critical(nullptr, QObject::tr("Ajout"),
                            QObject::tr("Ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_9_clicked() //Supprimer
{ notification n;
    int id=ui->lineEdit_code_collab->text().toUInt();
            bool test=tempcollab.supprimer_collab(id);
            if(test)
            {n.setPopupText("Une Collaboration a ete supprimer");
                n.show();
                mysystem->showMessage(tr("Notification"),tr("Il y a une suppression d'une collaboration"));
                ui->tableView->setModel(tempcollab.afficher_collab());
                QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                QObject::tr("Suppression avec succée"), QMessageBox::Ok);
               // hide();
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
                QObject::tr("Suppression echoués"), QMessageBox::Ok);
            }
}

void MainWindow::on_pushButton_8_clicked()  // Modifier
{notification n;
    int code_collab=ui->lineEdit_code_collab->text().toInt();
        QString nom_collaborateur=ui->lineEdit_nom_collaborateur->text();
        QString type_collab=ui->lineEdit_type_collab->text();
        QString budget=ui->lineEdit_budget->text();
        QString datedebut=ui->dateEdit_debut->date().toString();
        QString datefin=ui->dateEdit_fin-> date().toString();

            Collaboration c(code_collab,nom_collaborateur,type_collab,budget,datedebut,datefin);
            bool test=c.modifier_collab(code_collab);
            if(test)
            {n.setPopupText("Une Collaboration a ete modifier");
                n.show();
                mysystem->showMessage(tr("Notification"),tr("Il y a une modification d'une collaboration"));
                ui->tableView->setModel(tempcollab.afficher_collab());
                QMessageBox::information(nullptr, QObject::tr("modification"),
                            QObject::tr("Modification avec succés.\n" "Click Cancel to exit."), QMessageBox::Cancel);

            }
             else
                QMessageBox::critical(nullptr, QObject::tr("modification"),
                            QObject::tr("Modification échouée.\n""Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableView_activated(const QModelIndex &index) //
{
    Collaboration c;
        QString code_collab=ui->tableView->model()->data(index).toString();
          QSqlQuery query;

          query.prepare("select * from COLLAB where code_collab LIKE '"+code_collab+"%' or nom_collaborateur LIKE '"+code_collab+"%' or type_collab LIKE '"+code_collab+"%'");
          if(query.exec())
          {
            while(query.next())
            {
                ui->lineEdit_code_collab->setText(query.value(0).toString());
                ui->lineEdit_nom_collaborateur->setText(query.value(1).toString());
                ui->lineEdit_type_collab->setText(query.value(2).toString());
                ui->lineEdit_budget->setText(query.value(4).toString());

          }
          }
            else
            {


              QMessageBox::critical(nullptr, QObject::tr("error"),
                          QObject::tr("error.\n""Click Cancel to exit."), QMessageBox::Cancel);
          }
}

void MainWindow::on_pushButton_6_clicked()
{
    QString code_collab =ui->lineEdit_rech->text();
       ui->tableView->setModel(tempcollab.recherche(code_collab));
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->tableView->setModel(tempcollab.triercroi());

}

void MainWindow::on_pushButton_10_clicked()
{
    ui->tableView->setModel(tempcollab.trierdeccroi());

}

void MainWindow::on_pushButton_clicked()
{
    QPdfWriter pdf("C:/Users/Rayen/Desktop/Atelier_Connexion/Atelier_Connexion/pdfcollab.pdf");
                  QPainter painter(&pdf);
                 int i = 4000;
                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Arial", 25));
                      painter.drawText(950,1100,"LISTE DES COLLABORATIONS");
                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Arial", 15));
                     //
                      painter.drawRect(100,100,7300,2600);
                      painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Rayen/Desktop/Atelier_Connexion/Atelier_Connexion/logo.png"));
                      painter.drawRect(0,3000,9600,500);
                      painter.setFont(QFont("Arial", 9));
                      painter.drawText(200,3300,"CODE COLLAB");
                      painter.drawText(1600,3300,"NOM COLLAB");
                      painter.drawText(3000,3300,"TYPE COLLAB");
                      painter.drawText(4200,3300,"BUDGET");
                      painter.drawText(5300,3300,"DATE DEBUT");
                      painter.drawText(7400,3300,"DATE FIN");


                      QSqlQuery query;
                      query.prepare("select * from COLLAB");
                      query.exec();
                      while (query.next())
                      {
                          painter.drawText(200,i,query.value(0).toString());
                          painter.drawText(1600,i,query.value(1).toString());
                          painter.drawText(3000,i,query.value(2).toString());
                          painter.drawText(4200,i,query.value(3).toString());
                          painter.drawText(5300,i,query.value(4).toString());
                          painter.drawText(7400,i,query.value(5).toString());


                         i = i + 500;
                      }
                      QMessageBox::information(nullptr, QObject::tr("PDF Enregistré!"),
                                  QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->tableView->model()->rowCount();
                  const int columnCount = ui->tableView->model()->columnCount();
                  out <<"<html>\n"
                        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      << "<title>ERP - COMmANDE LIST<title>\n "
                      << "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"
                      "<h1 style=\"text-align: center;\"><strong> LISTE DES COLLABORATIONS  ""</strong></h1>"
                      "<table style=\"text-align: center; font-size: 13px;\" border=1>\n "
                        "</br> </br>";
                  // headers
                  out << "<thead><tr bgcolor=#FF3399>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tableView->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableView->isColumnHidden(column)) {
                              QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table>\n"
                      "</body>\n"
                      "</html>\n";

                  QTextDocument *document = new QTextDocument();
                  document->setHtml(strStream);

                  QPrinter printer;

                  QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                  if (dialog->exec() == QDialog::Accepted) {
                      document->print(&printer);
                  }

                  delete document;
}

