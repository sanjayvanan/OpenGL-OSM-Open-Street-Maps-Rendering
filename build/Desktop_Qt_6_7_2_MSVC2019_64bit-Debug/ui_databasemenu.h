/********************************************************************************
** Form generated from reading UI file 'databasemenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEMENU_H
#define UI_DATABASEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DatabaseMenu
{
public:

    void setupUi(QWidget *DatabaseMenu)
    {
        if (DatabaseMenu->objectName().isEmpty())
            DatabaseMenu->setObjectName("DatabaseMenu");
        DatabaseMenu->resize(400, 300);

        retranslateUi(DatabaseMenu);

        QMetaObject::connectSlotsByName(DatabaseMenu);
    } // setupUi

    void retranslateUi(QWidget *DatabaseMenu)
    {
        DatabaseMenu->setWindowTitle(QCoreApplication::translate("DatabaseMenu", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DatabaseMenu: public Ui_DatabaseMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEMENU_H
