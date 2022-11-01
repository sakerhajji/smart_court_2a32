#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include "salleaudience.h"
#include <QMainWindow>

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
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();


    void on_update_clicked();

private:
    Ui::MainWindow *ui;
    salleaudience p;
};
#endif // MAINWINDOW_H
