#include "polygonmenu.h"
#include "ui_polygonmenu.h"
#include "databasemanager.h"

PolygonMenu::PolygonMenu(QQuickWidget *quickWidget,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PolygonMenu),
    m_quickWidget(quickWidget)
{
    ui->setupUi(this);

    ui->tableWidget_polygon->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_polygon->setColumnHidden(0,true);

    qmlObject = m_quickWidget->rootObject();
    if (!qmlObject) {
        qDebug() << "QML object is null.";
        return;
    }

    polygonObject = qmlObject->findChild<QObject*>("polygonspace");
    if (!polygonObject) {
        qDebug() << "pointspace object is null.";
        return;
    }

    funcObject = qmlObject->findChild<QObject*>("functionspace");
    if (!funcObject) {
        qDebug() << "functionspace object is null.";
        return;
    }

    QObject::connect(qmlObject, SIGNAL(sendPolygonList(QVariant,QVariant)),this, SLOT(updatePolygonTable(QVariant,QVariant)));
    QObject::connect(qmlObject, SIGNAL(sendpolygonLoadList(QVariant)),this, SLOT(loadPolygonTable(QVariant)));

    ui->pushButton_splitz->setText("Create Polygon");

    QIcon iconShow(":/res/wshow.png");
    QPixmap pixmapShow = iconShow.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_loadpolygon->setIcon(pixmapShow);
    ui->pushButton_loadpolygon->setToolTip("Show Polygon");
    ui->pushButton_loadpolygon->setToolTipDuration(5000);

    QIcon iconHide(":/res/whide.png");
    QPixmap pixmapHide = iconHide.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_unloadpolygon->setIcon(pixmapHide);
    ui->pushButton_unloadpolygon->setToolTip("Hide Polygon");
    ui->pushButton_unloadpolygon->setToolTipDuration(5000);

    QIcon iconSave(":/res/wsave.png");
    QPixmap pixmapSave = iconSave.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_savePolygons->setIcon(pixmapSave);
    ui->pushButton_savePolygons->setToolTip("Save Polygon");
    ui->pushButton_savePolygons->setToolTipDuration(5000);

    QIcon iconRemove(":/res/wremove.png");
    QPixmap pixmapRemove = iconRemove.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_removePolygon->setIcon(pixmapRemove);
    ui->pushButton_removePolygon->setToolTip("Remove Polygon");
    ui->pushButton_removePolygon->setToolTipDuration(5000);

    QIcon iconDelete(":/res/wdelete.png");
    QPixmap pixmapDelete = iconDelete.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_deletepolygon->setIcon(pixmapDelete);
    ui->pushButton_deletepolygon->setToolTip("Delete Polygon");
    ui->pushButton_deletepolygon->setToolTipDuration(5000);
}

PolygonMenu::~PolygonMenu()
{
    delete ui;
}

QStringList PolygonMenu::selectedRows(){ // Returns all selected rows
    QStringList selectedrows;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_polygon->selectedItems();
    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_polygon->item(row, 0);
        if(idItem)
        {
            QString id = idItem->text();
            selectedrows << id;
        }
    }
    selectedrows.removeDuplicates();
    ui->tableWidget_polygon->clearSelection();
    return selectedrows;
}


void PolygonMenu::on_pushButton_splitz_clicked()
{
    if(menuType == 0){
        ui->pushButton_splitz->setText("Create Polygon");
        setWidgetState(1);
    }
    else if(menuType == 1){
        ui->pushButton_splitz->setText("View Polygon");
        setWidgetState(0);
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }
}

// Set Widget mode(Create/view) ==============================================================================================

