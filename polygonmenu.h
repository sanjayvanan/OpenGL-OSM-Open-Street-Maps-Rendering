#ifndef POLYGONMENU_H
#define POLYGONMENU_H

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
class PolygonMenu;
}

class PolygonMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PolygonMenu(QQuickWidget *quickWidget, QWidget *parent = nullptr);
    ~PolygonMenu();

public slots:
    void setWidgetState(int type);

    void loadPolygonTable(QVariant loadList);

private slots:
    void on_pushButton_splitz_clicked();

    void updatePolygonTable(QVariant polygonList, QVariant type);

    void on_pushButton_removePolygon_clicked();

    QStringList selectedRows();

    void on_pushButton_savePolygons_clicked();

    void loadPolygonGisData();

    void on_pushButton_loadpolygon_clicked();

    void on_pushButton_unloadpolygon_clicked();

    void on_tableWidget_polygon_cellDoubleClicked(int row, int column);

    void updatepolygonGisData(QString id,QString newName);

    void allDisconnects();

    void on_comboBox_loadOrder_activated(int index);

    void on_pushButton_deletepolygon_clicked();

private:
    Ui::PolygonMenu *ui;
    QQuickWidget *m_quickWidget;
    QQuickItem *qmlObject;
    QObject* funcObject;
    QObject* polygonObject;
    QMap<QString,QStringList> polygonTableMap;
    int menuType;
    QMetaObject::Connection cellChangeConnect;
};

#endif // POLYGONMENU_H
