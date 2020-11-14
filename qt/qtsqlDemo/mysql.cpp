#include "mysql.h"

namespace Mysql{

int mysql::index = 0;

mysql::mysql()
{
    qDebug() << QSqlDatabase::drivers();
}

bool mysql::createConnection(QString name){

#ifdef DEBUG_
    myDebug();
#endif

    if(QSqlDatabase::contains(name)){
        database = QSqlDatabase::database("QMYSQL3");
        qDebug() << "contains";
    }
    else{
        database = QSqlDatabase::addDatabase("QMYSQL3",name);
        qDebug() << "not contains";
    }
//    database.setHostName(QString("localhost"));
    database.setUserName(QString("root"));
    database.setPassword(QString("12345"));
    database.setDatabaseName(QString("jony"));
    database.setPort(3306);

    if(! database.open()){
        QMessageBox::warning(NULL, "open database error", database.lastError().text());
        return false;
    }

    QStringList temp = database.tables();
    for(int i = 0; i < temp.size(); ++ i){
        qDebug() << temp[i];
    }

    query = QSqlQuery(database);
    qDebug() << "end ";
    return true;
}

bool mysql::createTable(QString name){

#ifdef DEBUG_
    myDebug();
#endif

    tableName = name;
    QString selectsql = QString("select * from sys.tables where name='") +  tableName + QString("'");

    query.exec(selectsql);

    if(query.next()){
        QMessageBox::information(NULL, "info" ,"table is already open!");
        return true;
    }

    query.exec(    "CREATE TABLE " + QString(tableName) + "(\
                   id int PRIMARY KEY AUTO_INCREMENT,\
                   name VARCHAR(40) NOT NULL, \
                   score INTEGER NOT NULL)"
            );

    if(query.next()){
        qDebug() << "create table success";
        return true;
    }else{
        qDebug() << query.lastError().text();
    }

    return false;
}

bool mysql::insertByIndex(QString name, int source){

#ifdef DEBUG_
    myDebug();
#endif
    //    " (name, score) value ('" + QString(name) + "','" + QString(source)+ "')");

    query.exec("insert into " + QString(tableName) + \
        "(name, score) value ('" + QString(name) + "','" + QString::number(source)+ "')");

//        "(id, name, score) value ('" + QString::number(index) + "','" + QString(name) + "','" + QString::number(source)+ "')");

    index ++;

    if(query.next()){
        return true;
    }else{
        qDebug() << query.lastError().text();

    }

    return false;

}

bool mysql::deleteByIndex(int index){

#ifdef DEBUG_
    myDebug();
#endif

    query.exec("DELETE FROM " + tableName + " WHERE id = " + QString::number(index));

    if(query.next()){
        return true;
    }else{
        qDebug() << query.lastError().text();

    }

    return false;
}

bool mysql::queryByIndex(int index){

#ifdef DEBUG_
    myDebug();
#endif
    query.exec("SELECT * FROM " + tableName + " WHERE id <" + QString::number(index));

    while(query.next()){
//        QMessageBox::information(NULL, "query by index", query.value("name").toString());
        QString id =  query.value("id").toString();
        QString name =  query.value("name").toString();
        QString score = query.value("score").toString();
        qDebug() << id << name << score;
//        return true;
    }
//    else{
//        qDebug() << query.lastError().text();

//    }
    return false;
}

mysql::~mysql(){

}


}   // end namespace Mysql
