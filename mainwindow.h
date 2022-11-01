#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "avocat.h"
#include <QMainWindow>

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
    void on_btn_ajouter_clicked();

    void on_btn_supprimer_clicked();

    void on_btn_modifier_clicked();

private:
    Ui::MainWindow *ui;
    Avocat A ;
};

#endif // MAINWINDOW_H
