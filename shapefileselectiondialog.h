#ifndef SHAPEFILESELECTIONDIALOG_H
#define SHAPEFILESELECTIONDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>

class ShapefileSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShapefileSelectionDialog(const QString &rootPath, QWidget *parent = nullptr);
    QStringList getSelectedFiles() const;

private slots:
    void selectAllClicked(int state);
    void updateSelectedFiles(QTreeWidgetItem *item, int column);

private:
    QTreeWidget *treeWidget;
    QPushButton *selectButton;
    QPushButton *cancelButton;
    QCheckBox *selectAllCheckBox;
    QStringList selectedFiles;

    void populateTree(const QString &path, QTreeWidgetItem *parent);
    void setAllCheckState(QTreeWidgetItem *item, Qt::CheckState state);
};

#endif // SHAPEFILESELECTIONDIALOG_H
