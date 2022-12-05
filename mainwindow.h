#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QPrinter>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <bits/stdc++.h>
#include<QMessageBox>
#include<QIntValidator>
#include <QPainter>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableWidget>
#include<QSystemTrayIcon>

#include "salleaudience.h"
#include "connection.h"
#include<QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QIntValidator>
#include <QTabWidget>
#include <QAbstractItemView>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>
#include<QMessageBox>
#include <QtSql/QSqlError>
#include<QIntValidator>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include<QSystemTrayIcon>
#include<QPrinter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>
#include <QSqlQuery>
#include <exportexcelobject.h>







#include"affaire_juridique.h"
#include "smtp.h"
#include "arduino.h"
#include "avocat.h"
#include "conge.h"
#include "juge.h"
#include "salleaudience.h"




/**********Amine**********/
#include "personnels.h"
#include"arduinop.h"
#include <QMainWindow>
#include <QtPrintSupport/QPrintDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QChartView *chartView ;
        void BarChartAV();
        void PieChart();

private slots:
    void on_login_clicked();
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
    void on_ON_clicked();
    void on_OFF_clicked();
    void on_btn_ajouter_clicked();
    void on_btn_supprimer_clicked();
    void on_btn_modifier_clicked();
    void on_btn_trouver_clicked();
    void on_Achercher_textChanged(const QString &arg1);
    void on_btn_tri_clicked();
    void on_pdf_AV_clicked();
    void on_sendBtnAV_clicked();
    void on_browseBtnAV_clicked();
    void on_btn_evaluer_clicked();
    void on_btn_executer_clicked();
    void on_ajouter_conge_clicked();
    /**************************************/
    void on_yas_ajouter_clicked();
    void on_yas_supprimer_clicked();
    void on_yas_modifer_clicked();
    void on_yas_tri1_clicked();
    void on_yas_tri2_clicked();
    void on_chercher_yas_textChanged(const QString &arg1);
    void on_yas_chercher_clicked();
    void on_yas_browse_clicked();
    void on_yas_send_clicked();
    void on_yas_pdf_clicked();
    void on_calendarWidget_clicked(const QDate &date);
    void on_yas_done_clicked();
    void on_yas_verifier_clicked();
    /******************aziz******************/
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
     /******************aziz******************/
/********************Amine********************/

    void rechEmploy();

    void on_ajouter_3_clicked();

    void on_supprimer_3_clicked();

    void on_update_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();
void on_rechercher_button_clicked();
    void on_lineEdit_customContextMenuRequested(const QPoint &pos);
void on_qrcodegen_clicked();
void on_statsmed_clicked();
/********************Amine********************/

void on_ajouter_2_clicked();

void on_pushButton_9_clicked();

void on_rechercher_button_2_clicked();

void on_qrcodegen_2_clicked();

void on_stastmed_clicked();

void on_pushButton_14_clicked();

void on_pushButton_11_clicked();

void on_pushButton_12_clicked();
void on_pushButton_13_clicked();

void on_pushButton_10_clicked();

private:

    Ui::MainWindow *ui;
    affaire_juridique Aff ;
    QStringList files;
    bool logintest ;
    QByteArray data;
    Arduino Ar;
    Arduino aav ;
    Avocat A ;
    SALLE_AUDIENCE p;
    conge c ;
    QByteArray dataaAV;
    Juge j;
    QSystemTrayIcon *msystemtryicon;


//amine
    personnels per;

    QByteArray dataP; // variable contenant les données reçues

       //ArduinoP A;

};
#endif // MAINWINDOW_H
