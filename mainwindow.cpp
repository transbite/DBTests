#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupModel();
    connect(ui->actionAdd_Item, &QAction::triggered, this, &MainWindow::onAddItem);
    m_addItemDialog = new AddItemDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddItem()
{
    int r = m_addItemDialog->exec();
    if(r == QDialog::Accepted)
    {
        QString firstName;
        QString lastName;
        QString id;
        m_addItemDialog->data(firstName, lastName, id);
        QList<QStandardItem*> row;
        row << new QStandardItem(firstName) << new QStandardItem(lastName) << new QStandardItem(id);
        m_model.appendRow(row);
    }
}

void MainWindow::setupModel()
{
    QStringList headerLabels;
    headerLabels << "First Name" << "Last Name" << "Id";
    m_model.setHorizontalHeaderLabels(headerLabels);
    ui->table->setModel(&m_model);
}
