#include "product.h"
#include "ui_product.h"

product::product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product)
{
    ui->setupUi(this);
}

product::~product()
{
    delete ui;
}
