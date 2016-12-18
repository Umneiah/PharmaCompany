#include "employee.h"
#include "ui_employee.h"

employee::employee(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::employee)
{
    ui->setupUi(this);
    insert = 0;
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
    insert = 0;
    ui->SSN->setEnabled(false);
    ui->Address->setEnabled(1);
    ui->Name->setEnabled(1);
    ui->PhoneNum->setEnabled(1);
    ui->Salary->setEnabled(1);
    ui->DepartNum->setEnabled(1);
    ui->comboBox->setEnabled(1);
}

void employee::on_UpdateRB_clicked()
{
    //ui->SSN->show();
    ui->SSN->setEnabled(true);
    ui->Address->setEnabled(1);
    ui->Name->setEnabled(1);
    ui->PhoneNum->setEnabled(1);
    ui->Salary->setEnabled(1);
    ui->DepartNum->setEnabled(1);
    ui->comboBox->setEnabled(1);
    insert = 1;
}

void employee::on_Perform_clicked()
{
    QString add = ui->Address->toPlainText();
    QString name = ui->Name->toPlainText();
    QString pho = ui->PhoneNum->toPlainText();
    QString salary = ui->Salary->toPlainText();
    QString DepNum = ui->DepartNum->currentText();
    QString type = ui->comboBox->currentText();
    if(insert == 0)
    {
        QString qur = "INSERT INTO Employee(Address,Name,Phone,Salary,Job_Type,Dep_number) VALUES('"+add+"','"+name+"','"+pho+"','"+salary+"','"+type+"','"+DepNum+"')";
        l->exec(qur);
    }
    else if(insert == 1)
    {

    }
    else if(insert == 2)
    {

    }
}

void employee::on_DeleteRB_clicked()
{
    insert = 2;
    ui->Address->setEnabled(0);
    ui->Name->setEnabled(0);
    ui->PhoneNum->setEnabled(0);
    ui->Salary->setEnabled(0);
    ui->DepartNum->setEnabled(0);
    ui->comboBox->setEnabled(0);


}
