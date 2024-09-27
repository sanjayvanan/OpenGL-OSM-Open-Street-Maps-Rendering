#include "pointmenu.h"
#include "ui_pointmenu.h"
#include "databasemanager.h"

PointMenu::PointMenu(QQuickWidget *quickWidget,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PointMenu),
    m_quickWidget(quickWidget)
{
    ui->setupUi(this);
    ui->tableWidget_point->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_point->setColumnHidden(0,true);

    qmlObject = m_quickWidget->rootObject();
    if (!qmlObject) {
        qDebug() << "QML object is null.";
        return;
    }

    pointObject = qmlObject->findChild<QObject*>("pointspace");
    if (!pointObject) {
        qDebug() << "pointspace object is null.";
        return;
    }

    funcObject = qmlObject->findChild<QObject*>("functionspace");
    if (!funcObject) {
        qDebug() << "functionspace object is null.";
        return;
    }    

    QObject::connect(qmlObject, SIGNAL(sendPointList(QVariant,QVariant)),this, SLOT(updatePointMap(QVariant,QVariant)));
    QObject::connect(qmlObject, SIGNAL(sendLoadList(QVariant)),this, SLOT(loadPointTable(QVariant)));

    //Setting Icons and ToolTips
    ui->pushButton_splitz->setText("Create Point");

    QIcon iconShow(":/res/wshow.png");
    QPixmap pixmapShow = iconShow.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_load->setIcon(pixmapShow);
    ui->pushButton_load->setToolTip("Show Points");
    ui->pushButton_load->setToolTipDuration(5000);

    QIcon iconHide(":/res/whide.png");
    QPixmap pixmapHide = iconHide.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_unload->setIcon(pixmapHide);
    ui->pushButton_unload->setToolTip("Hide Points");
    ui->pushButton_unload->setToolTipDuration(5000);

    QIcon iconSave(":/res/wsave.png");
    QPixmap pixmapSave = iconSave.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_savePoint->setIcon(pixmapSave);
    ui->pushButton_savePoint->setToolTip("Save Points");
    ui->pushButton_savePoint->setToolTipDuration(5000);

    QIcon iconRemove(":/res/wremove.png");
    QPixmap pixmapRemove = iconRemove.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_remove->setIcon(pixmapRemove);
    ui->pushButton_remove->setToolTip("Remove Points");
    ui->pushButton_remove->setToolTipDuration(5000);

    QIcon iconDelete(":/res/wdelete.png");
    QPixmap pixmapDelete = iconDelete.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_delete->setIcon(pixmapDelete);
    ui->pushButton_delete->setToolTip("Delete Points");
    ui->pushButton_delete->setToolTipDuration(5000);
}

PointMenu::~PointMenu()
{
    delete ui;
}

//*** When we close the point menu the temp points not getting deleted ==============================================

QStringList PointMenu::selectedRows(){ // Returns all selected rows
    QStringList selectedrows;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_point->selectedItems();
    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_point->item(row, 0);
        if(idItem)
        {
            QString id = idItem->text();
            selectedrows << id;
        }
    }
    selectedrows.removeDuplicates();
    ui->tableWidget_point->clearSelection();
    return selectedrows;
}

void PointMenu::on_pushButton_splitz_clicked()
{
    if(menuType == 0){
        ui->pushButton_splitz->setText("Create Point");
        setWidgetState(1);
    }
    else if(menuType == 1){
        ui->pushButton_splitz->setText("View Point");
        setWidgetState(0);
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }
}

// Set Widget mode(Create/view) ==============================================================================================

void PointMenu::setWidgetState(int type){
    menuType = type;
    ui->tableWidget_point->clearContents();
    ui->tableWidget_point->setRowCount(0);
    pointTableMap.clear();
    if(pointObject) {
        QMetaObject::invokeMethod(pointObject, "deleteAllPoints");
        //QMetaObject::invokeMethod(pointObject, "deLoadAllPoints");
    }
    if(type == 0){ // Create Points
        //Hide
        ui->pushButton_load->hide();
        ui->pushButton_unload->hide();
        ui->pushButton_delete->hide();
        ui->comboBox_loadOrder->hide();

        //show
        ui->pushButton_savePoint->show();
        ui->pushButton_remove->show();
        if(funcObject) {
           QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 1));
        }

    }
    else if(type == 1){ // Display Points
        loadGisData();
        //Show
        ui->pushButton_load->show();
        ui->pushButton_unload->show();
        ui->pushButton_delete->show();
        ui->comboBox_loadOrder->show();

        //Hide
        ui->pushButton_savePoint->hide();
        ui->pushButton_remove->hide();
        if(funcObject) {
            QMetaObject::invokeMethod(funcObject, "stopDraw",Q_ARG(QVariant, 0));
        }
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }
}

