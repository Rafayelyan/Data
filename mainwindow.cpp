#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydata.h"
#include <QSqlQuery>
#include <QString>
#include <string>
#include <QtSql>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QDebug>
#include <QMessageBox>
using namespace std;

void showTable(QObject* parent,Ui::MainWindow *ui);

QString id;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showTable(this,ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{

    MyData addElementWindow;
    addElementWindow.setModal(true);
    addElementWindow.exec();
    showTable(this,ui);
}

void MainWindow::on_pushButton_clicked()
{
    //search button clicked
    QString search_data = ui->lineEdit->text();
    string input = search_data.toStdString();
    while(!input.find_first_of(' '))
    {
        input.erase(0,1);
    }
    qDebug() << input[0];
    if(input == "")
    {
        showTable(this,ui);
    }
    else
    {
        QString search_data = QString::fromUtf8(input.c_str());

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);
        if(!db.open())
        {
            qDebug()<<"cannot open database."<<db.lastError();
        }
        QSqlQueryModel *modal = new QSqlQueryModel();

        QSqlQuery *query = new QSqlQuery(db);

        query->prepare("SELECT * FROM people WHERE (first_name='"+ search_data + "' or last_name='"+ search_data + "' or adress='"+ search_data + "' or phone='"+ search_data + "')");

        if(!query->exec())
        {
            qDebug() << "Unable to select";
        }
        modal->setQuery(*query);
        ui->tableView->setModel(modal);
        qDebug() << modal->rowCount();
    }
}


// how to create db exter and use it(chi stacvel)
void showTable(QObject* parent,Ui::MainWindow *ui)
{

       QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(path);
       if(!db.open())
       {
           qDebug()<<"cannot open database."<<db.lastError();
       }

       QSqlTableModel *model= new QSqlTableModel(parent,db);
       model->setTable("people");
       //model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model->select();
       ui->tableView->setModel(model);
       ui->tableView->setColumnHidden(0,1);
       //ui->tableView->selected;
       ui->tableView->show();

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->pushButton_3->setEnabled(true);
    id = QVariant(index.sibling(index.row(),0).data()).toString();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if(!db.open())
    {
        qDebug() << "Cannot open database: " << db.lastError();
    }
    QSqlQuery query;
    query.prepare("DELETE FROM people WHERE id='"+ id + "'");

    if(!query.exec())
    {
        qDebug() << "Unable to delete";
    }
    ui->pushButton_3->setEnabled(false);
    showTable(this,ui);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"------------------------------------";
    id = QVariant(index.sibling(index.row(),0).data()).toString();


    MyData addElementWindow(id.toInt());
    addElementWindow.setModal(true);
    addElementWindow.exec();

    showTable(this,ui);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    //text edited
    string input = arg1.toStdString();
    while(!input.find_first_of(' '))
    {
        input.erase(0,1);
    }
    qDebug() << input[0];

    if(input == "")
    {
        showTable(this,ui);
    }
}
