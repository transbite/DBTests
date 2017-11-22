#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemdialog.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlField>
#include <QSqlRecord>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionAdd_Item, &QAction::triggered, this, &MainWindow::onAddItem);
    m_addItemDialog = new AddItemDialog(this);
    QString hostName;
    QString databaseName;
    QString userName;
    QString password;
    readSettings(hostName, databaseName, userName, password);
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(hostName);
    m_db.setDatabaseName(databaseName);
    m_db.setUserName(userName);
    m_db.setPassword(password);
    bool ok = m_db.open();
    if(!ok)
    {
        ui->statusBar->showMessage(tr("Database not connected!"));
    }
    else
    {
        ui->statusBar->showMessage(tr("Database connected!"));
    }
    setupModel();
    ui->table->setModel(m_model);
    connect(ui->actionRefresh, &QAction::triggered, this, &MainWindow::onRefreshDB);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSettings(QString &hostName, QString &databaseName, QString &userName, QString &password)
{
    qDebug() << "App dir path " << qApp->applicationDirPath();
    QSettings s(qApp->applicationDirPath() + "/DBTests.conf", QSettings::IniFormat);
    hostName = s.value("HOSTNAME").toString();
    databaseName = s.value("DATABASENAME").toString();
    userName = s.value("USERNAME").toString();
    password = s.value("PASSWORD").toString();
    qDebug() << "Settings file name " << s.fileName();
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
    m_model = new QSqlTableModel(this, m_db);
    m_model->setTable("Persons");
//    m_model->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    m_model->setHeaderData(0, Qt::Horizontal, tr("Id"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("First Name"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
    m_model->select();
}

void MainWindow::insertQuery(const QString &id, const QString &firstName, const QString &lastName)
{
    QSqlField idField("id", QVariant::Int);
    QSqlField firstNameField("firstname", QVariant::String);
    QSqlField lastNameField("lastname", QVariant::String);
    idField.setValue(id);
    firstNameField.setValue(firstName);
    lastNameField.setValue(lastName);
    QSqlRecord record;
    record.append(idField);
    record.append(firstNameField);
    record.append(lastNameField);
    m_model->insertRecord(-1, record);
    if(!m_model->submitAll())
    {
        ui->statusBar->showMessage(tr("Values not submitted to remote database!"));
    }
    else
    {
        ui->statusBar->showMessage(tr("Values submitted to remote database."));
    }
}

void MainWindow::selectQuery()
{
    m_model->select();
}
