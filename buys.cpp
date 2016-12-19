#include "buys.h"
#include "ui_buys.h"

Buys::Buys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Buys)
{
    ui->setupUi(this);
    ui->BuysGB->setEnabled(1);
}

Buys::~Buys()
{
    delete ui;
}


void Buys::on_Return_clicked()
{
    MainWindow *m = new MainWindow();
    m->show();
    this->close();
}
