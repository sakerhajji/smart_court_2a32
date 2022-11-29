#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <juge.h>

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
    void on_pushButton_clicked();

    void on_bt_supprimer_clicked();


    void on_modiferbutton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_chercher_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
    Juge j;
};

#endif // MAINWINDOW_H
