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
    void on_pushButton_clicked();

    void on_bt_supprimer_clicked();


    void on_modiferbutton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_chercher_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_browseBtn_clicked();

    void on_sendBtn_clicked();
    void mailSent(QString status) ;

    void on_pdf_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_checkBox_clicked();

    void on_done_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    Juge j;
    QStringList files;
    QSystemTrayIcon *msystemtryicon;
};

#endif // MAINWINDOW_H
