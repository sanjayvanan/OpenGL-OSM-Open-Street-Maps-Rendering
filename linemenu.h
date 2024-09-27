#ifndef LINEMENU_H
#define LINEMENU_H

#include <QWidget>
#include <QQuickWidget>
#include <QQuickItem>
#include <QVariant>
#include <QQuickItem>
#include <QMessageBox>
#include <QGeoCoordinate>
#include <QTableWidgetItem>
#include <QStringList>
#include <QIcon>

namespace Ui {
class LineMenu;
}

class LineMenu : public QWidget
{
    Q_OBJECT

public:
    explicit LineMenu(QQuickWidget *quickWidegt, QWidget *parent = nullptr);
    ~LineMenu();

private slots:
    void on_pushButton_saveLines_clicked();

    void on_pushButton_removeLines_clicked();

    void on_pushButton_splitz_clicked();

    QStringList selectedRows();

    void loadLineGisData();

    void on_pushButton_loadLines_clicked();

    void on_pushButton_unloadLines_clicked();

    void on_tableWidget_line_cellDoubleClicked(int row, int column);

    void allDisconnects();

    void updateLineGisData(QString id, QString newName);

    void on_pushButton_deleteLines_clicked();

    void on_comboBox_loadOrder_activated(int index);

public slots:
    void updateLineTable(QVariant lineList, QVariant type);

    void setWidgetState(int type);

    void loadlineTable(QVariant loadList);

private:
    Ui::LineMenu *ui;
    QQuickWidget *m_quickWidget;
    QQuickItem *qmlObject;
    QObject* funcObject;
    QObject* lineObject;
    QMap<QString,QStringList> lineTableMap;
    int menuType;
    QMetaObject::Connection cellChangeConnect;
};

#endif // LINEMENU_H
