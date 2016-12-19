#include "manufacture.h"
#include "ui_manufacture.h"

Manufacture::Manufacture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manufacture)
{
    ui->setupUi(this);
}

Manufacture::~Manufacture()
{
    delete ui;
}
