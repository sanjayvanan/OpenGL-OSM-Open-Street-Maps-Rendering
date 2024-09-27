#include "databasemenu.h"
#include "ui_databasemenu.h"

DatabaseMenu::DatabaseMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DatabaseMenu)
{
    ui->setupUi(this);
}

DatabaseMenu::~DatabaseMenu()
{
    delete ui;
}
