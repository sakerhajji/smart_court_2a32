#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QPrinter>
#include"affaire_juridique.h"
#include "smtp.h"
#include "arduino.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void update_label();
void on_Ajouter_clicked();
void on_afficher_clicked();
void on_supprimer_clicked();
void on_Update_clicked();
void on_search_clicked();
void on_Sort_af_clicked();
void on_UpdateBox_currentIndexChanged(const QString &arg1);
void on_chercher_textChanged(const QString &arg1);
void on_browseBtn_clicked();
void on_sendBtn_clicked();
void mailSent(QString);
void on_PDF_clicked();
void on_login_clicked();
void on_ON_clicked();
void on_OFF_clicked();


private:
    Ui::MainWindow *ui;
    affaire_juridique Aff ;
    QStringList files;
    bool logintest ;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire

};

#endif // MAINWINDOW_H
