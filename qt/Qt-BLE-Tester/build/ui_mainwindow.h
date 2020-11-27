/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *sendButton;
    QTextEdit *receivedTextEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *servicesComboBox;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *devicesComboBox;
    QPushButton *bleScanButton;
    QPushButton *connectButton;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *asciiRadioButton;
    QRadioButton *hexRadioButton;
    QPlainTextEdit *sendTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(517, 436);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        horizontalLayout_2->addWidget(sendButton);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        receivedTextEdit = new QTextEdit(centralWidget);
        receivedTextEdit->setObjectName(QString::fromUtf8("receivedTextEdit"));
        receivedTextEdit->setReadOnly(true);

        gridLayout->addWidget(receivedTextEdit, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        servicesComboBox = new QComboBox(centralWidget);
        servicesComboBox->setObjectName(QString::fromUtf8("servicesComboBox"));

        horizontalLayout->addWidget(servicesComboBox);

        horizontalLayout->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 6, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        devicesComboBox = new QComboBox(centralWidget);
        devicesComboBox->setObjectName(QString::fromUtf8("devicesComboBox"));

        horizontalLayout_3->addWidget(devicesComboBox);

        bleScanButton = new QPushButton(centralWidget);
        bleScanButton->setObjectName(QString::fromUtf8("bleScanButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bleScanButton->sizePolicy().hasHeightForWidth());
        bleScanButton->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        bleScanButton->setIcon(icon);

        horizontalLayout_3->addWidget(bleScanButton);

        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout_3->addWidget(connectButton);

        horizontalLayout_3->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        asciiRadioButton = new QRadioButton(centralWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(asciiRadioButton);
        asciiRadioButton->setObjectName(QString::fromUtf8("asciiRadioButton"));
        asciiRadioButton->setChecked(true);

        horizontalLayout_4->addWidget(asciiRadioButton);

        hexRadioButton = new QRadioButton(centralWidget);
        buttonGroup->addButton(hexRadioButton);
        hexRadioButton->setObjectName(QString::fromUtf8("hexRadioButton"));

        horizontalLayout_4->addWidget(hexRadioButton);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        sendTextEdit = new QPlainTextEdit(centralWidget);
        sendTextEdit->setObjectName(QString::fromUtf8("sendTextEdit"));

        gridLayout->addWidget(sendTextEdit, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 517, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), receivedTextEdit, SLOT(clear()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "Send", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Service", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        label->setText(QApplication::translate("MainWindow", "Device", nullptr));
        bleScanButton->setText(QString());
        connectButton->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        asciiRadioButton->setText(QApplication::translate("MainWindow", "ASCII", nullptr));
        hexRadioButton->setText(QApplication::translate("MainWindow", "Hex", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
