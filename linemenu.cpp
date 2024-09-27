#include "linemenu.h"
#include "ui_linemenu.h"
#include "databasemanager.h"

LineMenu::LineMenu(QQuickWidget *quickWidget,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LineMenu),
    m_quickWidget(quickWidget)
{
    ui->setupUi(this);

    ui->tableWidget_line->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_line->setColumnHidden(0,true);

    qmlObject = m_quickWidget->rootObject();
    if (!qmlObject) {
        qDebug() << "QML object is null.";
        return;
    }

    lineObject = qmlObject->findChild<QObject*>("linespace");
    if (!lineObject) {
        qDebug() << "pointspace object is null.";
        return;
    }

    funcObject = qmlObject->findChild<QObject*>("functionspace");
    if (!funcObject) {
        qDebug() << "functionspace object is null.";
        return;
    }

    QObject::connect(qmlObject, SIGNAL(sendLineList(QVariant,QVariant)),this, SLOT(updateLineTable(QVariant,QVariant)));
    QObject::connect(qmlObject, SIGNAL(sendLineLoadList(QVariant)),this, SLOT(loadlineTable(QVariant)));

    //Setting Icons and ToolTips
    ui->pushButton_splitz->setText("Create Lines");

    QIcon iconShow(":/res/wshow.png");
    QPixmap pixmapShow = iconShow.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_loadLines->setIcon(pixmapShow);
    ui->pushButton_loadLines->setToolTip("Show Lines");
    ui->pushButton_loadLines->setToolTipDuration(5000);

    QIcon iconHide(":/res/whide.png");
    QPixmap pixmapHide = iconHide.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_unloadLines->setIcon(pixmapHide);
    ui->pushButton_unloadLines->setToolTip("Hide Lines");
    ui->pushButton_unloadLines->setToolTipDuration(5000);

    QIcon iconSave(":/res/wsave.png");
    QPixmap pixmapSave = iconSave.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_saveLines->setIcon(pixmapSave);
    ui->pushButton_saveLines->setToolTip("Save Lines");
    ui->pushButton_saveLines->setToolTipDuration(5000);

    QIcon iconRemove(":/res/wremove.png");
    QPixmap pixmapRemove = iconRemove.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_removeLines->setIcon(pixmapRemove);
    ui->pushButton_removeLines->setToolTip("Remove Lines");
    ui->pushButton_removeLines->setToolTipDuration(5000);

    QIcon iconDelete(":/res/wdelete.png");
    QPixmap pixmapDelete = iconDelete.pixmap(QSize(96, 96), Qt::SmoothTransformation);
    ui->pushButton_deleteLines->setIcon(pixmapDelete);
    ui->pushButton_deleteLines->setToolTip("Delete Lines");
    ui->pushButton_deleteLines->setToolTipDuration(5000);
}

LineMenu::~LineMenu()
{
    delete ui;
}

QStringList LineMenu::selectedRows(){ // Returns all selected rows
    QStringList selectedrows;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_line->selectedItems();
    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_line->item(row, 0);
        if(idItem)
        {
            QString id = idItem->text();
            selectedrows << id;
        }
    }
    selectedrows.removeDuplicates();
    ui->tableWidget_line->clearSelection();
    return selectedrows;
}


void LineMenu::on_pushButton_splitz_clicked()
{
    if(menuType == 0){
        ui->pushButton_splitz->setText("Create Lines");
        setWidgetState(1);
    }
    else if(menuType == 1){
        ui->pushButton_splitz->setText("View Lines");
        setWidgetState(0);
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }
}

// Set Widget mode(Create/view) ==============================================================================================

