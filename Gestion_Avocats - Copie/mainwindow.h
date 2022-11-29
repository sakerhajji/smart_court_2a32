#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "avocat.h"
#include "conge.h"
#include <QMainWindow>
#include<QTextStream>
#include <QPrinter>
#include<QFileDialog>
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
#include "arduino.h"
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QChartView *chartView ;
        void BarChart();
        void PieChart();

private slots:
    void  update_label();

    void on_btn_ajouter_clicked();

    void on_btn_supprimer_clicked();

    void on_btn_modifier_clicked();

    void on_btn_trouver_clicked();

void on_Achercher_textChanged(const QString &arg1);

    void on_btn_tri_clicked();

    void on_pdf_clicked();

    void on_sendBtn_clicked();

    void on_browseBtn_clicked();

    void on_btn_evaluer_clicked();

    void on_btn_executer_clicked();

    void on_ajouter_conge_clicked();


private:
    Ui::MainWindow *ui;
    Avocat A ;
    QStringList files;
    conge c ;
    arduino a ;
    QByteArray dataa;
};

#endif // MAINWINDOW_H
