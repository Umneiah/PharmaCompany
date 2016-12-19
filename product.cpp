#include "product.h"
#include "ui_product.h"

product::product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product)
{
    ui->setupUi(this);
    ui->radioButton_2->setChecked(true);
    Equipment = true;
    insert = true;
    ui->name->setChecked(true);
    ui->Ids->setEnabled(0);
}

product::~product()
{
    delete ui;
}

void product::on_radioButton_2_clicked()
{
    Equipment = true;
    ui->category->setEnabled(true);
}

void product::on_radioButton_3_clicked()
{
    Equipment = false;
    ui->category->setEnabled(false);
}

void product::on_radioButton_clicked()
{
    ui->Name->setEnabled(true);
    ui->Price->setEnabled(true);
    if(Equipment)
    {
        ui->category->setEnabled(true);
        ui->category->setPlaceholderText("Category");
    }
    ui->Name->setPlaceholderText(" Name");
    ui->Price->setPlaceholderText(" Price");
    insert = true;
    dele = false;
    ui->Ids->clear();
    ui->Ids->setEnabled(0);
}

void product::on_UpdateRB_clicked()
{
    ui->Ids->setEnabled(1);
    ui->Ids->clear();
    insert = false;
    dele = false;
    ui->Name->setEnabled(true);
    ui->Price->setEnabled(true);
    if(Equipment)
    {
        ui->category->setEnabled(true);
    }
    ui->Name->setPlaceholderText("Updated Name");
    ui->Price->setPlaceholderText("Updated Price");
    ui->category->setPlaceholderText("Updated Category");
    QString query = "select ID from Product;";
    l->exec(query);
    while(l->next())
    {
        int item = l->value(0).toInt();
        ui->Ids->addItem(QString::number(item));
    }
}

void product::on_Perform_clicked()
{
    if(insert)
    {

        QString Name = ui->Name->toPlainText();
        QString Price =ui->Price->toPlainText();
        l->exec("insert into Product (Name,Price) values ('"+Name+"','"+Price+"');");
        l->exec("select count(*) from Product;");
        l->next();
        int count = l->value(0).toInt();
        if(Equipment)
        {
            QString category = ui->category->toPlainText();
            QString query = "insert into Equipment(EID,Category)values('"+QString::number(count)+"','"+category+"')";
            l->exec(query);
        }else{
           QString query = "INSERT INTO Medicine (`M_ID`, `Expiration_Date`) VALUES ('"+QString::number(count)+"', CURRENT_TIMESTAMP);";
           l->exec(query);
        }
        ui->Name->clear();
        ui->Price->clear();
        ui->category->clear();
    }else if(dele){
         QString query = "delete from Product where ID = "+ui->Ids->currentText();
         l->exec(query);
         ui->Ids->clear();
         QString query1 = "select ID from Product;";
         l->exec(query1);
         while(l->next())
         {
             int item = l->value(0).toInt();
             ui->Ids->addItem(QString::number(item));
         }
    }
    else{
        QString query="update Product set ";
        int y=0;
        if(ui->Name->toPlainText()!="")
        {
            query += "Name = '"+ui->Name->toPlainText()+"'";
            y = 1;
        }
        if(ui->Price->toPlainText() != "")
        {
            if(y)query += ", ";
            query += "Price = '"+ui->Price->toPlainText()+"'";
        }
        query += " where ID = "+ui->Ids->currentText();
        l->exec(query);
        if(ui->category->toPlainText() != "")
        {
            QString query = "update Equipment set Category = '"+ui->category->toPlainText()+"'";
            query += " where EID = "+ui->Ids->currentText();
            l->exec(query);
        }
        ui->Name->clear();
        ui->Price->clear();
        ui->category->clear();
    }
}



void product::on_radioButton_4_clicked()
{
    ui->Ids->setEnabled(1);
    ui->Ids->clear();
    ui->category->setEnabled(false);
    ui->Name->setEnabled(false);
    ui->Price->setEnabled(false);
    dele = true;
    insert = false;
    QString query = "select ID from Product;";
    l->exec(query);
    while(l->next())
    {
        int item = l->value(0).toInt();
        ui->Ids->addItem(QString::number(item));
    }
}