void LineMenu::setWidgetState(int type)
{
    menuType = type;
    ui->tableWidget_line->clearContents();
    ui->tableWidget_line->setRowCount(0);
    lineTableMap.clear();
    if(lineObject) {
        QMetaObject::invokeMethod(lineObject, "deleteAllLines");
        //QMetaObject::invokeMethod(pointObject, "deLoadAllPoints");
    }
    if(type == 0){ // Create Lines
        //Hide
        ui->pushButton_loadLines->hide();
        ui->pushButton_unloadLines->hide();
        ui->pushButton_deleteLines->hide();
        ui->comboBox_loadOrder->hide();

        //show
        ui->pushButton_saveLines->show();
        ui->pushButton_removeLines->show();
        if(funcObject) {
            QMetaObject::invokeMethod(funcObject, "chooseDraw",Q_ARG(QVariant, 2));
        }

    }
    else if(type == 1){ // Display Lines
        loadLineGisData();
        //Show
        ui->pushButton_loadLines->show();
        ui->pushButton_unloadLines->show();
        ui->pushButton_deleteLines->show();
        ui->comboBox_loadOrder->show();

        //Hide
        ui->pushButton_saveLines->hide();
        ui->pushButton_removeLines->hide();
        if(funcObject) {
            QMetaObject::invokeMethod(funcObject, "stopDraw",Q_ARG(QVariant, 0));
        }
    }
    else{
        qDebug()<<"Invalid Menu Type";
    }

}

//Create Line Maker =========================================================================================================

void LineMenu::updateLineTable(QVariant lineList,QVariant type)
{
    QMap<QString, QVariant> markerMap = lineList.toMap();
    int typeOP = type.toInt();
    //qDebug() << "markerMap" << markerMap << markerMap.size() <<typeOP ;

    if(typeOP == 0){
        QList<QString> keys = markerMap.keys();
        if (!keys.isEmpty()) {
            QString lastKey = keys.last();
            QVariant polylineVariant = markerMap.value(lastKey);
            QObject* polylineObject = polylineVariant.value<QObject*>();

            QVariantList path = polylineObject->property("path").toList();

            QString allPoints;

            int PointIndex = 1;
            for (const QVariant& coordinateVariant : path) {
                QGeoCoordinate coordinate = coordinateVariant.value<QGeoCoordinate>();
                QString onePoint = "Point " + QString::number(PointIndex) + "\n";
                onePoint += "Latitude = " + QString::number(coordinate.latitude()) + "\n";
                onePoint += "Longitude = " + QString::number(coordinate.longitude()) + "\n\n";
                PointIndex ++;
                allPoints+=onePoint;
            }
            //qDebug()<<"allPoints"<<allPoints;
            lineTableMap[lastKey] = QStringList()<<"Line"<<allPoints;
        }
        else{
            qDebug() << "The map is empty.";
        }
    }
    else if(typeOP == 1){
        foreach (const QString& lineId, lineTableMap.keys()) {
            if(markerMap.contains(lineId)){
                //Do Nothing
            }
            else{
                lineTableMap.remove(lineId);
            }
        }
    }
    else{
        qDebug()<<"Invalid Type of Operation";
        return;
    }


    ui->tableWidget_line->clearContents();
    ui->tableWidget_line->setRowCount(0);

    foreach (const QString& polylineId, lineTableMap.keys())
    {
        QStringList values = lineTableMap[polylineId];

        int row = ui->tableWidget_line->rowCount();
        ui->tableWidget_line->insertRow(row);
        QTableWidgetItem *item1 = new QTableWidgetItem(polylineId);
        item1->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_line->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem(values[0]);
        item2->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_line->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem(values[1]);
        item3->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_line->setItem(row, 2, item3);
        ui->tableWidget_line->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    //qDebug()<<"****LINE MAP****"<<lineTableMap;
}

void LineMenu::on_pushButton_removeLines_clicked()
{
    QStringList removeLines;
    removeLines = selectedRows();
    qDebug()<<"removeLines"<<removeLines;

    if(lineObject) {
        QMetaObject::invokeMethod(lineObject, "deleteLineList",Q_ARG(QVariant, removeLines));
    }
}

void LineMenu::on_pushButton_saveLines_clicked()
{
    QSqlQuery query;
    const QString lineInsertQuery = "INSERT INTO geoline VALUES(:geolineid,:geolinename,ST_GeomFromText(:gline,4326));";
    const QString lineSelectQuery = "SELECT * FROM geoline WHERE glinename = :glinename1 OR gline = ST_GeomFromText(:gline1);";
    //static QRegularExpression regexLinestring(R"(\bLatitude\s*=\s*([\d\.]+)\s*Longitude\s*=\s*([\d\.]+)\b)");
    static QRegularExpression regexLinestring(R"(\bLatitude\s*=\s*(-?[\d\.]+)\s*Longitude\s*=\s*(-?[\d\.]+)\b)");
    if(!lineTableMap.isEmpty())
    {
        if(!DatabaseManager::getInstance().isopen()){
            qCritical()<<query.lastError();
            return;
        }
        foreach (const QString& lineId, lineTableMap.keys())
        {
            QStringList values = lineTableMap[lineId];
            //qDebug()<<"values"<<values[0]<<values[1];
            QRegularExpressionMatchIterator matchIterator = regexLinestring.globalMatch(values[1]);
            QString linestring;
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                if (match.hasMatch()) {
                    QString latitude = match.captured(1);
                    QString longitude = match.captured(2);
                    if (!linestring.isEmpty()) {
                        linestring += ",";
                    }
                    linestring += latitude + " " + longitude;
                }
            }
            if (!linestring.isEmpty()) {
                linestring = "LINESTRING(" + linestring + ")";
                qDebug()<< linestring.toStdString();
            }

            query.prepare(lineSelectQuery);
            query.bindValue(":glinename1",values[0]);
            query.bindValue(":gline1",linestring);
            if(!query.exec()){
                qCritical()<<query.lastError();
            }

            if(query.next()){
                qCritical()<<"data exsists";
                continue;
            }

            query.prepare(lineInsertQuery);
            query.bindValue(":geolineid",lineId);
            query.bindValue(":geolinename",values[0]);
            query.bindValue(":gline",linestring);

            if(!query.exec()){
                qCritical()<<query.lastError();
            }
        }
    }
}

