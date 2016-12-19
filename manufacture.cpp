#include "manufacture.h"
#include "ui_manufacture.h"

Manufacture::Manufacture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manufacture)
{
    ui->setupUi(this);
    l = new QSqlQuery();
    mydatabase = new QSqlDatabase();
    ui->pID->setChecked(true);
    QString query1 = "select ID from Product";
    QString query2 = "select Department_number from Department";
    l->exec(query1);
    while(l->next())
    {
        ui->p_id->addItem(l->value(0).toString());
    }
    l->exec(query2);
    while(l->next())
    {
        ui->dep_num->addItem(l->value(0).toString());
    }

}

Manufacture::~Manufacture()
{
    delete ui;
}

void Manufacture::on_insert_clicked()
{
   QString pid = ui->p_id->currentText();
   QString depnum = ui->dep_num->currentText();
   QString query = "insert into Manufacture (Dep_number,Product_ID) values ('"+depnum+"','"+pid+"')";
   l->exec(query);
   ui->p_id->clear();
   ui->dep_num->clear();
   QString query1 = "select ID from Product";
   QString query2 = "select Department_number from Department";
   l->exec(query1);
   while(l->next())
   {
       ui->p_id->addItem(l->value(0).toString());
   }
   l->exec(query2);
   while(l->next())
   {
       ui->dep_num->addItem(l->value(0).toString());
   }
}

void Manufacture::on_Back_clicked()
{
    MainWindow *m = new MainWindow();
    m->show();
    this->close();
}


void Manufacture::on_search_textChanged()
{
    QString query ;
    QStandardItemModel *model = new QStandardItemModel(0,2,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("   Product Name    ")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("      Department Name       ")));
    if(ui->search->toPlainText() != "")
    {
        if(ui->pID->isChecked())
        {
            query += "select p.Name, d.Name from Manufacture as m ,Department as d, Product as p where m.Product_ID = "+ui->search->toPlainText();
            query += " AND p.ID =  m.Product_ID AND d.Department_number = m.Dep_number";
        }else if(ui->DN->isChecked())
        {
            query += "select p.Name, d.Name from Manufacture as m ,Department as d, Product as p where m.Dep_number = "+ui->search->toPlainText();
            query += " AND p.ID =  m.Product_ID AND d.Department_number = m.Dep_number";
        }
        l->exec(query);
        int index = 0;
        model->setRowCount(l->size());
        while (l->next()){
            QStandardItem *dn = new QStandardItem(QString(l->value(0).toString()));
            QStandardItem *pid = new QStandardItem(QString(l->value(1).toString()));
            model->setItem(index,0,dn);
            model->setItem(index,1,pid);
           index++;
        }
    }

    ui->tableView->setModel(model);
}
