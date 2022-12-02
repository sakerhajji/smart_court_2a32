#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include"connection.h"
#include "juge.h"
#include "smtp.h"
#include <bits/stdc++.h>
#include "arduino.h"
using namespace  std ;


QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
class QSystemTrayIcon;
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void update_label();
    void on_yas_ajouter_clicked();

    void on_yas_supprimer_clicked();


    void on_yas_modifer_clicked();

    void on_yas_tri1_clicked();

    void on_yas_tri2_clicked();

    void on_chercher_textChanged(const QString &arg1);

    void on_yas_chercher_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_yas_browse_clicked();

    void on_yas_send_clicked();
    void mailSent(QString status) ;

    void on_yas_pdf_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_checkBox_clicked();

    void on_done_clicked();

    void on_yas_done_clicked();

    void on_yas_verifier_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_le_cin_supp_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    Juge j;
    QStringList files;
    QSystemTrayIcon *msystemtryicon;
    QByteArray data;
    Arduino A;
};

#endif // MAINWINDOW_H
