#include "qtsqldemo.h"
#include "ui_qtsqldemo.h"

qtsqlDemo::qtsqlDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtsqlDemo),
    mysqlImpl(new Mysql::mysql())
{
    ui->setupUi(this);
    connect(ui->pushButton_CreateConnection, SIGNAL(clicked()), this, SLOT(createConnection()));
    connect(ui->pushButton_CreateTable, SIGNAL(clicked()), this, SLOT(createTable()));
    connect(ui->pushButton_deleteItem, SIGNAL(clicked()), this, SLOT(deleteByIndex()));
    connect(ui->pushButton_insertItem, SIGNAL(clicked()), this, SLOT(insertByIndex()));
    connect(ui->pushButton_queryItem, SIGNAL(clicked()), this, SLOT(queryByIndex()));

}

qtsqlDemo::~qtsqlDemo()
{
    delete ui;
}

void qtsqlDemo::createConnection(){

    mysqlImpl->createConnection(QString("testDemo"));
}

void qtsqlDemo::createTable(){

    mysqlImpl->createTable(QString("person"));
}

void qtsqlDemo::insertByIndex(){

    mysqlImpl->insertByIndex(QString("jony"), 100);
}

void qtsqlDemo::deleteByIndex(){
    mysqlImpl->deleteByIndex(2);
}

void qtsqlDemo::queryByIndex(){
    mysqlImpl->queryByIndex(10);
}
