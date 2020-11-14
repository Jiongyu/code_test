#ifndef HEADER
#define HEADER

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QMutex>
#include <QMessageBox>
#include <QVariant>
#include <QDebug>


//#define DEBUG_

#define myDebug()    qDebug() << ("文件名: ") <<  __FILE__ << ("行号: ")<<  __LINE__ << ("函数名: ") <<  __FUNCTION__;

#endif // HEADER

