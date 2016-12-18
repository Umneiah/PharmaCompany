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
}

void product::on_UpdateRB_clicked()
{
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
    }else if(dele){
         QString query = "delete from Product where ID = '"+ui->Ids->currentText()+"';";
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
        if(ui->Name->toPlainText()!="")
        {
            query += "Name = '"+ui->Name->toPlainText()+"'";
        }
        if(ui->Price->toPlainText() != "")
        {
            query += " ,Price = '"+ui->Price->toPlainText()+"'";
        }
        query += " where ID = "+ui->Ids->currentText();
        l->exec(query);
        if(ui->category->toPlainText() != "")
        {
            QString query = "update Equipment set Category = '"+ui->category->toPlainText()+"'";
            query += " where EID = "+ui->Ids->currentText();
            l->exec(query);
        }
    }
}



void product::on_radioButton_4_clicked()
{
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
    ui->out->clear();
    int c1=0,c2=0;
    QString output="ID \t Name \t Price \t Category \n";
    QString output1 = "ID \t Name \t Price \t Expiration_Date \n ";
    if(ui->name->isChecked())
    {
        QString query = "select ID,Name,Price,Category from product as p,Equipment as e where Name = '"+ui->textEdit->toPlainText();
        query += "' AND e.EID = p.ID;";
        l->exec(query);
        while(l->next())
        {
            output += l->value(0).toString()+" \t "+l->value(1).toString()+" \t "+l->value(2).toString();
            output += " \t "+l->value(3).toString()+"\n";
            c1 = 1;
        }
        QString query1 = "select ID,Name,Price,Expiration_Date from product as p, Medicine as e where Name = '"+ui->textEdit->toPlainText();
        query1 += "' AND e.EID = p.ID;";
        l->exec(query1);
        while(l->next())
        {
            output1 += l->value(0).toString()+" \t "+l->value(1).toString()+" \t "+l->value(2).toString();
            output1 += " \t "+l->value(3).toString()+"\n";
            c2 = 1;
        }

    }else if(ui->id->isChecked()){
        QString query = "select ID,Name,Price,Category from product as p,Equipment as e where ID ="+ui->textEdit->toPlainText();
        query += " AND e.EID = p.ID;";
        l->exec(query);
        while(l->next())
        {
            output += l->value(0).toString()+" \t "+l->value(1).toString()+" \t "+l->value(2).toString();
            output += " \t "+l->value(3).toString()+"\n";
            c1 = 1;
        }
        QString query1 = "select ID,Name,Price,Expiration_Date from product as p, Medicine as e where ID = '"+ui->textEdit->toPlainText();
        query1 += "' AND e.EID = p.ID;";
        l->exec(query1);
        while(l->next())
        {
            output1 += l->value(0).toString()+" \t "+l->value(1).toString()+" \t "+l->value(2).toString();
            output1 += " \t "+l->value(3).toString()+"\n";
            c2 = 1;
        }
    }else if(ui->pr->isChecked())
    {
        QString query = "select ID,Name,Price,Category from product as p,Equipment as e where Price ="+ui->textEdit->toPlainText();
        query += " AND e.EID = p.ID;";
        l->exec(query);
        while(l->next())
        {
            output += l->value(0).toString()+" \t "+l->value(1).toString()+" \t "+l->value(2).toString();
            output += " \t "+l->value(3).toString()+"\n";
            c1 = 1;
        }
        QString query1 = "select ID,Name,Price,Expiration_Date from product as p, Medicine as e where Price = '"+ui->textEdit->toPlainText();
        query1 += "' AND e.EID = p.ID;";
        l->exec(query1);
        while(l->next())
        {
            output1 += l->value(0).toString()+" \t "+l->value(1).toString()+" \t "+l->value(2).toString();
            output1 += " \t "+l->value(3).toString()+"\n";
            c2 = 1;
        }
    }
    QString o = "";
    if(c1)o += output;
    if(c2)o += output1;
    ui->out->setText(o);
}
