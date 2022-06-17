/********************************************************************************
** Form generated from reading UI file 'chess1.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESS1_H
#define UI_CHESS1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chess1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *chess1Class)
    {
        if (chess1Class->objectName().isEmpty())
            chess1Class->setObjectName(QString::fromUtf8("chess1Class"));
        chess1Class->resize(600, 400);
        menuBar = new QMenuBar(chess1Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        chess1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(chess1Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        chess1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(chess1Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        chess1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(chess1Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        chess1Class->setStatusBar(statusBar);

        retranslateUi(chess1Class);

        QMetaObject::connectSlotsByName(chess1Class);
    } // setupUi

    void retranslateUi(QMainWindow *chess1Class)
    {
        chess1Class->setWindowTitle(QCoreApplication::translate("chess1Class", "chess1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chess1Class: public Ui_chess1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESS1_H
