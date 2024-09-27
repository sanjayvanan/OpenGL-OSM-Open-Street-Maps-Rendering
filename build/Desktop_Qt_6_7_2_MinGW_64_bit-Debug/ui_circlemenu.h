/********************************************************************************
** Form generated from reading UI file 'circlemenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCLEMENU_H
#define UI_CIRCLEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CircleMenu
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox_loadOrder;
    QPushButton *pushButton_splitz;
    QPushButton *pushButton_saveCircle;
    QPushButton *pushButton_loadCircle;
    QPushButton *pushButton_unloadCircle;
    QPushButton *pushButton_deleteCircle;
    QPushButton *pushButton_removeCircle;
    QTableWidget *tableWidget_circle;

    void setupUi(QWidget *CircleMenu)
    {
        if (CircleMenu->objectName().isEmpty())
            CircleMenu->setObjectName("CircleMenu");
        CircleMenu->resize(354, 674);
        verticalLayout = new QVBoxLayout(CircleMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(CircleMenu);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        comboBox_loadOrder = new QComboBox(groupBox);
        comboBox_loadOrder->addItem(QString());
        comboBox_loadOrder->addItem(QString());
        comboBox_loadOrder->setObjectName("comboBox_loadOrder");

        horizontalLayout_2->addWidget(comboBox_loadOrder);

        pushButton_splitz = new QPushButton(groupBox);
        pushButton_splitz->setObjectName("pushButton_splitz");

        horizontalLayout_2->addWidget(pushButton_splitz);

        pushButton_saveCircle = new QPushButton(groupBox);
        pushButton_saveCircle->setObjectName("pushButton_saveCircle");

        horizontalLayout_2->addWidget(pushButton_saveCircle);

        pushButton_loadCircle = new QPushButton(groupBox);
        pushButton_loadCircle->setObjectName("pushButton_loadCircle");
        pushButton_loadCircle->setToolTipDuration(-1);

        horizontalLayout_2->addWidget(pushButton_loadCircle);

        pushButton_unloadCircle = new QPushButton(groupBox);
        pushButton_unloadCircle->setObjectName("pushButton_unloadCircle");

        horizontalLayout_2->addWidget(pushButton_unloadCircle);

        pushButton_deleteCircle = new QPushButton(groupBox);
        pushButton_deleteCircle->setObjectName("pushButton_deleteCircle");

        horizontalLayout_2->addWidget(pushButton_deleteCircle);

        pushButton_removeCircle = new QPushButton(groupBox);
        pushButton_removeCircle->setObjectName("pushButton_removeCircle");

        horizontalLayout_2->addWidget(pushButton_removeCircle);


        verticalLayout->addWidget(groupBox);

        tableWidget_circle = new QTableWidget(CircleMenu);
        if (tableWidget_circle->columnCount() < 3)
            tableWidget_circle->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_circle->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_circle->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_circle->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_circle->setObjectName("tableWidget_circle");

        verticalLayout->addWidget(tableWidget_circle);


        retranslateUi(CircleMenu);

        QMetaObject::connectSlotsByName(CircleMenu);
    } // setupUi

    void retranslateUi(QWidget *CircleMenu)
    {
        CircleMenu->setWindowTitle(QCoreApplication::translate("CircleMenu", "Form", nullptr));
        groupBox->setTitle(QString());
        comboBox_loadOrder->setItemText(0, QCoreApplication::translate("CircleMenu", "All", nullptr));
        comboBox_loadOrder->setItemText(1, QCoreApplication::translate("CircleMenu", "Loaded", nullptr));

        pushButton_splitz->setText(QString());
        pushButton_saveCircle->setText(QString());
#if QT_CONFIG(tooltip)
        pushButton_loadCircle->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_loadCircle->setText(QString());
        pushButton_unloadCircle->setText(QString());
        pushButton_deleteCircle->setText(QString());
        pushButton_removeCircle->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget_circle->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CircleMenu", "CircleId", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_circle->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CircleMenu", "Circle", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_circle->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CircleMenu", "Coordinates", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CircleMenu: public Ui_CircleMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCLEMENU_H
