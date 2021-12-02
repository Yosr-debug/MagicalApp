#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <personnel.h>


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_add_clicked();

    void on_mod_clicked();

    void on_supp_clicked();

    void on_mod_3_clicked();

  //  void on_pushButton_imp_clicked();

    void on_pushButton_4_clicked();

    //void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

   // void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    //void on_label_2_linkActivated(const QString &link);

   // void on_tri_desc_8_clicked();

//    void on_tri_asc_8_clicked();

   // void on_pushButton_tric_clicked();

    void on_pushButton_trid_clicked();

    void on_tri_salaire_clicked();


    void on_tabperso_clicked(const QModelIndex &index);
    //void on_QRcodecom_pressed();

    //void on_QRcodecom_2_clicked();

    //void on_QRcodecom_clicked();

   // void on_QRcodecom_2_pressed();

  //  void on_pushButton_clicked();

    void on_QRcodecom_3_clicked();

    //void on_QRcodecom_4_clicked();

    void on_pushButton_5_clicked();

    void on_QRcodecom_clicked();

private:
    Ui::Form *ui;
    personnel tmpperso;

};

#endif // FORM_H