void PolygonMenu::setWidgetState(int type)
{
    menuType = type;
    ui->tableWidget_polygon->clearContents();
    ui->tableWidget_polygon->setRowCount(0);
    polygonTableMap.clear();
    if(polygonObject) {
        QMetaObject::invokeMethod(polygonObject, "deleteAllPolygon");
    }
    if(type == 0){ // Create polygons
        //Hide
        ui->pushButton_loadpolygon->hide();
        ui->pushButton_unloadpolygon->hide();
        ui->pushButton_deletepolygon->hide();
        ui->comboBox_loadOrder->hide();

        //show
        ui->pushButton_savePolygons->show();
        ui->pushButton_removePolygon->show();
        if(funcObject) {
            QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 3));
        }

    }
    else if(type == 1){ // Display polygons
        loadPolygonGisData();
        //Show
        ui->pushButton_loadpolygon->show();
        ui->pushButton_unloadpolygon->show();
        ui->pushButton_deletepolygon->show();
        ui->comboBox_loadOrder->show();

        //Hide
        ui->pushButton_savePolygons->hide();
        ui->pushButton_removePolygon->hide();
        if(funcObject) {
            QMetaObject::invokeMethod(funcObject, "stopDraw",Q_ARG(QVariant, 0));
        }
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }
}

//Create polygon Maker =========================================================================================================

void PolygonMenu::updatePolygonTable(QVariant polygonList,QVariant type) {
    int typeOP = type.toInt();
    QMap<QString, QVariant> markerMap = polygonList.toMap();
    //qDebug() << "markerMap" << markerMap << markerMap.size();

    if(typeOP == 0){
        QList<QString> keys = markerMap.keys();
        if (!keys.isEmpty()) {
            QString lastKey = keys.last();
            QVariant polygonVariant = markerMap.value(lastKey);
            QObject* polygonObject = polygonVariant.value<QObject*>();

            QVariantList path = polygonObject->property("path").toList();

            QString allPolygons;

            int PolygonIndex = 1;
            for (const QVariant& coordinateVariant : path) {
                QGeoCoordinate coordinate = coordinateVariant.value<QGeoCoordinate>();
                QString onePolygon = "Point " + QString::number(PolygonIndex) + "\n";
                onePolygon += "Latitude = " + QString::number(coordinate.latitude()) + "\n";
                onePolygon += "Longitude = " + QString::number(coordinate.longitude()) + "\n\n";
                PolygonIndex ++;
                allPolygons+=onePolygon;
            }
            polygonTableMap[lastKey] = QStringList()<<"Polygon"<<allPolygons;
        }
        else{
            qDebug() << "The map is empty.";
        }
    }
    else if(typeOP == 1){
        foreach (const QString& polygonId, polygonTableMap.keys()) {
            if(markerMap.contains(polygonId)){
                //Do Nothing
            }
            else{
                polygonTableMap.remove(polygonId);
            }
        }
    }
    else{
        qDebug()<<"Invalid Type of Operation";
        return;
    }

    ui->tableWidget_polygon->clearContents();
    ui->tableWidget_polygon->setRowCount(0);

    foreach (const QString& polygonId, polygonTableMap.keys())
    {
        QStringList values = polygonTableMap[polygonId];

        int row = ui->tableWidget_polygon->rowCount();
        ui->tableWidget_polygon->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(polygonId);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(values[0]);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(values[1]);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 2, item3);
        ui->tableWidget_polygon->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}


void PolygonMenu::on_pushButton_removePolygon_clicked()
{
    QStringList removePolygon;
    removePolygon = selectedRows();
    qDebug()<<"removepolygons"<<removePolygon;

   if(polygonObject) {
        QMetaObject::invokeMethod(polygonObject, "deletePolygonList",Q_ARG(QVariant, removePolygon));
   }
}

