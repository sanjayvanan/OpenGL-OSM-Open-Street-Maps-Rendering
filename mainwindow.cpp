#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"
#include <QFileDialog>
#include <ogrsf_frmts.h>
#include "shapefileselectiondialog.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "ogr_api.h"
#ifdef __cplusplus
}
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ZoshMap - VER1");

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    ui->quickWidget->show();

    pointMenu = new PointMenu(ui->quickWidget);
    lineMenu = new LineMenu(ui->quickWidget);
    polygonMenu = new PolygonMenu(ui->quickWidget);
    circleMenu = new CircleMenu(ui->quickWidget);
    databaseMenu = new DatabaseMenu(ui->quickWidget);

    //STARTING DATABASE MANAGER
    DatabaseManager::getInstance();

    createMainMenu();

    QObject::connect(ui->quickWidget->rootObject(), SIGNAL(dataToPoint()),
                     this, SLOT(loadGeoData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMainMenu(){
    // Creating Menus =================================================================
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    QMenu *toolMenu = menuBar()->addMenu(tr("&Tools"));
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QIcon zoomin(":/res/zoomin.ico");
    QIcon zoomout(":/res/zoomout.ico");

    // Actions for filemenu ===========================================================
    QAction *quitAction = new QAction(tr("&Quit"), this);
    fileMenu->addAction(quitAction);

    // Actions for viewmenu ===========================================================
    QAction *zoomPlusAction = new QAction(tr("&Zoom +"), this);
    zoomPlusAction->setIcon(zoomin);
    viewMenu->addAction(zoomPlusAction);

    QAction *zoomMinusAction = new QAction(tr("&Zoom -"), this);
    zoomMinusAction->setIcon(zoomout);
    viewMenu->addAction(zoomMinusAction);

    //Actions for toolmenu ============================================================
    // QAction *drawMenu = new QAction(tr("Map Mark"),this);
    // toolMenu->addAction(drawMenu);

    // QMenu *drawMap = new QMenu("Mark Map",this);
    // drawMenu->setMenu(drawMap);

    // QAction *createPoint = new QAction("Create Point",this);
    // drawMap->addAction(createPoint);
    // connect(createPoint,&QAction::triggered,this,&MainWindow::createPointMenu);

    // QAction *createLine = new QAction("Create Line",this);
    // drawMap->addAction(createLine);

    // QAction *createPolygon = new QAction("Create Polygon",this);
    // drawMap->addAction(createPolygon);

    // QAction *createCircle = new QAction("Create Circle",this);
    // drawMap->addAction(createCircle);

    QAction *pointMark = new QAction("Point Menu", this);
    toolMenu->addAction(pointMark);
    connect(pointMark,&QAction::triggered,this,&MainWindow::createPointMenu);

    QAction *lineMark = new QAction("Line Menu", this);
    toolMenu->addAction(lineMark);
    connect(lineMark,&QAction::triggered,this,&MainWindow::createLineMenu);

    QAction *polygonMark = new QAction("Polygon Menu", this);
    toolMenu->addAction(polygonMark);
    connect(polygonMark,&QAction::triggered,this,&MainWindow::createPolygonMenu);

    QAction *circleMark = new QAction("Circle Menu", this);
    toolMenu->addAction(circleMark);
    connect(circleMark,&QAction::triggered,this,&MainWindow::createCircleMenu);

    // Action for helpmenu ============================================================
    QAction *openDocs = new QAction(tr("Z-map Docs"),this);
    helpMenu->addAction(openDocs);
    connect(openDocs,&QAction::triggered,this,&MainWindow::createDocsMenu);

    // Add a new action for loading geodata
    QAction *loadGeoDataAction = new QAction(tr("&Load GeoData"), this);
    fileMenu->addAction(loadGeoDataAction);
    connect(loadGeoDataAction, &QAction::triggered, this, &MainWindow::loadGeoData);
}

void MainWindow::createPointMenu(){
    closeCurrentDockWidget();

    QDockWidget *pointmenuDock = new QDockWidget(this);
    pointmenuDock->setWindowTitle("Point Menu");
    pointmenuDock->setWidget(pointMenu);
    this->addDockWidget(Qt::RightDockWidgetArea, pointmenuDock);

    pointMenu->setWidgetState(1);
    connect(pointmenuDock, &QDockWidget::visibilityChanged, this, &MainWindow::stopDraw);
    currentDockWidget = pointmenuDock;
}

void MainWindow::createLineMenu(){

    closeCurrentDockWidget();

    QDockWidget *linemenuDock = new QDockWidget(this);
    linemenuDock->setWindowTitle("Line Menu");
    linemenuDock->setWidget(lineMenu);
    this->addDockWidget(Qt::RightDockWidgetArea, linemenuDock);

    lineMenu->setWidgetState(1);
    connect(linemenuDock, &QDockWidget::visibilityChanged, this, &MainWindow::stopDraw);
    currentDockWidget = linemenuDock;
}

void MainWindow::createPolygonMenu(){
    closeCurrentDockWidget();

    QDockWidget *polygonmenuDock = new QDockWidget(this);
    polygonmenuDock->setWindowTitle("Polygon Menu");
    polygonmenuDock->setWidget(polygonMenu);
    this->addDockWidget(Qt::RightDockWidgetArea, polygonmenuDock);

    polygonMenu->setWidgetState(1);
    connect(polygonmenuDock, &QDockWidget::visibilityChanged, this, &MainWindow::stopDraw);
    currentDockWidget = polygonmenuDock;
}

void MainWindow::createCircleMenu(){
    closeCurrentDockWidget();
    QDockWidget *circlemenuDock = new QDockWidget(this);
    circlemenuDock->setWindowTitle("Circle Menu");
    circlemenuDock->setWidget(circleMenu);
    this->addDockWidget(Qt::RightDockWidgetArea, circlemenuDock);

    circleMenu->setWidgetState(1);
    connect(circlemenuDock, &QDockWidget::visibilityChanged, this, &MainWindow::stopDraw);
    currentDockWidget = circlemenuDock;
}

void MainWindow::createDocsMenu(){
    qDebug()<<"Not Done Yet";
}

void MainWindow::closeCurrentDockWidget(){
    if (currentDockWidget && currentDockWidget->isVisible()) {
        currentDockWidget->close();
    }
    currentDockWidget = nullptr;
}

void MainWindow::stopDraw(bool visible)
{
    QDockWidget *dockWidget = qobject_cast<QDockWidget*>(sender());

    QQuickItem* qmlObject = ui->quickWidget->rootObject();
    if (!qmlObject) {
        qDebug() << "QML object is null.";
        return;
    }

    QObject* funcObject = qmlObject->findChild<QObject*>("functionspace");
    if (!funcObject) {
       qDebug() << "functionspace object is null.";
        return;
    }

    if (dockWidget) {
        if (!visible) {
            QString dockWidgetName = dockWidget->windowTitle();
            qDebug() << dockWidgetName << "is now stopDraw invisible";

            QMetaObject::invokeMethod(funcObject, "stopDraw",Q_ARG(QVariant, 0));

            // if(dockWidgetName == "Point Menu"){
            //     QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 1));
            // }
            // else if(dockWidgetName == "Line Menu"){
            //     QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 2));
            // }
            // else if(dockWidgetName == "Polygon Menu"){
            //     QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 3));
            // }
            // else if(dockWidgetName == "Circle Menu"){
            //     QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 4));
            // }
            // else{
            //     qDebug()<<"Invalid dockwidget";
            // }
        }
    }
}

void MainWindow::loadGeoData()
{
    QString rootPath = "C:/Zosh Aerospace/Materials/ENC Shapefiles";
    ShapefileSelectionDialog dialog(rootPath, this);
    
    if (dialog.exec() == QDialog::Accepted) {
        QStringList selectedFiles = dialog.getSelectedFiles();
        
        for (const QString &fileName : selectedFiles) {
            loadShapefile(fileName);
        }
    }
}

void MainWindow::loadShapefile(const QString &fileName)
{
    qDebug() << "Loading shapefile:" << fileName;

    GDALAllRegister();
    GDALDataset *poDS = (GDALDataset*) GDALOpenEx(fileName.toStdString().c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (poDS == NULL)
    {
        qDebug() << "Failed to open shapefile. Error:" << CPLGetLastErrorMsg();
        return;
    }

    qDebug() << "Shapefile opened successfully";

    OGRLayer *poLayer;
    poLayer = poDS->GetLayer(0);
    if (poLayer == NULL)
    {
        qDebug() << "Failed to get layer from shapefile";
        GDALClose(poDS);
        return;
    }

    qDebug() << "Layer name:" << poLayer->GetName();
    qDebug() << "Feature count:" << poLayer->GetFeatureCount();
    qDebug() << "Geometry type:" << OGRGeometryTypeToName(poLayer->GetGeomType());

    OGRFeature *poFeature;
    poLayer->ResetReading();
    
    QVariantList features;
    while ((poFeature = poLayer->GetNextFeature()) != NULL)
    {
        OGRGeometry *poGeometry;
        poGeometry = poFeature->GetGeometryRef();
        if (poGeometry != NULL)
        {
            QVariantMap feature;
            feature["type"] = QString(poGeometry->getGeometryName());
            feature["fileName"] = QFileInfo(fileName).fileName(); // Add file name to feature data
            
            switch (wkbFlatten(poGeometry->getGeometryType()))
            {
                case wkbPoint:
                {
                    OGRPoint *poPoint = (OGRPoint *) poGeometry;
                    feature["x"] = poPoint->getX();
                    feature["y"] = poPoint->getY();
                    features.append(feature);
                    qDebug() << "Added point from" << feature["fileName"].toString() << ":" << feature["x"].toDouble() << feature["y"].toDouble();
                    break;
                }
                case wkbLineString:
                {
                    OGRLineString *poLine = (OGRLineString *) poGeometry;
                    QVariantList points;
                    for (int i = 0; i < poLine->getNumPoints(); i++)
                    {
                        QVariantMap point;
                        point["x"] = poLine->getX(i);
                        point["y"] = poLine->getY(i);
                        points.append(point);
                    }
                    feature["points"] = points;
                    features.append(feature);
                    qDebug() << "Added linestring from" << feature["fileName"].toString() << "with" << points.size() << "points";
                    break;
                }
                case wkbPolygon:
                {
                    OGRPolygon *poPolygon = (OGRPolygon *) poGeometry;
                    OGRLinearRing *poRing = poPolygon->getExteriorRing();
                    QVariantList points;
                    for (int i = 0; i < poRing->getNumPoints(); i++)
                    {
                        QVariantMap point;
                        point["x"] = poRing->getX(i);
                        point["y"] = poRing->getY(i);
                        points.append(point);
                    }
                    feature["points"] = points;
                    features.append(feature);
                    qDebug() << "Added polygon from" << feature["fileName"].toString() << "with" << points.size() << "points";
                    break;
                }
                default:
                    qDebug() << "Unsupported geometry type:" << poGeometry->getGeometryName();
            }
        }
        else
        {
            qDebug() << "Feature has no geometry";
        }
        OGRFeature::DestroyFeature(poFeature);
    }
    GDALClose(poDS);

    qDebug() << "Loaded" << features.size() << "features";

    QQuickItem* qmlObject = ui->quickWidget->rootObject();
    if (qmlObject)
    {
        qDebug() << "Invoking renderGeoData in QML";
        QMetaObject::invokeMethod(qmlObject, "renderGeoData",
                                  Q_ARG(QVariant, QVariant::fromValue(features)));
    }
    else
    {
        qDebug() << "Failed to get QML root object";
    }
}




