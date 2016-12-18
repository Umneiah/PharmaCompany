#include "employee.h"
#include "ui_employee.h"

employee::employee(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employee)
{
    ui->setupUi(this);
    insert = true;
    fullT = true;
    ui->SSN->setEnabled(false);
    ui->comboBox->addItem("Full Time");
    ui->comboBox->addItem("Part Time");
}

employee::~employee()
{
    delete ui;
}

void employee::on_radioButton_clicked()
{
    insert = true;
    ui->SSN->setEnabled(false);
}

void employee::on_UpdateRB_clicked()
{
    //ui->SSN->show();
    ui->SSN->setEnabled(true);
    insert = false;
}

void employee::on_Perform_clicked()
{
    if(insert)
    {
        QString add = ui->Address->toPlainText();
        QString name = ui->Name->toPlainText();
        QString pho = ui->PhoneNum->toPlainText();
        QString salary = ui->Salary->toPlainText();
        QString DepNum = ui->DepartNum->toPlainText();
        QString type = ui->comboBox->currentText();
        QString qur = "INSERT INTO Employee(Address,Name,Phone,Salary,Job_Type,Dep_number) VALUES('"+add+"','"+name+"','"+pho+"','"+salary+"','"+type+"','"+DepNum+"');";

        l->exec(qur);
    }
    else
    {

    }
}
