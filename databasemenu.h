#ifndef DATABASEMENU_H
#define DATABASEMENU_H

#include <QWidget>

namespace Ui {
class DatabaseMenu;
}

class DatabaseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseMenu(QWidget *parent = nullptr);
    ~DatabaseMenu();

private:
    Ui::DatabaseMenu *ui;
};

#endif // DATABASEMENU_H