void product::on_textEdit_textChanged()
{
    //int c1=0,c2=0;
    QStringList output;
    QStringList output1 ;
    int size = 0;
    if(ui->name->isChecked())
    {
        QString query = "select ID,Name,Price,Category from product as p,Equipment as e ,Medicine as m where Name = '"+ui->textEdit->toPlainText();
        query += "' AND e.EID = p.ID;";
        l->exec(query);
        while(l->next())
        {
            output.append(l->value(0).toString());
            output.append(l->value(1).toString());
            output.append(l->value(2).toString());
            output.append(l->value(3).toString());
            size++;
        }
        QString query1 = "select ID,Name,Price,Expiration_Date from product as p, Medicine as e where Name = '"+ui->textEdit->toPlainText();
        query1 += "' AND e.M_ID = p.ID;";
        l->exec(query1);
        while(l->next())
        {
            output1.append(l->value(0).toString());
            output1.append(l->value(1).toString());
            output1.append(l->value(2).toString());
            output1.append(l->value(3).toString());
            size++;
        }

    }else if(ui->id->isChecked()){
        QString query = "select ID,Name,Price,Category from product as p,Equipment as e where ID ="+ui->textEdit->toPlainText();
        query += " AND e.EID = p.ID;";
        l->exec(query);
        while(l->next())
        {
            output.append(l->value(0).toString());
            output.append(l->value(1).toString());
            output.append(l->value(2).toString());
            output.append(l->value(3).toString());
            size++;
        }
        QString query1 = "select ID,Name,Price,Expiration_Date from product as p, Medicine as e where ID = '"+ui->textEdit->toPlainText();
        query1 += "' AND e.M_ID = p.ID;";
        l->exec(query1);
        while(l->next())
        {
            output1.append(l->value(0).toString());
            output1.append(l->value(1).toString());
            output1.append(l->value(2).toString());
            output1.append(l->value(3).toString());
            size++;
        }
    }else if(ui->pr->isChecked())
    {
        QString query = "select ID,Name,Price,Category from product as p,Equipment as e where Price ="+ui->textEdit->toPlainText();
        query += " AND e.EID = p.ID;";
        l->exec(query);
        while(l->next())
        {
            output.append(l->value(0).toString());
            output.append(l->value(1).toString());
            output.append(l->value(2).toString());
            output.append(l->value(3).toString());
            size++;
        }
        QString query1 = "select ID,Name,Price,Expiration_Date from product as p, Medicine as e where Price = '"+ui->textEdit->toPlainText();
        query1 += "' AND e.M_ID = p.ID;";
        l->exec(query1);
        while(l->next())
        {
            output1.append(l->value(0).toString());
            output1.append(l->value(1).toString());
            output1.append(l->value(2).toString());
            output1.append(l->value(3).toString());
            size++;
        }
    }
    QStandardItemModel *model = new QStandardItemModel(0,0,this);
    model->setColumnCount(4);
    model->setRowCount(size);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Price")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Category/Expiration_Date")));
    if(size)
    {

        for(int index = 0 ;index <output.size();index = index + 4)
        {
            QStandardItem *id= new QStandardItem(output[index]);
            QStandardItem *name = new QStandardItem(output[index+1]);
            QStandardItem *price = new QStandardItem(output[index+2]);
            QStandardItem *e = new QStandardItem(output[index+3]);
            model->setItem(index,0,id);
            model->setItem(index,1,name);
            model->setItem(index,2,price);
            model->setItem(index,3,e);
        }
        for(int index = 0 ;index <output1.size();index = index + 4)
        {
            QStandardItem *id= new QStandardItem(output1[index]);
            QStandardItem *name = new QStandardItem(output1[index+1]);
            QStandardItem *price = new QStandardItem(output1[index+2]);
            QStandardItem *e = new QStandardItem(output1[index+3]);
            model->setItem(index,0,id);
            model->setItem(index,1,name);
            model->setItem(index,2,price);
            model->setItem(index,3,e);
        }

    }
ui->tableView->setModel(model);
}

void product::on_pushButton_clicked()
{
    MainWindow * w = new MainWindow();
    w->show();
    this->close();
}
