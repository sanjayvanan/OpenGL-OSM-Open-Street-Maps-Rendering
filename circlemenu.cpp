#include "circlemenu.h"
#include "ui_circlemenu.h"
#include "databasemanager.h"

CircleMenu::CircleMenu(QQuickWidget *quickWidget,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CircleMenu),
    m_quickWidget(quickWidget)
{
    ui->setupUi(this);

    ui->tableWidget_circle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_circle->setColumnHidden(0,true);
    qmlObject = m_quickWidget->rootObject();
    if (!qmlObject) {
        qDebug() << "QML object is null.";
        return;
    }

    circleObject = qmlObject->findChild<QObject*>("circlespace");
    if (!circleObject) {
        qDebug() << "pointspace object is null.";
        return;
    }

    funcObject = qmlObject->findChild<QObject*>("functionspace");
    if (!funcObject) {
        qDebug() << "functionspace object is null.";
        return;
    }
    QObject::connect(qmlObject, SIGNAL(sendCircleList(QVariant,QVariant)),this, SLOT(updateCircleTable(QVariant,QVariant)));
    QObject::connect(qmlObject, SIGNAL(sendCircleLoadList(QVariant)),this, SLOT(loadCircleTable(QVariant)));

    ui->pushButton_splitz->setText("Create Circle");

    QIcon iconShow(":/res/wshow.png");
    QPixmap pixmapShow = iconShow.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_loadCircle->setIcon(pixmapShow);
    ui->pushButton_loadCircle->setToolTip("Show Circles");
    ui->pushButton_loadCircle->setToolTipDuration(5000);

    QIcon iconHide(":/res/whide.png");
    QPixmap pixmapHide = iconHide.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_unloadCircle->setIcon(pixmapHide);
    ui->pushButton_unloadCircle->setToolTip("Hide Circles");
    ui->pushButton_unloadCircle->setToolTipDuration(5000);

    QIcon iconSave(":/res/wsave.png");
    QPixmap pixmapSave = iconSave.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_saveCircle->setIcon(pixmapSave);
    ui->pushButton_saveCircle->setToolTip("Save Circles");
    ui->pushButton_saveCircle->setToolTipDuration(5000);

    QIcon iconRemove(":/res/wremove.png");
    QPixmap pixmapRemove = iconRemove.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_removeCircle->setIcon(pixmapRemove);
    ui->pushButton_removeCircle->setToolTip("Remove Circles");
    ui->pushButton_removeCircle->setToolTipDuration(5000);

    QIcon iconDelete(":/res/wdelete.png");
    QPixmap pixmapDelete = iconDelete.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_deleteCircle->setIcon(pixmapDelete);
    ui->pushButton_deleteCircle->setToolTip("Delete Circles");
    ui->pushButton_deleteCircle->setToolTipDuration(5000);
}


CircleMenu::~CircleMenu()
{
    delete ui;
}

QStringList CircleMenu::selectedRows(){ // Returns all selected rows
    QStringList selectedrows;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_circle->selectedItems();
    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_circle->item(row, 0);
        if(idItem)
        {
            QString id = idItem->text();
            selectedrows << id;
        }
    }
    selectedrows.removeDuplicates();
    ui->tableWidget_circle->clearSelection();
    return selectedrows;
}

void CircleMenu::on_pushButton_splitz_clicked()
{
    if(menuType == 0){
        ui->pushButton_splitz->setText("Create Circle");
        setWidgetState(1);
    }
    else if(menuType == 1){
        ui->pushButton_splitz->setText("View Circle");
        setWidgetState(0);
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }
}

void CircleMenu::setWidgetState(int type){
    menuType = type;
    ui->tableWidget_circle->clearContents();
    ui->tableWidget_circle->setRowCount(0);
    circleTableMap.clear();
    if(circleObject) {
        QMetaObject::invokeMethod(circleObject, "deleteAllCircle");
        //QMetaObject::invokeMethod(pointObject, "deLoadAllPoints");
    }
    if(type == 0){ // Create Points
        //Hide
        ui->pushButton_loadCircle->hide();
        ui->pushButton_unloadCircle->hide();
        ui->pushButton_deleteCircle->hide();
        ui->comboBox_loadOrder->hide();

        //show
        ui->pushButton_saveCircle->show();
        ui->pushButton_removeCircle->show();
        if(funcObject) {
            QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 4));
        }

    }
    else if(type == 1){ // Display Points
        loadCircleGisData();
        //Show
        ui->pushButton_loadCircle->show();
        ui->pushButton_unloadCircle->show();
        ui->pushButton_deleteCircle->show();
        ui->comboBox_loadOrder->show();

        //Hide
        ui->pushButton_saveCircle->hide();
        ui->pushButton_removeCircle->hide();
        if(funcObject) {
            QMetaObject::invokeMethod(funcObject, "stopDraw",Q_ARG(QVariant, 0));
        }
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }
}