//Create Point Maker =========================================================================================================

void PointMenu::updatePointMap(QVariant pointList,QVariant type){
    QMap<QString, QVariant> markerMap = pointList.toMap();
    int typeOP = type.toInt();

    qDebug() << "markerMap" << markerMap << markerMap.size()<<typeOP;
    if(typeOP == 0){
        QList<QString> keys = markerMap.keys();
        if (!keys.isEmpty()) {
            QString lastKey = keys.last();
            QVariant lastValue = markerMap.value(lastKey);
            QObject* markerObject = lastValue.value<QObject*>();
            QVariant coordinateVariant = markerObject->property("coordinate");
            QGeoCoordinate coordinate = coordinateVariant.value<QGeoCoordinate>();

            QString coorDetails = "Latitude = " + QString::number(coordinate.latitude()) + "\nLongitude = " + QString::number(coordinate.longitude());
            pointTableMap[lastKey] = QStringList()<<"Points"<<coorDetails;
        }
        else{
            qDebug() << "The map is empty.";
        }

        qDebug()<<"pointTableMap"<<pointTableMap;
    }
    else if(typeOP == 1){
        foreach (const QString& pointId, pointTableMap.keys()) {
            if(markerMap.contains(pointId)){
                //Do Nothing
            }
            else{
                pointTableMap.remove(pointId);
            }
        }
    }
    else{
        qDebug()<<"Invalid Type of Operation";
        return;
    }

    ui->tableWidget_point->clearContents();
    ui->tableWidget_point->setRowCount(0);

    foreach (const QString& pointId, pointTableMap.keys())
    {
        //qDebug()<<"pointTableMap"<<pointTableMap[pointId];
        QStringList values = pointTableMap[pointId];
        //qDebug()<<"values"<<values[0];

        //Writing Table
        int row = ui->tableWidget_point->rowCount();
        ui->tableWidget_point->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(pointId);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_point->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(values[0]);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_point->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(values[1]);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_point->setItem(row, 2, item3);

        ui->tableWidget_point->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

void PointMenu::on_pushButton_remove_clicked()
{
    //Getting the List of Selected Rows
    QStringList removePoints;
    removePoints = selectedRows();
    if(pointObject) {
        QMetaObject::invokeMethod(pointObject, "deletePointList",Q_ARG(QVariant, removePoints));
    }
}


void PointMenu::on_pushButton_savePoint_clicked()
{
    QSqlQuery query;
    const QString pointInsertQuery = "INSERT INTO geopoint VALUES (:gpointid,:gpointname,ST_GeomFromText(:gpoint,4326));" ;
    const QString pointSelectQuery = "SELECT * FROM geopoint WHERE gpointname = :gpointname1 or gpoint = ST_GeomFromText(:gpoint1);";
    static QRegularExpression regex("Latitude = ([+-]?[0-9]+\\.[0-9]+)\\s*Longitude = ([+-]?[0-9]+\\.[0-9]+)");
    if(!pointTableMap.isEmpty()){

        if(!DatabaseManager::getInstance().isopen()){
            qCritical()<<query.lastError();
            return;
        }

        foreach (const QString& pointId, pointTableMap.keys())
        {
            QStringList values = pointTableMap[pointId];
            qDebug()<<"values"<<values[0]<<values[1];

            QRegularExpressionMatch match = regex.match(values[1]);

            if(match.hasMatch()){
                double latitudeStr = match.captured(1).toDouble();
                double longitudeStr = match.captured(2).toDouble();
                QString pointObj = QString("Point(%1 %2)").arg(latitudeStr).arg(longitudeStr);

                query.prepare(pointSelectQuery);
                query.bindValue(":gpointname1",values[0]);
                query.bindValue(":gpoint1",pointObj);
                if(!query.exec()){
                    qCritical()<<query.lastError();
                }

                if(query.next()){
                    qCritical()<<"data exsists";
                    continue;
                }

                query.prepare(pointInsertQuery);
                query.bindValue(":gpointid",pointId);
                query.bindValue(":gpointname",values[0]);
                query.bindValue(":gpoint",pointObj);

                if(!query.exec()){// IF QUERY DOES EXECUTE
                    qCritical()<<query.lastError();
                }
            }
        }
    }
    else{
        qDebug()<<"PointMap Empty nothing to add to db";
        return;
    }
}

void PointMenu::on_tableWidget_point_cellDoubleClicked(int row, int column)
{
    //qDebug()<<"row"<<row<<column<<"column";
    QString originalValue = ui->tableWidget_point->item(row, column)->text();
    ui->tableWidget_point->editItem(ui->tableWidget_point->item(row, column));

    cellChangeConnect = connect(ui->tableWidget_point, &QTableWidget::cellChanged,
    this, [this, row, column, originalValue](int currentRow, int currentColumn) {
        if(menuType == 0){
            if (row == currentRow && column == currentColumn && ui->tableWidget_point->item(row, column)->text() != originalValue) {
                QString id = ui->tableWidget_point->item(row,0)->text();
                QString newName = ui->tableWidget_point->item(row,1)->text();
                QStringList& values = pointTableMap[id];
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
            if (row == currentRow && column == currentColumn && ui->tableWidget_point->item(row, column)->text() != originalValue) {
                if(ui->tableWidget_point->rowCount()>1){
                    QString id = ui->tableWidget_point->item(row,0)->text();
                    QString newName = ui->tableWidget_point->item(row,1)->text();
                    updateGisData(id,newName);
                }
            }
            allDisconnects();
        }
        ui->tableWidget_point->clearSelection();
    });
}

void PointMenu::allDisconnects(){
    qDebug()<<"disconnect called";
    disconnect(cellChangeConnect);
}


// View Database Points =========================================================================================================

void PointMenu::updateGisData(QString id, QString newName){
    //qDebug()<<"updateGisData"<<id<<newName;
    QSqlQuery query;
    const QString pointUpdateQuery = "UPDATE geopoint SET gpointname = :gnewName WHERE gpointid = :gupdatePoint;";
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
            loadGisData();
        } else {
            qDebug()<<"Failed to update row";
        }
    }

}

void PointMenu::loadGisData(){
    ui->tableWidget_point->clearContents();
    ui->tableWidget_point->setRowCount(0);
    pointTableMap.clear();

    QSqlQuery query;
    const QString pointSelectQuery = "Select gpointid,gpointname,ST_AsText(gpoint) from geopoint;";
    static QRegularExpression regex("POINT\\(([^ ]+) ([^ ]+)\\)");

    if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
        qCritical()<<query.lastError();
        return;
    }
    if(!query.exec(pointSelectQuery)){
        qCritical()<<query.lastError();
        return;
    }
    while (query.next()) {
        qint64 gpointid = query.value(0).toLongLong();
        QString gpointname = query.value(1).toString();
        QString gpointtext = query.value(2).toString();
        QRegularExpressionMatch match = regex.match(gpointtext);
        if(match.hasMatch()){
            QString latitude = match.captured(1);
            QString longitude = match.captured(2);
            QString coorDetails = "Latitude = " + latitude + "\nLongitude = " + longitude;

            //Writing Table
            int row = ui->tableWidget_point->rowCount();
            ui->tableWidget_point->insertRow(row);

            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(gpointid));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_point->setItem(row, 0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem(gpointname);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_point->setItem(row, 1, item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(coorDetails);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_point->setItem(row, 2, item3);
            ui->tableWidget_point->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
    }
}


void PointMenu::loadPointTable(QVariant loadList){
    ui->tableWidget_point->clearContents();
    ui->tableWidget_point->setRowCount(0);
    pointTableMap.clear();

    QMap<QString, QVariant> markerMap = loadList.toMap();
    qDebug()<<"markerMap"<<markerMap.size();
    QList<QString> keys = markerMap.keys();

    QSqlQuery query;
    const QString pointSelectQuery = "SELECT gpointid,gpointname,ST_AsText(gpoint) FROM geopoint WHERE gpointid=:gpointkey;";
    static QRegularExpression regex("POINT\\(([^ ]+) ([^ ]+)\\)");

    if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
        qCritical()<<query.lastError();
        return;
    }

    foreach (const QString &key, keys) {
        qDebug()<<"Keys"<<key;
        query.prepare(pointSelectQuery);
        query.bindValue(":gpointkey",key);
        if (!query.exec()) {
            qCritical() << query.lastError();
            continue;
        }
        if (!query.next()) {
            qWarning() << "No results found for key" << key;
            continue;
        }
        qint64 gpointid = query.value(0).toLongLong();
        QString gpointname = query.value(1).toString();
        QString gpointtext = query.value(2).toString();
        QRegularExpressionMatch match = regex.match(gpointtext);
        if(match.hasMatch()){
            QString latitude = match.captured(1);
            QString longitude = match.captured(2);
            QString coorDetails = "Latitude = " + latitude + "\nLongitude = " + longitude;

            //Writing Table
            int row = ui->tableWidget_point->rowCount();
            ui->tableWidget_point->insertRow(row);

            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(gpointid));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_point->setItem(row, 0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem(gpointname);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_point->setItem(row, 1, item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(coorDetails);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_point->setItem(row, 2, item3);
            ui->tableWidget_point->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
    }
}

void PointMenu::on_pushButton_delete_clicked()
{
    QStringList deletePoints;
    deletePoints = selectedRows();
    if(!deletePoints.isEmpty())
    {
        QSqlQuery query;
        const QString pointDeleteQuery = "DELETE FROM geopoint WHERE gpointid = :deletepointid;";
        bool deletionSuccessful = true;
        if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
            qCritical()<<query.lastError();
            return;
        }

        for(int i=0; i<deletePoints.length(); i++){
            query.prepare(pointDeleteQuery);
            query.bindValue(":deletepointid",deletePoints[i]);

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
            loadGisData();
            if(pointObject) {
               QMetaObject::invokeMethod(pointObject, "deLoadPointList",Q_ARG(QVariant, deletePoints));
                if(ui->comboBox_loadOrder->currentIndex() == 1){
                    QMetaObject::invokeMethod(pointObject, "sendLoadedPoints");
                }
            }
        }
    }
    else{
        qDebug()<<"Nothing to Delete";
    }
}

void PointMenu::on_pushButton_load_clicked()
{
    QStringList loadPoints;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_point->selectedItems();
    static QRegularExpression regex("Latitude = ([+-]?[0-9]+\\.[0-9]+)\\s*Longitude = ([+-]?[0-9]+\\.[0-9]+)");
    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_point->item(row, 0);
        QTableWidgetItem* coorItem = ui->tableWidget_point->item(row,2);
        if(idItem && coorItem)
        {
            QString id = idItem->text();
            QString coord = coorItem->text();
            QRegularExpressionMatch match = regex.match(coord);
            if(match.hasMatch()){
                QString latitudeStr = match.captured(1);
                QString longitudeStr = match.captured(2);
                QString load = id+"|"+latitudeStr+"|"+longitudeStr;
                loadPoints << load;
            }
        }
    }
    loadPoints.removeDuplicates();
    if(pointObject) {
        QMetaObject::invokeMethod(pointObject, "loadPointList",Q_ARG(QVariant, loadPoints));
    }
    ui->tableWidget_point->clearSelection();
}

void PointMenu::on_pushButton_unload_clicked()
{
    QStringList unloadPoints;
    unloadPoints = selectedRows();
    if(pointObject) {
        QMetaObject::invokeMethod(pointObject, "deLoadPointList",Q_ARG(QVariant, unloadPoints));
        if(ui->comboBox_loadOrder->currentIndex() == 1){
            QMetaObject::invokeMethod(pointObject, "sendLoadedPoints");
        }
    }
}

void PointMenu::on_comboBox_loadOrder_activated(int index)
{
    qDebug()<<"index"<<index;
    if(index == 0){
        loadGisData();
    }
    else if(index == 1){
        qDebug()<<"loaded values";
        if(pointObject) {
            QMetaObject::invokeMethod(pointObject, "sendLoadedPoints");
        }
    }
    else{
        qDebug()<<"invalid index";
    }
}




