/********************************************************************************
** Form generated from reading UI file 'pointmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTMENU_H
#define UI_POINTMENU_H

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

class Ui_PointMenu
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox_loadOrder;
    QPushButton *pushButton_splitz;
    QPushButton *pushButton_load;
    QPushButton *pushButton_unload;
    QPushButton *pushButton_savePoint;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_remove;
    QTableWidget *tableWidget_point;

    void setupUi(QWidget *PointMenu)
    {
        if (PointMenu->objectName().isEmpty())
            PointMenu->setObjectName("PointMenu");
        PointMenu->resize(495, 519);
        verticalLayout = new QVBoxLayout(PointMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(PointMenu);
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

        pushButton_load = new QPushButton(groupBox);
        pushButton_load->setObjectName("pushButton_load");
        pushButton_load->setToolTipDuration(-1);

        horizontalLayout_2->addWidget(pushButton_load);

        pushButton_unload = new QPushButton(groupBox);
        pushButton_unload->setObjectName("pushButton_unload");

        horizontalLayout_2->addWidget(pushButton_unload);

        pushButton_savePoint = new QPushButton(groupBox);
        pushButton_savePoint->setObjectName("pushButton_savePoint");

        horizontalLayout_2->addWidget(pushButton_savePoint);

        pushButton_delete = new QPushButton(groupBox);
        pushButton_delete->setObjectName("pushButton_delete");

        horizontalLayout_2->addWidget(pushButton_delete);

        pushButton_remove = new QPushButton(groupBox);
        pushButton_remove->setObjectName("pushButton_remove");

        horizontalLayout_2->addWidget(pushButton_remove);


        verticalLayout->addWidget(groupBox);

        tableWidget_point = new QTableWidget(PointMenu);
        if (tableWidget_point->columnCount() < 3)
            tableWidget_point->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_point->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_point->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_point->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_point->setObjectName("tableWidget_point");

        verticalLayout->addWidget(tableWidget_point);


        retranslateUi(PointMenu);

        QMetaObject::connectSlotsByName(PointMenu);
    } // setupUi

    void retranslateUi(QWidget *PointMenu)
    {
        PointMenu->setWindowTitle(QCoreApplication::translate("PointMenu", "Form", nullptr));
        groupBox->setTitle(QString());
        comboBox_loadOrder->setItemText(0, QCoreApplication::translate("PointMenu", "All", nullptr));
        comboBox_loadOrder->setItemText(1, QCoreApplication::translate("PointMenu", "Loaded", nullptr));

        pushButton_splitz->setText(QCoreApplication::translate("PointMenu", "Create Point", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_load->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_load->setText(QString());
        pushButton_unload->setText(QString());
        pushButton_savePoint->setText(QString());
        pushButton_delete->setText(QString());
        pushButton_remove->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget_point->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PointMenu", "pointId", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_point->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PointMenu", "Point", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_point->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PointMenu", "Coordinates", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PointMenu: public Ui_PointMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTMENU_H