void CircleMenu::updateCircleTable(QVariant CircleList,QVariant type){
    int typeOP = type.toInt();
    QMap<QString, QVariant> markerMap = CircleList.toMap();
    //qDebug() << "markerMap" << markerMap << markerMap.size();

    if(typeOP == 0){
        QList<QString> keys = markerMap.keys();
        if (!keys.isEmpty()) {
            QString lastKey = keys.last();
            QVariant circleVariant = markerMap.value(lastKey);
            QObject* circleObject = circleVariant.value<QObject*>();

            QGeoCoordinate center = circleObject->property("center").value<QGeoCoordinate>();
            double radius = circleObject->property("radius").toDouble();

            QString centerPoint = "Center:\n";
            centerPoint += "Latitude = " + QString::number(center.latitude()) + "\n";
            centerPoint += "Longitude = " + QString::number(center.longitude()) + "\n";
            //centerPoint += "Radius = " + QString::number(radius) + " meters\n";
            centerPoint += "Radius = " + QString::number(radius, 'f', 0) + " meters\n";
            circleTableMap[lastKey] =  QStringList()<<"Circle"<<centerPoint;
        }
        else{
            qDebug() << "The map is empty.";
        }
    }
    else if(typeOP == 1){
        foreach (const QString& circleId, circleTableMap.keys()) {
            if(markerMap.contains(circleId)){
                //Do Nothing
            }
            else{
                circleTableMap.remove(circleId);
            }
        }
    }
    else{
        qDebug()<<"Invalid Type of Operation";
        return;
    }

    ui->tableWidget_circle->clearContents();
    ui->tableWidget_circle->setRowCount(0);

    foreach (const QString& circleId, circleTableMap.keys())
    {
        QStringList values = circleTableMap[circleId];

        int row = ui->tableWidget_circle->rowCount();
        ui->tableWidget_circle->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(circleId);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_circle->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(values[0]);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_circle->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(values[1]);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_circle->setItem(row, 2, item3);
        ui->tableWidget_circle->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

void CircleMenu::on_pushButton_removeCircle_clicked()
{
    QStringList deleteCircles;
    QList<QTableWidgetItem*> selectedCircles = ui->tableWidget_circle->selectedItems();
    for(int i = 0; i < selectedCircles.count(); i++)
    {
        int row = selectedCircles.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_circle->item(row, 0);
        if(idItem)
        {
            QString id = idItem->text();
            deleteCircles << id;
        }
    }
    deleteCircles.removeDuplicates();
    qDebug()<<"deleteCircles"<<deleteCircles;

    if(circleObject) {
        QMetaObject::invokeMethod(circleObject, "deleteCircleList",Q_ARG(QVariant, deleteCircles));
    }
}

void CircleMenu::on_pushButton_saveCircle_clicked()
{
    QSqlQuery query;
    const QString circleInsertQuery = "INSERT INTO geocircle VALUES (:gCircleId , :gCircleName , ST_GeomFromText(:gcenter, 4326), :gradius);";
    const QString circleSelectQuery = "SELECT * FROM geocircle WHERE gcirclename = :gCircleName1;"; // Atention needed here
    //static QRegularExpression regex("Latitude = ([0-9.]+)\nLongitude = ([0-9.]+)\nRadius = ([0-9]+) meters");
    static QRegularExpression regex("Latitude = (-?[0-9.]+)\nLongitude = (-?[0-9.]+)\nRadius = ([0-9]+) meters");

    if(!circleTableMap.isEmpty()){

        if(!DatabaseManager::getInstance().isopen()){
            qCritical()<<query.lastError();
            return;
        }

        foreach (const QString& circleId, circleTableMap.keys())
        {
            QStringList values = circleTableMap[circleId];
            qDebug()<<"values"<<values[0]<<values[1];
            QRegularExpressionMatch match = regex.match(values[1]);
            if (match.hasMatch()) {
                double latitude = match.captured(1).toDouble();
                double longitude = match.captured(2).toDouble();
                int radius = match.captured(3).toInt();

                QString pointObj = QString("Point(%1 %2)").arg(latitude).arg(longitude);

                qDebug() << "Center: " << pointObj;
                qDebug() << "Radius: " << radius;

                query.prepare(circleSelectQuery);
                query.bindValue(":gCircleName1",values[0]);
                if(!query.exec()){
                    qCritical()<<query.lastError();
                }

                if(query.next()){
                    qCritical()<<"data exsists";
                    continue;
                }

                query.prepare(circleInsertQuery);
                query.bindValue(":gCircleId",circleId);
                query.bindValue(":gCircleName",values[0]);
                query.bindValue(":gcenter",pointObj);
                query.bindValue(":gradius",radius);

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

void CircleMenu::on_tableWidget_circle_cellDoubleClicked(int row, int column)
{
    QString originalValue = ui->tableWidget_circle->item(row, column)->text();
    ui->tableWidget_circle->editItem(ui->tableWidget_circle->item(row, column));

    cellChangeConnect = connect(ui->tableWidget_circle, &QTableWidget::cellChanged,
    this, [this, row, column, originalValue](int currentRow, int currentColumn) {
        if(menuType == 0){
            if (row == currentRow && column == currentColumn && ui->tableWidget_circle->item(row, column)->text() != originalValue) {
                QString id = ui->tableWidget_circle->item(row,0)->text();
                QString newName = ui->tableWidget_circle->item(row,1)->text();
                QStringList& values = circleTableMap[id];
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
            if (row == currentRow && column == currentColumn && ui->tableWidget_circle->item(row, column)->text() != originalValue) {
                if(ui->tableWidget_circle->rowCount()>1){
                    QString id = ui->tableWidget_circle->item(row,0)->text();
                    QString newName = ui->tableWidget_circle->item(row,1)->text();
                    updateCircleGisData(id,newName);
                }
            }
            allDisconnects();
        }
        ui->tableWidget_circle->clearSelection();
    });
}

void CircleMenu::allDisconnects(){
    disconnect(cellChangeConnect);
}

// View Database Circles =========================================================================================================

void CircleMenu::updateCircleGisData(QString id,QString newName)
{
    QSqlQuery query;
    const QString circleUpdateQuery = "UPDATE geocircle SET gcirclename = :gnewName WHERE gcircleid = :gupdatecircle;";
    if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
        qCritical()<<query.lastError();
        return;
    }

    query.prepare(circleUpdateQuery);
    query.bindValue(":gupdatecircle",id);
    query.bindValue(":gnewName",newName);

    if (!query.exec()) {
        qCritical() << query.lastError();
    } else {
        int rowsAffected = query.numRowsAffected();
        if (rowsAffected > 0) {
            qDebug()<<"Success Row updated";
            loadCircleGisData();
        } else {
            qDebug()<<"Failed to update row";
        }
    }
}

void CircleMenu::loadCircleGisData()
{
    ui->tableWidget_circle->clearContents();
    ui->tableWidget_circle->setRowCount(0);
    circleTableMap.clear();

    QSqlQuery query;
    const QString polygonSelectQuery = "SELECT gcircleid,gcirclename,ST_AsText(gcenter),gradius from geocircle;";
    //static QRegularExpression regex("POINT\\(([^ ]+) ([^ ]+)\\)");
    static QRegularExpression regex("POINT\\((-?\\d+\\.\\d+) (-?\\d+\\.\\d+)\\)");

    if (!DatabaseManager::getInstance().isopen()) {
        qCritical() << query.lastError();
        return;
    }

    if (!query.exec(polygonSelectQuery)) {
        qCritical() << query.lastError();
        return;
    }
    while (query.next()){
        qint64 gcircleid = query.value(0).toLongLong();
        QString gcirclename = query.value(1).toString();
        QString gcenter = query.value(2).toString();
        QString gradius = query.value(3).toString();
        qDebug()<<"gcircleid"<<gcircleid<<"gcirclename"<<gcirclename<<"gcenter"<<gcenter<<"gradius"<<gradius;
        QRegularExpressionMatch match = regex.match(gcenter);
        if(match.hasMatch()){
            QString latitude = match.captured(1);
            QString longitude = match.captured(2);
            QString centerPoint = "Center:\n";
            centerPoint += "Latitude = " + latitude + "\n";
            centerPoint += "Longitude = " + longitude + "\n";
            centerPoint += "Radius = " + gradius + " meters\n";

            int row = ui->tableWidget_circle->rowCount();
            ui->tableWidget_circle->insertRow(row);

            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(gcircleid));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_circle->setItem(row, 0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem(gcirclename);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_circle->setItem(row, 1, item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(centerPoint);

            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_circle->setItem(row, 2, item3);
            ui->tableWidget_circle->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
    }
}

void CircleMenu::loadCircleTable(QVariant loadList)
{
    ui->tableWidget_circle->clearContents();
    ui->tableWidget_circle->setRowCount(0);
    circleTableMap.clear();

    QMap<QString, QVariant> markerMap = loadList.toMap();
    qDebug()<<"markerMap"<<markerMap.size();
    QList<QString> keys = markerMap.keys();

    QSqlQuery query;
    const QString circleSelectQuery = "SELECT gcircleid,gcirclename,ST_AsText(gcenter),gradius FROM geocircle WHERE gcircleid=:gCircleId;";
    //static QRegularExpression regex("POINT\\(([^ ]+) ([^ ]+)\\)");
    static QRegularExpression regex("POINT\\((-?\\d+\\.\\d+) (-?\\d+\\.\\d+)\\)");

    if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
        qCritical()<<query.lastError();
        return;
    }

    foreach (const QString &key, keys) {
        qDebug()<<"Keys"<<key;
        query.prepare(circleSelectQuery);
        query.bindValue(":gCircleId",key);
        if (!query.exec()) {
            qCritical() << query.lastError();
            continue;
        }

        if (!query.next()) {
            qWarning() << "No results found for key" << key;
            continue;
        }

        qint64 gcircleid = query.value(0).toLongLong();
        QString gcirclename = query.value(1).toString();
        QString gcenter = query.value(2).toString();
        QString gradius = query.value(3).toString();

        qDebug()<<"gcircleid"<<gcircleid<<"gcirclename"<<gcirclename<<"gcenter"<<gcenter<<"gradius"<<gradius;

        QRegularExpressionMatch match = regex.match(gcenter);
        if(match.hasMatch()){
            QString latitude = match.captured(1);
            QString longitude = match.captured(2);
            QString centerPoint = "Center:\n";
            centerPoint += "Latitude = " + latitude + "\n";
            centerPoint += "Longitude = " + longitude + "\n";
            centerPoint += "Radius = " + gradius + " meters\n";

            int row = ui->tableWidget_circle->rowCount();
            ui->tableWidget_circle->insertRow(row);

            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(gcircleid));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_circle->setItem(row, 0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem(gcirclename);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_circle->setItem(row, 1, item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(centerPoint);

            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_circle->setItem(row, 2, item3);
            ui->tableWidget_circle->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
    }
}

void CircleMenu::on_pushButton_deleteCircle_clicked()
{
    QStringList deleteCircles;
    deleteCircles = selectedRows();
    if(!deleteCircles.isEmpty())
    {
        QSqlQuery query;
        const QString pointDeleteQuery = "DELETE FROM geocircle WHERE gcircleid = :deletepointid;";
        bool deletionSuccessful = true;
        if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
            qCritical()<<query.lastError();
            return;
        }
        for(int i=0; i<deleteCircles.length(); i++){
            query.prepare(pointDeleteQuery);
            query.bindValue(":deletepointid",deleteCircles[i]);

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
        if(deletionSuccessful){
            loadCircleGisData();
            if(circleObject) {
                QMetaObject::invokeMethod(circleObject, "deLoadCircleList",Q_ARG(QVariant, deleteCircles));
                if(ui->comboBox_loadOrder->currentIndex() == 1){
                    QMetaObject::invokeMethod(circleObject, "sendLoadedCircles");
                }
            }
        }
    }
}

void CircleMenu::on_pushButton_loadCircle_clicked()
{
    QStringList loadCircles;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_circle->selectedItems();
    //static QRegularExpression regex("Latitude = ([0-9.]+)\nLongitude = ([0-9.]+)\nRadius = ([0-9]+) meters");
    static QRegularExpression regex("Latitude = (-?[0-9.]+)\nLongitude = (-?[0-9.]+)\nRadius = ([0-9]+) meters");

    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_circle->item(row, 0);
        QTableWidgetItem* coorItem = ui->tableWidget_circle->item(row,2);
        if(idItem && coorItem)
        {
            QString id = idItem->text();
            QString coord = coorItem->text();
            QRegularExpressionMatch match = regex.match(coord);
            if(match.hasMatch()) {
                QString latitude = match.captured(1);
                QString longitude = match.captured(2);
                QString radius = match.captured(3);
                QString circle = id+"|"+latitude+"|"+longitude+"|"+radius;
                loadCircles << circle;
            }
        }
    }
    loadCircles.removeDuplicates();
    qDebug()<<"loadPoints"<<loadCircles;

    if(circleObject) {
        QMetaObject::invokeMethod(circleObject, "loadCircleList",Q_ARG(QVariant, loadCircles));
    }
    ui->tableWidget_circle->clearSelection();
}

void CircleMenu::on_pushButton_unloadCircle_clicked()
{
    QStringList unloadCircle;
    unloadCircle = selectedRows();
    if(circleObject) {
        QMetaObject::invokeMethod(circleObject, "deLoadCircleList",Q_ARG(QVariant, unloadCircle));
        if(ui->comboBox_loadOrder->currentIndex() == 1){
            QMetaObject::invokeMethod(circleObject, "sendLoadedCircles");
        }
    }
}

void CircleMenu::on_comboBox_loadOrder_activated(int index)
{
    qDebug()<<"index"<<index;
    if(index == 0){
        loadCircleGisData();
    }
    else if(index == 1){
        qDebug()<<"loaded values";
        if(circleObject) {
            QMetaObject::invokeMethod(circleObject, "sendLoadedCircles");
        }
    }
    else{
        qDebug()<<"invalid index";
    }
}




