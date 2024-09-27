
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QSettings>

class DatabaseManager
{
public:
    static DatabaseManager &getInstance();
    QString getusername();
    bool isopen();
    void setusername(QString uname);

private:
    DatabaseManager();
    QSqlDatabase db;
    QString loguser;
};

#endif // DATABASEMANAGER_H
