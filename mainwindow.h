#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonajouter_clicked();
    void on_pushButton_supprimer_clicked();

    void on_pushButtonModifier_clicked();


    void on_pushButtonTri_clicked();

    void on_tab_clients_clicked(const QModelIndex &index);

    void on_pushButtonEffacer_clicked();

    void on_tab_clients_doubleClicked(const QModelIndex &index);

    void on_pushButtonImprimer_clicked();

    void on_pushButtonImprimer_fiche_clicked();

    void on_lineEditCIN_chercher_textChanged();

    void on_pushButtonStats_clicked();

private:
    Ui::MainWindow *ui;
    Client c;
};
#endif // MAINWINDOW_H