void PolygonMenu::on_pushButton_savePolygons_clicked()
{
    QSqlQuery query;
    const QString polygonInsertQuery = "INSERT INTO geopolygon VALUES(:geopolygonid,:geopolygonname,ST_GeomFromText(:gpolygon,4326));";
    const QString polygonSelectQuery = "SELECT * FROM geopolygon WHERE gpolygonname = :gpolygonname1 OR gpolygon = ST_GeomFromText(:gpolygon1);";
    //static QRegularExpression regexpolygonstring(R"(\bLatitude\s*=\s*([\d\.]+)\s*Longitude\s*=\s*([\d\.]+)\b)");
    static QRegularExpression regexpolygonstring(R"(\bLatitude\s*=\s*(-?[\d\.]+)\s*Longitude\s*=\s*(-?[\d\.]+)\b)");

    if(!polygonTableMap.isEmpty()){
        if(!DatabaseManager::getInstance().isopen()){
            qCritical()<<query.lastError();
            return;
        }

        foreach (const QString& polygonId, polygonTableMap.keys())
        {
            QStringList values = polygonTableMap[polygonId];
            QRegularExpressionMatchIterator matchIterator = regexpolygonstring.globalMatch(values[1]);
            QString polygonstring;
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                if (match.hasMatch()) {
                    QString latitude = match.captured(1);
                    QString longitude = match.captured(2);
                    polygonstring += latitude + " " + longitude + ",";
                }
            }
            if (!polygonstring.isEmpty()) {
                polygonstring.chop(1);
                polygonstring += "," + polygonstring.split(",").first();
                polygonstring = "POLYGON((" + polygonstring + "))";
                qDebug()<<"polystring"<<polygonstring.toStdString();
            }

            query.prepare(polygonSelectQuery);
            query.bindValue(":gpolygonname1",values[0]);
            query.bindValue(":gpolygon1",polygonstring);
            if(!query.exec()){
                qCritical()<<query.lastError();
            }

            if(query.next()){
                qCritical()<<"data exsists";
                continue;
            }

            query.prepare(polygonInsertQuery);
            query.bindValue(":geopolygonid",polygonId);
            query.bindValue(":geopolygonname",values[0]);
            query.bindValue(":gpolygon",polygonstring);

            if(!query.exec()){
                qCritical()<<query.lastError();
            }
        }
    }
}

void PolygonMenu::on_tableWidget_polygon_cellDoubleClicked(int row, int column)
{
    QString originalValue = ui->tableWidget_polygon->item(row, column)->text();
    ui->tableWidget_polygon->editItem(ui->tableWidget_polygon->item(row, column));

    cellChangeConnect = connect(ui->tableWidget_polygon, &QTableWidget::cellChanged,
    this, [this, row, column, originalValue](int currentRow, int currentColumn) {
        if(menuType == 0){
            if (row == currentRow && column == currentColumn && ui->tableWidget_polygon->item(row, column)->text() != originalValue) {
                QString id = ui->tableWidget_polygon->item(row,0)->text();
                QString newName = ui->tableWidget_polygon->item(row,1)->text();
                QStringList& values = polygonTableMap[id];
                if (!values.isEmpty()) {
                    values[0] = newName;
                }
                else{
                    qDebug()<<"cellchanged nothing";
                }
            }
            allDisconnects();
        }
        else if(menuType == 1){
            qDebug()<<"update Called";
            if (row == currentRow && column == currentColumn && ui->tableWidget_polygon->item(row, column)->text() != originalValue) {
                if(ui->tableWidget_polygon->rowCount()>1){
                    QString id = ui->tableWidget_polygon->item(row,0)->text();
                    QString newName = ui->tableWidget_polygon->item(row,1)->text();
                    updatepolygonGisData(id,newName);
                }
            }
            allDisconnects();
        }
        ui->tableWidget_polygon->clearSelection();
    });
}

void PolygonMenu::allDisconnects(){
    disconnect(cellChangeConnect);
}

// View Database Polygon =========================================================================================================

void PolygonMenu::updatepolygonGisData(QString id,QString newName){
    QSqlQuery query;
    const QString pointUpdateQuery = "UPDATE geopolygon SET gpolygonname = :gnewName WHERE gpolygonid = :gupdatePoint;";
    if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
        qCritical()<<query.lastError();
        return;
    }

    query.prepare(pointUpdateQuery);
    query.bindValue(":gupdatePoint",id);
    query.bindValue(":gnewName",newName);
    if (!query.exec()) {
        qCritical() << query.lastError();
    } else {
        int rowsAffected = query.numRowsAffected();
        if (rowsAffected > 0) {
            qDebug()<<"Success Row updated";
            loadPolygonGisData();
        } else {
            qDebug()<<"Failed to update row";
        }
    }
}

