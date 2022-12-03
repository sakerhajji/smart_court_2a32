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
    void on_pushButton_ajouter_AZ_clicked();

    void on_pushButton_supprimer_AZ_clicked();


    void on_updateBtnAZ_clicked();

    void on_pdfbuttonAZ_clicked();

    void on_tributtonAZ_clicked();

    void on_trier2AZ_clicked();





   void on_statbtnAZ_clicked();

   void on_excelAZ_clicked();



   void on_btnVersArduinoAZ_clicked();


   void on_btnVerifAZ_clicked();

   void on_TrouverAZIZ_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    salleaudience p;
    QByteArray data; // variable contenant les données reçues

            Arduino A; // objet temporaire
};
#endif
