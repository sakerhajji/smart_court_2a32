#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include "salleaudience.h"
#include <QMainWindow>
#include "arduinoh.h"



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
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();


    void on_update_clicked();

    void on_pdfbutton_clicked();

    void on_tributton_clicked();

    void on_trierbutton2_clicked();

    void on_recherchebutton_textChanged(const QString &arg1);

   void on_stat_clicked();



   void on_bb_clicked();

   void on_excel_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_5_clicked();

   void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    salleaudience p;
    QByteArray data; // variable contenant les données reçues

            Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