void LineMenu::on_tableWidget_line_cellDoubleClicked(int row, int column)
{
    QString originalValue = ui->tableWidget_line->item(row, column)->text();
    ui->tableWidget_line->editItem(ui->tableWidget_line->item(row, column));

    cellChangeConnect = connect(ui->tableWidget_line, &QTableWidget::cellChanged,
    this, [this, row, column, originalValue](int currentRow, int currentColumn) {
        if(menuType == 0){
            if (row == currentRow && column == currentColumn && ui->tableWidget_line->item(row, column)->text() != originalValue) {
                QString id = ui->tableWidget_line->item(row,0)->text();
                QString newName = ui->tableWidget_line->item(row,1)->text();
                QStringList& values = lineTableMap[id];
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
            if (row == currentRow && column == currentColumn && ui->tableWidget_line->item(row, column)->text() != originalValue) {
                if(ui->tableWidget_line->rowCount()>1){
                    QString id = ui->tableWidget_line->item(row,0)->text();
                    QString newName = ui->tableWidget_line->item(row,1)->text();
                    updateLineGisData(id,newName);
                }
            }
            allDisconnects();
        }
        ui->tableWidget_line->clearSelection();
    });

}

void LineMenu::allDisconnects(){
    disconnect(cellChangeConnect);
}

// View Database Lines =========================================================================================================

void LineMenu::updateLineGisData(QString id, QString newName){
    QSqlQuery query;
    const QString pointUpdateQuery = "UPDATE geoline SET glinename = :gnewName WHERE glineid = :gupdatePoint;";
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
            loadLineGisData();
        } else {
            qDebug()<<"Failed to update row";
        }
    }
}

