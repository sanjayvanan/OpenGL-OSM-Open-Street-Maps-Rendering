#ifndef POINTMENU_H
#define POINTMENU_H

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
class PointMenu;
}

class PointMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PointMenu(QQuickWidget *quickWidget,QWidget *parent = nullptr);
    ~PointMenu();

private slots:

    void on_pushButton_remove_clicked();

    void on_pushButton_savePoint_clicked();

    void on_pushButton_load_clicked();

    void loadGisData();

    void on_pushButton_unload_clicked();

    void on_pushButton_delete_clicked();

    QStringList selectedRows();

    void updateGisData(QString id, QString newName);

    void allDisconnects();

    void on_tableWidget_point_cellDoubleClicked(int row, int column);

    void on_comboBox_loadOrder_activated(int index);

    void on_pushButton_splitz_clicked();

public slots:
    void updatePointMap(QVariant pointList, QVariant type);

    void loadPointTable(QVariant loadList);

    void setWidgetState(int type);

private:
    Ui::PointMenu *ui;
    QQuickWidget* m_quickWidget;
    QQuickItem *qmlObject;
    QObject* funcObject;
    QObject* pointObject;
    QMap<QString,QStringList> pointTableMap;
    int menuType;
    QMetaObject::Connection cellChangeConnect;
};

#endif // POINTMENU_H
