#include "shapefileselectiondialog.h"
#include <QDir>
#include <QFileInfo>

ShapefileSelectionDialog::ShapefileSelectionDialog(const QString &rootPath, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Select Shapefiles");
    setMinimumSize(400, 300);

    treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderLabels(QStringList() << "File/Folder" << "Type");
    treeWidget->setSelectionMode(QAbstractItemView::NoSelection);

    selectAllCheckBox = new QCheckBox("Select All", this);
    selectButton = new QPushButton("Select", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(selectAllCheckBox);
    layout->addWidget(treeWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(selectButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(selectAllCheckBox, &QCheckBox::stateChanged, this, &ShapefileSelectionDialog::selectAllClicked);
    connect(treeWidget, &QTreeWidget::itemChanged, this, &ShapefileSelectionDialog::updateSelectedFiles);
    connect(selectButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    populateTree(rootPath, nullptr);
}

void ShapefileSelectionDialog::populateTree(const QString &path, QTreeWidgetItem *parent)
{
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);

    for (const QFileInfo &fileInfo : list) {
        QTreeWidgetItem *item;
        if (parent)
            item = new QTreeWidgetItem(parent);
        else
            item = new QTreeWidgetItem(treeWidget);

        item->setText(0, fileInfo.fileName());
        item->setData(0, Qt::UserRole, fileInfo.filePath());

        if (fileInfo.isDir()) {
            item->setText(1, "Folder");
            populateTree(fileInfo.filePath(), item);
        } else if (fileInfo.suffix().toLower() == "shp") {
            item->setText(1, "Shapefile");
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(0, Qt::Unchecked);
        }
    }
}

void ShapefileSelectionDialog::selectAllClicked(int state)
{
    Qt::CheckState checkState = static_cast<Qt::CheckState>(state);
    setAllCheckState(treeWidget->invisibleRootItem(), checkState);
}

void ShapefileSelectionDialog::setAllCheckState(QTreeWidgetItem *item, Qt::CheckState state)
{
    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *child = item->child(i);
        if (child->text(1) == "Shapefile") {
            child->setCheckState(0, state);
        } else if (child->text(1) == "Folder") {
            setAllCheckState(child, state);
        }
    }
}

void ShapefileSelectionDialog::updateSelectedFiles(QTreeWidgetItem *item, int column)
{
    if (column == 0 && item->text(1) == "Shapefile") {
        QString filePath = item->data(0, Qt::UserRole).toString();
        if (item->checkState(0) == Qt::Checked) {
            if (!selectedFiles.contains(filePath))
                selectedFiles.append(filePath);
        } else {
            selectedFiles.removeAll(filePath);
        }
    }
}

QStringList ShapefileSelectionDialog::getSelectedFiles() const
{
    return selectedFiles;
}