void LineMenu::loadLineGisData(){
    ui->tableWidget_line->clearContents();
    ui->tableWidget_line->setRowCount(0);
    lineTableMap.clear();

    QSqlQuery query;
    const QString lineSelectQuery = "SELECT glineid,glinename,ST_AsText(gline) FROM geoline;";
    // static QRegularExpression regex("LINESTRING\\(((?:\\d+(?:\\.\\d+)? \\d+(?:\\.\\d+)?,?)+)"); // this one is to see if LineString is there
    // static QRegularExpression regexLine("(\\d+(?:\\.\\d+)?) (\\d+(?:\\.\\d+)?)"); // this one to seperate the different points it runs in iterator
    static QRegularExpression regex("LINESTRING\\(([-]?\\d+(?:\\.\\d+)? [-]?\\d+(?:\\.\\d+)?(?:,[-]?\\d+(?:\\.\\d+)? [-]?\\d+(?:\\.\\d+)?)*)\\)");
    static QRegularExpression regexLine("([-]?\\d+(?:\\.\\d+)?) ([-]?\\d+(?:\\.\\d+)?)");


    if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
        qCritical()<<query.lastError();
        return;
    }
    if(!query.exec(lineSelectQuery)){
        qCritical()<<query.lastError();
        return;
    }
    while(query.next()){
        qint64 glineid = query.value(0).toLongLong();
        QString glinename = query.value(1).toString();
        QString glinetext = query.value(2).toString();
        QRegularExpressionMatchIterator it = regex.globalMatch(glinetext);
        qDebug()<<"glinename"<<glinename<<"glinetext"<<glinetext;
        QString allPoints;
        int pointCount = 1;

        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString coordinatesString = match.captured(1);
            QRegularExpressionMatchIterator pointIt = regexLine.globalMatch(coordinatesString);
            while (pointIt.hasNext()) {
                QRegularExpressionMatch pointMatch = pointIt.next();
                QString latitude = pointMatch.captured(1);
                QString longitude = pointMatch.captured(2);
                QString onePoint = "Point " + QString::number(pointCount) + "\n";
                onePoint += "Latitude = " + latitude + "\n";
                onePoint += "Longitude = " + longitude + "\n\n";
                allPoints+=onePoint;
                pointCount++;
            }
            //qDebug()<<"allPoints"<<glinename<<allPoints;

            int row = ui->tableWidget_line->rowCount();
            ui->tableWidget_line->insertRow(row);
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(glineid));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_line->setItem(row, 0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem(glinename);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_line->setItem(row, 1, item2);

            QTableWidgetItem *item3 = new QTableWidgetItem(allPoints);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_line->setItem(row, 2, item3);
            ui->tableWidget_line->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
    }
}


void LineMenu::loadlineTable(QVariant loadList){
    ui->tableWidget_line->clearContents();
    ui->tableWidget_line->setRowCount(0);
    lineTableMap.clear();

    QMap<QString, QVariant> markerMap = loadList.toMap();
    qDebug()<<"markerMap"<<markerMap.size();
    QList<QString> keys = markerMap.keys();

    QSqlQuery query;
    const QString lineSelectQuery = "SELECT glineid,glinename,ST_AsText(gline) FROM geoline WHERE glineid = :glinekey;";
    // static QRegularExpression regex("LINESTRING\\(((?:\\d+(?:\\.\\d+)? \\d+(?:\\.\\d+)?,?)+)"); // this one is to see if LineString is there
    // static QRegularExpression regexLine("(\\d+(?:\\.\\d+)?) (\\d+(?:\\.\\d+)?)"); // this one to seperate the different points it runs in iterator
    static QRegularExpression regex("LINESTRING\\(([-]?\\d+(?:\\.\\d+)? [-]?\\d+(?:\\.\\d+)?(?:,[-]?\\d+(?:\\.\\d+)? [-]?\\d+(?:\\.\\d+)?)*)\\)");
    static QRegularExpression regexLine("([-]?\\d+(?:\\.\\d+)?) ([-]?\\d+(?:\\.\\d+)?)");

    if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
        qCritical()<<query.lastError();
        return;
    }

    foreach (const QString &key, keys) {
        qDebug()<<"Keys"<<key;
        query.prepare(lineSelectQuery);
        query.bindValue(":glinekey",key);
        if (!query.exec()) {
            qCritical() << query.lastError();
            continue;
        }
        if (!query.next()) {
            qWarning() << "No results found for key" << key;
            continue;
        }
        qint64 glineid = query.value(0).toLongLong();
        QString glinename = query.value(1).toString();
        QString glinetext = query.value(2).toString();
        QRegularExpressionMatchIterator it = regex.globalMatch(glinetext);

        QString allPoints;
        int pointCount = 1;

        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString coordinatesString = match.captured(1);
            QRegularExpressionMatchIterator pointIt = regexLine.globalMatch(coordinatesString);
            while (pointIt.hasNext()) {
                QRegularExpressionMatch pointMatch = pointIt.next();
                QString latitude = pointMatch.captured(1);
                QString longitude = pointMatch.captured(2);
                QString onePoint = "Point " + QString::number(pointCount) + "\n";
                onePoint += "Latitude = " + latitude + "\n";
                onePoint += "Longitude = " + longitude + "\n\n";
                allPoints+=onePoint;
                pointCount++;
            }

            int row = ui->tableWidget_line->rowCount();
            ui->tableWidget_line->insertRow(row);
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(glineid));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_line->setItem(row, 0, item1);

            QTableWidgetItem *item2 = new QTableWidgetItem(glinename);
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_line->setItem(row, 1, item2);

            QTableWidgetItem *item3 = new QTableWidgetItem(allPoints);
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_line->setItem(row, 2, item3);
            ui->tableWidget_line->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
    }
}

