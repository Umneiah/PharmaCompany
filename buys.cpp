#include "buys.h"
#include "ui_buys.h"

Buys::Buys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Buys)
{
    ui->setupUi(this);
    ui->BuysGB->setEnabled(1);
    choice = 0;
    l = new QSqlQuery();
    mydatabase = new QSqlDatabase();
    UpdateComboBoxes();
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

void Buys::UpdateComboBoxes()
{
    ui->ClientIDCB->clear();
    ui->ProductIDCB->clear();
    QString query1 = "select ID from Product;";
    l->exec(query1);
    while(l->next())
    {
        int item = l->value(0).toInt();
        ui->ProductIDCB->addItem(QString::number(item));
    }
    QString query = "select ID from Client;";
    l->exec(query);
    while(l->next())
    {
        QString item = l->value(0).toString();
        ui->ClientIDCB->addItem(item);
    }
}

void Buys::on_insert_clicked()
{
    QString PID = ui->ProductIDCB->currentText();
    QString CID = ui->ClientIDCB->currentText();
    QString qur = "INSERT INTO Buys(Product_ID,Client_ID,Contract_Date) VALUES('"+PID+"','"+CID+"',CURRENT_TIMESTAMP)";
    l->exec(qur);
}

void Buys::on_BuysSearch_textChanged()
{
    QString sea = ui->BuysSearch->toPlainText();
    QString qur;
    if(choice == 0)
    {
        qur = "SELECT * FROM Buys WHERE Bill_Number='"+sea+"'";
    }
    else if(choice == 1)
    {
        qur = "SELECT * FROM Buys WHERE Product_ID='"+sea+"'";
    }
    else if(choice == 2)
    {
        qur = "SELECT * FROM Buys WHERE Client_ID='"+sea+"'";
    }
    l->exec(qur);
    QStandardItemModel *model = new QStandardItemModel(l->size(),4,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Bill Number")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Product ID")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Client ID")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Contract Date")));
    int index = 0;
    while(l->next())
    {
        QStandardItem *BiNum = new QStandardItem(QString(l->value("Bill_Number").toString()));
        QSqlQuery *l1 = new QSqlQuery();
        l1->exec("SELECT Name FROM Product WHERE ID='"+l->value("Product_ID").toString()+"'");
        l1->next();
        QStandardItem *PID = new QStandardItem(QString(l1->value("Name").toString()));
        l1->exec("SELECT Name FROM Client WHERE ID='"+l->value("Client_ID").toString()+"'");
        l1->next();
        QStandardItem *CID = new QStandardItem(QString(l1->value("Name").toString()));
        QStandardItem *CoDate = new QStandardItem(QString(l->value("Contract_Date").toString()));
        model->setItem(index,0,BiNum);
        model->setItem(index,1,PID);
        model->setItem(index,2,CID);
        model->setItem(index,3,CoDate);
        index++;
    }
    ui->tableView->setModel(model);
}

void Buys::on_radioButton_clicked()
{
    choice = 0;
}

void Buys::on_radioButton_2_clicked()
{
    choice = 1;
}

void Buys::on_radioButton_3_clicked()
{
    choice = 2;
}
