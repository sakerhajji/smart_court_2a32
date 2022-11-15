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
void on_Ajouter_clicked();
void on_afficher_clicked();
void on_supprimer_clicked();
void on_Update_clicked();
void on_pushButton_3_clicked();
void on_pushButton_clicked();

void on_comboBox_2_currentIndexChanged(const QString &arg1);

void on_chercher_textChanged(const QString &arg1);

void on_browseBtn_clicked();

void on_sendBtn_clicked();
void mailSent(QString);

void on_pushButton_4_clicked();



void on_login_clicked();

private:
    Ui::MainWindow *ui;
    affaire_juridique Aff ;
    QStringList files;
    bool logintest ;

};

#endif // MAINWINDOW_H
