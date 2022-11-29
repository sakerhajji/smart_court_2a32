#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "personnels.h"
#include"arduino.h"
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
    void rechEmploy();

    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_update_clicked();

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
private:
    Ui::MainWindow *ui;
    personnels p;

    QByteArray data; // variable contenant les données reçues

       Arduino A;
};

#endif // MAINWINDOW_H