void PolygonMenu::loadPolygonGisData() {
    ui->tableWidget_polygon->clearContents();
    ui->tableWidget_polygon->setRowCount(0);
    polygonTableMap.clear();

    QSqlQuery query;
    const QString polygonSelectQuery = "SELECT gpolygonid, gpolygonname, ST_AsText(gpolygon) FROM geopolygon;";
    static QRegularExpression rx("(-?\\d+\\.\\d+)\\s(-?\\d+\\.\\d+)");

    if (!DatabaseManager::getInstance().isopen()) {
        qCritical() << query.lastError();
        return;
    }

    if (!query.exec(polygonSelectQuery)) {
        qCritical() << query.lastError();
        return;
    }

    while (query.next()) {
        qint64 gpolygonid = query.value(0).toLongLong();
        QString gpolygonname = query.value(1).toString();
        QString gpolygontext = query.value(2).toString();
        qDebug() << "gpolygontext" << gpolygontext;

        QString allPoints;
        int pointCount = 1;

        QRegularExpressionMatchIterator pointIt = rx.globalMatch(gpolygontext);
        while (pointIt.hasNext()) {
            QRegularExpressionMatch match = pointIt.next();
            QString lat = match.captured(1);
            QString lng = match.captured(2);
            qDebug() << "Latitude: " << lat << ", Longitude: " << lng;

            QString onePoint = "Point " + QString::number(pointCount) + "\n";
            onePoint += "Latitude = " + lat + "\n";
            onePoint += "Longitude = " + lng + "\n\n";
            allPoints+=onePoint;
            pointCount++;
        }

        int row = ui->tableWidget_polygon->rowCount();
        ui->tableWidget_polygon->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(gpolygonid));
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(gpolygonname);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(allPoints);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 2, item3);
        ui->tableWidget_polygon->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

void PolygonMenu::loadPolygonTable(QVariant loadList){
    ui->tableWidget_polygon->clearContents();
    ui->tableWidget_polygon->setRowCount(0);
    polygonTableMap.clear();

    QMap<QString, QVariant> markerMap = loadList.toMap();
    qDebug()<<"markerMap"<<markerMap.size();
    QList<QString> keys = markerMap.keys();

    QSqlQuery query;
    const QString polygonSelectQuery = "SELECT gpolygonid, gpolygonname, ST_AsText(gpolygon) FROM geopolygon WHERE gpolygonid = :gpolygonkey;";
    static QRegularExpression rx("(-?\\d+\\.\\d+)\\s(-?\\d+\\.\\d+)");

    if (!DatabaseManager::getInstance().isopen()) {
        qCritical() << query.lastError();
        return;
    }

    foreach (const QString &key, keys) {
        qDebug()<<"Keys"<<key;
        query.prepare(polygonSelectQuery);
        query.bindValue(":gpolygonkey",key);
        if (!query.exec()) {
            qCritical() << query.lastError();
            continue;
        }
        if (!query.next()) {
            qWarning() << "No results found for key" << key;
            continue;
        }
        qint64 gpolygonid = query.value(0).toLongLong();
        QString gpolygonname = query.value(1).toString();
        QString gpolygontext = query.value(2).toString();

        QString allPoints;
        int pointCount = 1;

        QRegularExpressionMatchIterator pointIt = rx.globalMatch(gpolygontext);
        while (pointIt.hasNext()) {
            QRegularExpressionMatch match = pointIt.next();
            QString lat = match.captured(1);
            QString lng = match.captured(2);
            qDebug() << "Latitude: " << lat << ", Longitude: " << lng;

            QString onePoint = "Point " + QString::number(pointCount) + "\n";
            onePoint += "Latitude = " + lat + "\n";
            onePoint += "Longitude = " + lng + "\n\n";
            allPoints+=onePoint;
            pointCount++;
        }

        int row = ui->tableWidget_polygon->rowCount();
        ui->tableWidget_polygon->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(gpolygonid));
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(gpolygonname);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(allPoints);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_polygon->setItem(row, 2, item3);
        ui->tableWidget_polygon->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

void PolygonMenu::on_pushButton_deletepolygon_clicked()
{
    QStringList deletepolygons;
    deletepolygons = selectedRows();
    if(!deletepolygons.isEmpty())
    {
        QSqlQuery query;
        const QString polygonDeleteQuery = "DELETE FROM geopolygon WHERE gpolygonid = :deletepolygonid;";
        bool deletionSuccessful = true;
        if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
            qCritical()<<query.lastError();
            return;
        }
        for(int i=0; i<deletepolygons.length(); i++){
            query.prepare(polygonDeleteQuery);
            query.bindValue(":deletepolygonid",deletepolygons[i]);

            if (!query.exec()) {
                qCritical() << query.lastError();
                deletionSuccessful = false;
                QMessageBox::critical(this, "Error", "Failed to delete row: " + query.lastError().text());
            } else {
                int rowsAffected = query.numRowsAffected();
                if (rowsAffected > 0) {
                    qDebug()<<"Success Row Deleted";
                } else {
                    qDebug()<<"Failed to delete row";// This will show everytime error will come fix it for once : partially fixed
                }
            }
        }
        if(deletionSuccessful) {
            loadPolygonGisData();
            if(polygonObject) {
                QMetaObject::invokeMethod(polygonObject, "deLoadPolygonList",Q_ARG(QVariant, deletepolygons));
                if(ui->comboBox_loadOrder->currentIndex() == 1){
                    QMetaObject::invokeMethod(polygonObject, "sendLoadedpolygon");
                }
            }
        }
    }
    else{
        qDebug()<<"Nothing to Delete";
    }
}

