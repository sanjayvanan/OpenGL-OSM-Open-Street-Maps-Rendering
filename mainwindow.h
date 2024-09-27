#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIcon>
#include <QDockWidget>
#include <QQuickWidget>
#include <QQuickItem>
#include <QtSql>
#include <QSqlDatabase>
#include "pointmenu.h"
#include "linemenu.h"
#include "polygonmenu.h"
#include "circlemenu.h"
#include "databasemenu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createMainMenu();
    void createPointMenu();
    void createLineMenu();
    void createPolygonMenu();
    void createCircleMenu();
    void createDocsMenu();
    void stopDraw(bool visible);
    void closeCurrentDockWidget();
    void loadGeoData(); // Add this line
    void loadShapefile(const QString &fileName);

private:
    Ui::MainWindow *ui;
    PointMenu *pointMenu;
    LineMenu *lineMenu;
    PolygonMenu *polygonMenu;
    CircleMenu *circleMenu;
    DatabaseMenu *databaseMenu;
    //QList<QDockWidget*> dockWidgets;
    QDockWidget *currentDockWidget = nullptr;
};
#endif // MAINWINDOW_H
