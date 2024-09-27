/********************************************************************************
** Form generated from reading UI file 'linemenu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEMENU_H
#define UI_LINEMENU_H

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

class Ui_LineMenu
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_loadOrder;
    QPushButton *pushButton_splitz;
    QPushButton *pushButton_saveLines;
    QPushButton *pushButton_loadLines;
    QPushButton *pushButton_unloadLines;
    QPushButton *pushButton_deleteLines;
    QPushButton *pushButton_removeLines;
    QTableWidget *tableWidget_line;

    void setupUi(QWidget *LineMenu)
    {
        if (LineMenu->objectName().isEmpty())
            LineMenu->setObjectName("LineMenu");
        LineMenu->resize(561, 461);
        verticalLayout = new QVBoxLayout(LineMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(LineMenu);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        comboBox_loadOrder = new QComboBox(groupBox);
        comboBox_loadOrder->addItem(QString());
        comboBox_loadOrder->addItem(QString());
        comboBox_loadOrder->setObjectName("comboBox_loadOrder");

        horizontalLayout->addWidget(comboBox_loadOrder);

        pushButton_splitz = new QPushButton(groupBox);
        pushButton_splitz->setObjectName("pushButton_splitz");

        horizontalLayout->addWidget(pushButton_splitz);

        pushButton_saveLines = new QPushButton(groupBox);
        pushButton_saveLines->setObjectName("pushButton_saveLines");

        horizontalLayout->addWidget(pushButton_saveLines);

        pushButton_loadLines = new QPushButton(groupBox);
        pushButton_loadLines->setObjectName("pushButton_loadLines");
        pushButton_loadLines->setToolTipDuration(-1);

        horizontalLayout->addWidget(pushButton_loadLines);

        pushButton_unloadLines = new QPushButton(groupBox);
        pushButton_unloadLines->setObjectName("pushButton_unloadLines");

        horizontalLayout->addWidget(pushButton_unloadLines);

        pushButton_deleteLines = new QPushButton(groupBox);
        pushButton_deleteLines->setObjectName("pushButton_deleteLines");

        horizontalLayout->addWidget(pushButton_deleteLines);

        pushButton_removeLines = new QPushButton(groupBox);
        pushButton_removeLines->setObjectName("pushButton_removeLines");

        horizontalLayout->addWidget(pushButton_removeLines);


        verticalLayout->addWidget(groupBox);

        tableWidget_line = new QTableWidget(LineMenu);
        if (tableWidget_line->columnCount() < 3)
            tableWidget_line->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_line->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_line->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_line->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_line->setObjectName("tableWidget_line");

        verticalLayout->addWidget(tableWidget_line);


        retranslateUi(LineMenu);

        QMetaObject::connectSlotsByName(LineMenu);
    } // setupUi

    void retranslateUi(QWidget *LineMenu)
    {
        LineMenu->setWindowTitle(QCoreApplication::translate("LineMenu", "Form", nullptr));
        groupBox->setTitle(QString());
        comboBox_loadOrder->setItemText(0, QCoreApplication::translate("LineMenu", "All", nullptr));
        comboBox_loadOrder->setItemText(1, QCoreApplication::translate("LineMenu", "Loaded", nullptr));

        pushButton_splitz->setText(QCoreApplication::translate("LineMenu", "Create Line", nullptr));
        pushButton_saveLines->setText(QString());
#if QT_CONFIG(tooltip)
        pushButton_loadLines->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pushButton_loadLines->setText(QString());
        pushButton_unloadLines->setText(QString());
        pushButton_deleteLines->setText(QString());
        pushButton_removeLines->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget_line->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LineMenu", "LineId", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_line->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LineMenu", "Lines", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_line->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LineMenu", "Coordinates", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LineMenu: public Ui_LineMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEMENU_H
