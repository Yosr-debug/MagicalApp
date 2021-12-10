#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Offre.h"
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include "exportexcelobjet.h"
#include "QrCode.hpp"

using namespace qrcodegen;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui ->tableView_Off->setModel(tmpoff.afficher_Off());
     ui->le_code->setValidator( new QIntValidator(0, 999999999, this));
      ui->le_cin->setValidator( new QIntValidator(0, 99999999, this));
       ui->le_code->setValidator( new QIntValidator(0, 999999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_4_clicked()
{
    QString id_off = ui->le_code->text();
    QString nom_off = ui->le_nom->text();
    int cin = ui->le_cin->text().toInt();
    QString duree = ui->le_duree->text();
     QString date_off = ui->le_date->text();

      //if(cin.size() == 8){

    Offre o(id_off,nom_off,cin,date_off,duree);
    bool test=o.ajouter_Off();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                          QObject::tr("Offre ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

    }
    /*  }else{
          QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                            QObject::tr("Verifier Le CIN.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

      }
*/
 ui ->tableView_Off->setModel(tmpoff.afficher_Off());

}


void MainWindow::on_pushmod_2_clicked()
{
    QString id_off = ui->le_code_2->text();
    QString nom_off = ui->le_nom_2->text();
    QString duree = ui->le_duree_2->text();
    QString date_off = ui->date_2->text();
     Offre o;
    bool test=o.modifier_Off(id_off,nom_off,date_off,duree);

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("modifie une Offre"),
                          QObject::tr("Offre modifie.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("non modifie"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

     ui->tableView_Off->setModel(tmpoff.afficher_Off());

}

void MainWindow::on_supp_clicked()
{
    QString id =ui->tableView_Off->model()->index(ui->tableView_Off->currentIndex().row(),0).data().toString();
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Supprimer", "Etes vous sur de supprimer cet Offre? ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
         // int idi = id.toInt() ;
          bool test=tmpoff.supprimer_Off(id);
          if(test)
          {
              ui->tableView_Off->setModel(tmpoff.afficher_Off());
              QMessageBox::information(nullptr,"Suppression","Offre supprimé");

          }
      }

}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    ui->tableView_Off->setModel(tmpoff.rechercher(arg1));
}

void MainWindow::on_pushButton_clicked()
{
    QString strStream;
            QTextStream out(&strStream);


    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);
    const int rowCount = ui->tableView_Off->model()->rowCount();
    const int columnCount = ui->tableView_Off->model()->columnCount();
    QString TT = QDate::currentDate().toString("yyyy/MM/dd");
    out <<"<html>\n"
          "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        << "<title>ERP - OFFRE LIST<title>\n "
        << "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<h1 style=\"text-align: center;\"><strong> LISTE DES OFFRES </strong></h1>"
        "<h5 style=\"text-align: center;\">Le : "+TT+"</h5>"
        "<br>\n"
        "<table style=\"text-align: center; font-size: 12;\" border=1>\n "
          "</br> </br>";
    // headers
    out << "<thead><tr bgcolor=#d6e5ff>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView_Off->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_Off->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_Off->isColumnHidden(column)) {
                QString data =ui->tableView_Off->model()->data(ui->tableView_Off->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.print(&printer);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                                tr("Fichiers d'extension Excel (*.xls)"));
                if (fileName.isEmpty())
                    return;

                ExportExcelObject obj(fileName, "mydata", ui->tableView_Off);

                // you can change the column order and
                // choose which colum to export
                obj.addField(0, "ID_P", "char(20)");
                obj.addField(1, "NOM_P", "char(20)");
                obj.addField(2, "TYPE", "char(20)");
                obj.addField(3, "PRIX", "char(20)");
                //obj.addField(5, "servespeed3", "char(20)");


                int retVal = obj.export2Excel();

                if( retVal > 0)
                {
                    QMessageBox::information(this, tr("FAIS!"),
                                             QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                             );
                }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tableView_Off->setModel(tmpoff.tri());

}

void MainWindow::on_pushButton_5_clicked()
{
    int tabev=ui->tableView_Off->currentIndex().row();
    QVariant idd=ui->tableView_Off->model()->data(ui->tableView_Off->model()->index(tabev,0));
    QString id= idd.toString();
    QSqlQuery qry;
    qry.prepare("select * from offres where id_off=:id");
    qry.bindValue(":id",id);
    qry.exec();
    QString a,aa,aaa,aaaa,aaaaa;
    while(qry.next()){
        a=qry.value(0).toString();
        aa=qry.value(1).toString();
        aaa=qry.value(2).toString();
        aaaa=qry.value(3).toString();
        aaaaa=qry.value(4).toString();
    }

 QString   ids="ID  : "+a+"  Date offre : "+aa+" Duree : "+aaa+" CIN : "+aaaa+" Nom offre : "+aaaaa;
    QrCode qr = QrCode::encodeText(ids.toUtf8().constData(), QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);
    ui->qrlabel->setPixmap(QPixmap::fromImage(im));
    int i=0 ;

}
