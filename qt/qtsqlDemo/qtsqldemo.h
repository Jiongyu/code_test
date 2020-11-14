#ifndef QTSQLDEMO_H
#define QTSQLDEMO_H

#include <QMainWindow>

#include "./mysql.h"

namespace Ui {
class qtsqlDemo;
}

class qtsqlDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit qtsqlDemo(QWidget *parent = 0);
    ~qtsqlDemo();

private slots:

    void createConnection();

    void createTable();

    void insertByIndex();

    void deleteByIndex();

    void queryByIndex();

private:
    Ui::qtsqlDemo *ui;
    QSharedPointer<Mysql::mysql> mysqlImpl;

};

#endif // QTSQLDEMO_H
