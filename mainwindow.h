#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

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

private:
    void setupModel();

private:
    Ui::MainWindow *ui;
    AddItemDialog *m_addItemDialog;
    QStandardItemModel m_model;
};

#endif // MAINWINDOW_H
