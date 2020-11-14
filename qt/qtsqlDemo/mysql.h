#ifndef MYSQL_H
#define MYSQL_H

#include "./header.h"

//#include <memory>

namespace Mysql {



class mysql
{
public:
    mysql();

    bool createConnection(QString name);

    bool createTable(QString name);

    bool insertByIndex(QString name, int source);

    bool deleteByIndex(int index);

    bool queryByIndex(int index);

    ~mysql();

private:
    QMutex mutex;
    QSqlDatabase database;
    QSqlQuery query;
    QString tableName;
    static int index;

};


}   // end namespace Mysql

#endif // MYSQL_H
