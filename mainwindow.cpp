#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemdialog.h"

#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupModel();
    ui->table->setModel(&m_model);
    connect(ui->actionAdd_Item, &QAction::triggered, this, &MainWindow::onAddItem);
    m_addItemDialog = new AddItemDialog(this);
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("");
    m_db.setDatabaseName("");
    m_db.setUserName("");
    m_db.setPassword("");
    bool ok = m_db.open();
    if(!ok)
    {
        ui->statusBar->showMessage(tr("Database not connected!"));
    }
    else
    {
        ui->statusBar->showMessage(tr("Database connected!"));
    }
    connect(ui->actionRefresh, &QAction::triggered, this, &MainWindow::onRefreshDB);
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
        insertQuery(id, firstName, lastName);
    }
}

void MainWindow::onRefreshDB()
{
    selectQuery();
}

void MainWindow::setupModel()
{
    m_model.clear();
    QStringList headerLabels;
    headerLabels << "First Name" << "Last Name" << "Id";
    m_model.setHorizontalHeaderLabels(headerLabels);
}

void MainWindow::insertQuery(const QString &id, const QString &firstName, const QString &lastName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Persons VALUES (:id, :firstName, :lastName)");
    query.bindValue(":id", id.toInt());
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    bool ok = query.exec();
    if(!ok)
    {
        QString errorString = query.lastError().databaseText();
        ui->statusBar->showMessage(tr("SQL Insert query failed - ") + errorString);
    }
    else
    {
        ui->statusBar->showMessage("SQL Insert query successful!");
    }
}

void MainWindow::selectQuery()
{
    QSqlQuery query("SELECT * FROM Persons");
    if(query.lastError().isValid())
    {
        QString errorString = query.lastError().databaseText();
        ui->statusBar->showMessage(tr("SQL Select query failed - ") + errorString);
        return;
    }
    else
    {
        ui->statusBar->showMessage("SQL Select query successful!");
        setupModel();
    }
    while(query.next())
    {
        QString id = QString("%1").arg(query.value(0).toInt());
        QString firstName = query.value(1).toString();
        QString lastName = query.value(2).toString();
        QList<QStandardItem*> row;
        row << new QStandardItem(firstName) << new QStandardItem(lastName) << new QStandardItem(id);
        m_model.appendRow(row);
    }
}
