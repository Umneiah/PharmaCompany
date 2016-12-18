#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setEnabled(0);
    mydatabase = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    mydatabase->setHostName("localhost");
    mydatabase->setDatabaseName("PharmaCompany");
    ui->pushButton->setEnabled(0);
    l = new QSqlQuery();
    choice = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_employeeRB_clicked()
{
    choice = 0;
}

void MainWindow::on_DepartmentRB_clicked()
{
    choice = 1;
}

void MainWindow::on_ClientsRB_clicked()
{
    choice = 2;
}

void MainWindow::on_ProductsRB_clicked()
{
    choice = 3;
}

void MainWindow::on_pushButton_clicked()
{
    if(choice == 0)
    {
        employee *e = new employee();
        e->mydatabase = this->mydatabase;
        e->l = this->l;
        e->show();
    }
    else if(choice == 1)
    {
        department *d = new department();
        d->mydatabase = this->mydatabase;
        d->l = this->l;
        d->show();
    }
    else if(choice == 2)
    {
        client *c = new client();
        c->mydatabase = this->mydatabase;
        c->l = this->l;
        c->show();
    }
    else if(choice == 3)
    {
        product *p = new product();
        p->mydatabase = this->mydatabase;
        p->l = this->l;
        p->show();
    }
    this->close();
}

void MainWindow::on_connect_clicked()
{
    QString use = ui->username->toPlainText();
    QString pass = ui->Password->toPlainText();
    mydatabase->setUserName(use);
    mydatabase->setPassword(pass);
    if(mydatabase->open())
    {
        ui->groupBox_2->setTitle("Connected to database");
        ui->groupBox->setEnabled(1);
        ui->groupBox_2->setEnabled(0);
        ui->pushButton->setEnabled(1);
    }
    else
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","couldn't connect to database");
        messageBox.setFixedSize(0,0);
    }
}
