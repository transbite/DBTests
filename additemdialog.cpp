#include "additemdialog.h"
#include "ui_additemdialog.h"

#include <QMessageBox>

AddItemDialog::AddItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void AddItemDialog::setData(const QString &firstName, const QString &lastName, const QString &id)
{
    ui->firstName->setText(firstName);
    ui->lastName->setText(lastName);
    ui->id->setText(id);
}

void AddItemDialog::data(QString &firstName, QString &lastName, QString &id)
{
    firstName = ui->firstName->text();
    lastName = ui->lastName->text();
    id = ui->id->text();
}

void AddItemDialog::accept()
{
    bool ok = true;
    ui->id->text().toInt(&ok);
    if(!ok)
    {
        QMessageBox::warning(this, tr("Add Item Error"), tr("Id should be a number"));
    }
    else
    {
        QDialog::accept();
    }
}

void AddItemDialog::showEvent(QShowEvent *)
{
    setData("", "", "");
}
