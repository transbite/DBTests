#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}
class AddItemDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onAddItem();
    void onRefreshDB();

private:
    void setupModel();
    void insertQuery(const QString &id, const QString &firstName, const QString &lastName);
    void selectQuery();

private:
    Ui::MainWindow *ui;
    AddItemDialog *m_addItemDialog;
    QStandardItemModel m_model;
    QSqlDatabase m_db;

};

#endif // MAINWINDOW_H
