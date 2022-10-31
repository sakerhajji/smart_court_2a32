#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"affaire_juridique.h"

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

    void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;
    affaire_juridique Aff ;

};

#endif // MAINWINDOW_H
