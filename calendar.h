#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDialog>

namespace Ui {
class calendar;
}

class calendar : public QDialog
{
    Q_OBJECT

public:
    explicit calendar(QWidget *parent = nullptr);
    ~calendar();

private slots:
    //void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_accepted();

private:
    Ui::calendar *ui;
};

#endif // CALENDAR_H
