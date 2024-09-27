/********************************************************************************
** Form generated from reading UI file 'polygonmenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYGONMENU_H
#define UI_POLYGONMENU_H

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

class Ui_PolygonMenu
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox_loadOrder;
    QPushButton *pushButton_splitz;
    QPushButton *pushButton_savePolygons;
    QPushButton *pushButton_loadpolygon;
    QPushButton *pushButton_unloadpolygon;
    QPushButton *pushButton_deletepolygon;
    QPushButton *pushButton_removePolygon;
    QTableWidget *tableWidget_polygon;

    void setupUi(QWidget *PolygonMenu)
    {
        if (PolygonMenu->objectName().isEmpty())
            PolygonMenu->setObjectName("PolygonMenu");
        PolygonMenu->resize(599, 592);
        verticalLayout = new QVBoxLayout(PolygonMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(PolygonMenu);
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

        pushButton_savePolygons = new QPushButton(groupBox);
        pushButton_savePolygons->setObjectName("pushButton_savePolygons");

        horizontalLayout_2->addWidget(pushButton_savePolygons);

        pushButton_loadpolygon = new QPushButton(groupBox);
        pushButton_loadpolygon->setObjectName("pushButton_loadpolygon");
        pushButton_loadpolygon->setToolTipDuration(-1);

        horizontalLayout_2->addWidget(pushButton_loadpolygon);

        pushButton_unloadpolygon = new QPushButton(groupBox);
        pushButton_unloadpolygon->setObjectName("pushButton_unloadpolygon");

        horizontalLayout_2->addWidget(pushButton_unloadpolygon);

        pushButton_deletepolygon = new QPushButton(groupBox);
        pushButton_deletepolygon->setObjectName("pushButton_deletepolygon");

        horizontalLayout_2->addWidget(pushButton_deletepolygon);

        pushButton_removePolygon = new QPushButton(groupBox);
        pushButton_removePolygon->setObjectName("pushButton_removePolygon");

        horizontalLayout_2->addWidget(pushButton_removePolygon);


        verticalLayout->addWidget(groupBox);

        tableWidget_polygon = new QTableWidget(PolygonMenu);
        if (tableWidget_polygon->columnCount() < 3)
            tableWidget_polygon->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_polygon->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_polygon->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_polygon->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_polygon->setObjectName("tableWidget_polygon");

        verticalLayout->addWidget(tableWidget_polygon);


        retranslateUi(PolygonMenu);

        QMetaObject::connectSlotsByName(PolygonMenu);
    } // setupUi

    void retranslateUi(QWidget *PolygonMenu)
    {
        PolygonMenu->setWindowTitle(QCoreApplication::translate("PolygonMenu", "Form", nullptr));
        groupBox->setTitle(QString());
        comboBox_loadOrder->setItemText(0, QCoreApplication::translate("PolygonMenu", "All", nullptr));
        comboBox_loadOrder->setItemText(1, QCoreApplication::translate("PolygonMenu", "Loaded", nullptr));

        pushButton_splitz->setText(QString());
        pushButton_savePolygons->setText(QString());
#if QT_CONFIG(tooltip)
        pushButton_loadpolygon->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_loadpolygon->setText(QString());
        pushButton_unloadpolygon->setText(QString());
        pushButton_deletepolygon->setText(QString());
        pushButton_removePolygon->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget_polygon->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PolygonMenu", "PolyId", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_polygon->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PolygonMenu", "Polygons", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_polygon->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PolygonMenu", "Coordinates", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PolygonMenu: public Ui_PolygonMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYGONMENU_H
