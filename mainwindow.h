#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}
class AddItemDialog;
class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onAddItem();
    void onRefreshDB();
    void onTableActionsTriggered(QAction *action);
    void onAddHours();

private:
    void setupModel();
    void insertQuery(const QString &id, const QString &firstName, const QString &lastName);
    void insertQuery(const QString &id, const QString &hours);
    void selectQuery();
    void readSettings(QString &hostName, QString &databaseName, QString &userName, QString &password);

private:
    Ui::MainWindow *ui;
    QActionGroup *m_tableActions;
    AddItemDialog *m_addItemDialog;
    QSqlTableModel *m_personsModel;
    QSqlRelationalTableModel *m_workingHoursModel;
    QSqlQueryModel *m_workingHoursJoinPersonsModel;
    QSqlDatabase m_db;

};

#endif // MAINWINDOW_H
