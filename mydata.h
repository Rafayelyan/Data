#ifndef MYDATA_H
#define MYDATA_H

#include <QDialog>
#include <QString>

extern QString path;


namespace Ui {
class MyData;
}

class MyData : public QDialog
{
    Q_OBJECT

public:
    explicit MyData(int isAdd = 0,QWidget *parent = nullptr);
    int isAdd;
    ~MyData();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MyData *ui;
};

#endif // MYDATA_H
