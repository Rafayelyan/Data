#include "mydata.h"
#include "ui_mydata.h"
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

MyData::MyData(int isAdd,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyData)
{
    ui->setupUi(this);
    if(isAdd)
    {
        ui->pushButton_2->hide();
//        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//        qDebug()<<path;
//        db.setDatabaseName(path);
//        if(!db.open())
//        {
//            qDebug() << "Cannot open database: " << db.lastError();
//        }
        QSqlQuery query;
        QString index = QVariant(isAdd).toString();
        query.prepare("SELECT * FROM people WHERE id='"+ index + "'");

        if(!query.exec())
        {
            qDebug() << "Unable to make insert operation";
        }
        QString first_name,last_name,adress,phone;
        while(query.next())
        {
            first_name=query.value(1).toString();
            last_name=query.value(2).toString();
            adress=query.value(3).toString();
            phone=query.value(4).toString();
            qDebug() << first_name<<last_name<<adress<<phone;
        }
        ui->lineEdit->setText(first_name);
        ui->lineEdit_2->setText(last_name);
        ui->lineEdit_3->setText(adress);
        ui->lineEdit_6->setText(phone);
        ui->lineEdit->setReadOnly(1);
        ui->lineEdit_2->setReadOnly(1);
        ui->lineEdit_3->setReadOnly(1);
        ui->lineEdit_6->setReadOnly(1);
    }




}

MyData::~MyData()
{
    delete ui;
}

void MyData::on_pushButton_2_clicked()
{
    QString  first_name,last_name,adress,phone;
    first_name = ui->lineEdit->text();
    last_name = ui->lineEdit_2->text();
    adress = ui->lineEdit_3->text();;
    phone = ui->lineEdit_6->text();

    if(first_name.length() == 0)
    {
        ui->label_3->setText("Please write First name input");
    }
    else if(last_name.length() == 0)
    {
        ui->label_3->setText("Please write Last name input");
    }
    else if(adress.length() == 0)
    {
        ui->label_3->setText("Please write Adress input");
    }
    else if(phone.length() < 4)
    {
        ui->label_3->setText("Number most be have 12 characters");
    }
    else
    {
//        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//        db.setDatabaseName(path);

//        if(!db.open())
//        {
//            qDebug() << "Cannot open database: " << db.lastError();
//        }
        QSqlQuery query;
        query.prepare("INSERT INTO people(first_name,last_name,adress,phone)  "
                       "VALUES (:first_name, :last_name, :adress,:phone)");
        query.bindValue(":first_name", first_name);
        query.bindValue(":last_name", last_name);
        query.bindValue(":adress", adress);
        query.bindValue(":phone", phone);
        if(!query.exec())
        {
            qDebug() << "Unable to make insert operation";
        }

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();;
        ui->lineEdit_6->clear();

    }

}

void MyData::on_pushButton_clicked()
{
    this->close();
}
