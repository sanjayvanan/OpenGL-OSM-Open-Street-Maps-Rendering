#ifndef CIRCLEMENU_H
#define CIRCLEMENU_H

#include <QWidget>
#include <QQuickWidget>
#include <QQuickItem>
#include <QVariant>
#include <QQuickItem>
#include <QMessageBox>
#include <QGeoCoordinate>

namespace Ui {
class CircleMenu;
}

class CircleMenu : public QWidget
{
    Q_OBJECT

public:
    explicit CircleMenu(QQuickWidget *quickWidget,QWidget *parent = nullptr);
    ~CircleMenu();

private slots:
    void on_pushButton_removeCircle_clicked();

    void on_pushButton_saveCircle_clicked();

    void on_pushButton_deleteCircle_clicked();

    void on_pushButton_loadCircle_clicked();

    void on_pushButton_unloadCircle_clicked();

    void on_pushButton_splitz_clicked();

    void on_comboBox_loadOrder_activated(int index);

    void on_tableWidget_circle_cellDoubleClicked(int row, int column);

    void allDisconnects();

    void loadCircleGisData();

    void updateCircleGisData(QString id,QString newName);

    QStringList selectedRows();

    void loadCircleTable(QVariant loadList);


public slots:
    void updateCircleTable(QVariant CircleList, QVariant type);

    void setWidgetState(int type);

private:
    Ui::CircleMenu *ui;
    QQuickWidget *m_quickWidget;
    QQuickItem *qmlObject;
    QObject* funcObject;
    QObject* circleObject;
    QMap<QString,QStringList> circleTableMap;
    int menuType;
    QMetaObject::Connection cellChangeConnect;
};

#endif // CIRCLEMENU_H