void PolygonMenu::on_pushButton_loadpolygon_clicked()
{
    QStringList Loadpolygons;
    QMap<QString,QString> loadpolygons;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_polygon->selectedItems();
    //static QRegularExpression regexpolygonstring(R"(\bLatitude\s*=\s*([\d\.]+)\s*Longitude\s*=\s*([\d\.]+)\b)");
    static QRegularExpression regexpolygonstring(R"(\bLatitude\s*=\s*(-?[\d\.]+)\s*Longitude\s*=\s*(-?[\d\.]+)\b)");

    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_polygon->item(row, 0);
        QTableWidgetItem* coorItem = ui->tableWidget_polygon->item(row,2);
        if(idItem && coorItem)
        {
            QString id = idItem->text();
            QString coord = coorItem->text();
            QRegularExpressionMatchIterator matchIterator = regexpolygonstring.globalMatch(coord);
            QString polygonstring;
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                if (match.hasMatch()) {
                    QString latitude = match.captured(1);
                    QString longitude = match.captured(2);
                    if (!polygonstring.isEmpty()) {
                        polygonstring += "|";
                    }
                    polygonstring += latitude + "," + longitude;
                }
            }
            if (!polygonstring.isEmpty()) {
                QString mpolygonString = polygonstring.left(polygonstring.lastIndexOf("|"));
                qDebug()<<"polygonstring"<<mpolygonString;
                Loadpolygons<<mpolygonString;
                loadpolygons[id] = mpolygonString;
            }
        }
    }
    Loadpolygons.removeDuplicates();
    if (polygonObject) {
        QVariantMap loadpolygonsMap;
        for (auto it = loadpolygons.begin(); it != loadpolygons.end(); ++it) {
            loadpolygonsMap.insert(it.key(), it.value());
        }
        QVariant loadpolygonsVariant(loadpolygonsMap);
        QMetaObject::invokeMethod(polygonObject, "loadpolygonList", Q_ARG(QVariant, loadpolygonsVariant));
    }
}

void PolygonMenu::on_pushButton_unloadpolygon_clicked()
{
    QStringList unloadPolygon;
    unloadPolygon = selectedRows();
    if(polygonObject){
        QMetaObject::invokeMethod(polygonObject, "deLoadPolygonList", Q_ARG(QVariant, unloadPolygon));
        if(ui->comboBox_loadOrder->currentIndex() == 1){
            QMetaObject::invokeMethod(polygonObject, "sendLoadedpolygon");
        }
    }
}

void PolygonMenu::on_comboBox_loadOrder_activated(int index)
{
    qDebug()<<"index"<<index;
    if(index == 0){
        loadPolygonGisData();
    }
    else if(index == 1){
        qDebug()<<"loaded values";
        if(polygonObject) {
            QMetaObject::invokeMethod(polygonObject, "sendLoadedpolygon");
        }
    }
    else{
        qDebug()<<"invalid index";
    }
}



