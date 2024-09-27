#include "databasemanager.h"

DatabaseManager& DatabaseManager::getInstance(){
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::isopen(){
    if(db.isOpen()){
        return 1;
    }
    else{
        return 0;
    }
}

QString DatabaseManager::getusername(){
    return loguser;
}

void DatabaseManager::setusername(QString uname){
    loguser = uname;
}

DatabaseManager::DatabaseManager()
{
    QString hostname, database, username, password;
    int port;
    QString filePath = QCoreApplication::applicationDirPath() + "/database.ini";

    QSettings settings(filePath,QSettings::IniFormat);
    hostname = settings.value("Database/localhost").toString();
    database = settings.value("Database/database").toString();
    username = settings.value("Database/username").toString();
    port     = settings.value("Database/port").toInt();
    password = settings.value("Database/password").toString();

    qDebug()<<"ini files read"<<hostname<<database<<username<<password;
    // ...
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(hostname);
    db.setPort(port);
    db.setDatabaseName(database);
    db.setUserName(username);
    db.setPassword(password);
    if (db.open()) {
        //qDebug()<<"Database connection done";
    } else {
        qCritical()<<"Database connection error" <<db.lastError();
    }
}