void LineMenu::on_pushButton_deleteLines_clicked()
{
    QStringList deleteLines;
    deleteLines = selectedRows();
    if(!deleteLines.isEmpty())
    {
        QSqlQuery query;
        const QString lineDeleteQuery = "DELETE FROM geoline WHERE glineid = :deletelineid;";
        bool deletionSuccessful = true;
        if(!DatabaseManager::getInstance().isopen()){ // CHECKING IF DATABASE IS OPEN
            qCritical()<<query.lastError();
            return;
        }
        for(int i=0; i<deleteLines.length(); i++){
            query.prepare(lineDeleteQuery);
            query.bindValue(":deletelineid",deleteLines[i]);

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
            loadLineGisData();
            if(lineObject) {
                QMetaObject::invokeMethod(lineObject, "deLoadLineList",Q_ARG(QVariant, deleteLines));
                if(ui->comboBox_loadOrder->currentIndex() == 1){
                    QMetaObject::invokeMethod(lineObject, "sendLoadedLine");
                }
            }
        }
    }
    else{
        qDebug()<<"Nothing to Delete";
    }
}

void LineMenu::on_pushButton_loadLines_clicked()
{
    QStringList Loadlines;
    QMap<QString,QString> loadLines;
    QList<QTableWidgetItem*> selectedPoints = ui->tableWidget_line->selectedItems();
    //static QRegularExpression regexLinestring(R"(\bLatitude\s*=\s*([\d\.]+)\s*Longitude\s*=\s*([\d\.]+)\b)");
    static QRegularExpression regexLinestring(R"(\bLatitude\s*=\s*(-?[\d\.]+)\s*Longitude\s*=\s*(-?[\d\.]+)\b)");
    for(int i = 0; i < selectedPoints.count(); i++)
    {
        int row = selectedPoints.at(i)->row();
        QTableWidgetItem* idItem = ui->tableWidget_line->item(row, 0);
        QTableWidgetItem* coorItem = ui->tableWidget_line->item(row,2);
        if(idItem && coorItem)
        {
            QString id = idItem->text();
            QString coord = coorItem->text();
            QRegularExpressionMatchIterator matchIterator = regexLinestring.globalMatch(coord);
            QString linestring;
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                if (match.hasMatch()) {
                    QString latitude = match.captured(1);
                    QString longitude = match.captured(2);
                    if (!linestring.isEmpty()) {
                        linestring += "|";
                    }
                    linestring += latitude + "," + longitude;
                }
            }
            if (!linestring.isEmpty()) {
                linestring = linestring;
                Loadlines<<linestring;
                loadLines[id] = linestring;
            }
        }
    }
    Loadlines.removeDuplicates();
    qDebug()<<"Loadlines"<<Loadlines;
    if (lineObject) {
        QVariantMap loadLinesMap;
        for (auto it = loadLines.begin(); it != loadLines.end(); ++it) {
            loadLinesMap.insert(it.key(), it.value());
        }
        QVariant loadLinesVariant(loadLinesMap);
        QMetaObject::invokeMethod(lineObject, "loadLineList", Q_ARG(QVariant, loadLinesVariant));
    }
}

void LineMenu::on_pushButton_unloadLines_clicked()
{
    QStringList unloadLines;
    unloadLines = selectedRows();
    if(lineObject){
        QMetaObject::invokeMethod(lineObject, "deLoadLineList", Q_ARG(QVariant, unloadLines));
        if(ui->comboBox_loadOrder->currentIndex() == 1){
            QMetaObject::invokeMethod(lineObject, "sendLoadedLine");
        }
    }
}

void LineMenu::on_comboBox_loadOrder_activated(int index)
{
    qDebug()<<"index"<<index;
    if(index == 0){
        loadLineGisData();
    }
    else if(index == 1){
        qDebug()<<"loaded values";
        if(lineObject) {
            QMetaObject::invokeMethod(lineObject, "sendLoadedLine");
        }
    }
    else{
        qDebug()<<"invalid index";
    }
}

