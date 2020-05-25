#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>
#include <string>
#include <QTableView>

QString path;

/*static */bool createConnection();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection())
    {
        qDebug()<<"cont connect";
        return -1;
    }

    path=argv[0];
    path = path.replace("\\","/");
    int index = path.lastIndexOf("/");
    path.remove(index,path.length());
    path =  path + "/../../Data/sqllite/data.sqlite";


    MainWindow w;
    w.show();
    return a.exec();
}

/*static */bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if(!db.open())
    {
        qDebug() << "Cannot open database: " << db.lastError();
        return false;
    }
    return true;
}

