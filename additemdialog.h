#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>

namespace Ui {
class AddItemDialog;
}

class AddItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemDialog(QWidget *parent = 0);
    ~AddItemDialog();

    void setData(const QString &firstName, const QString &lastName, const QString &id);
    void data(QString &firstName, QString &lastName, QString &id);

protected:
    void accept() override;
    void showEvent(QShowEvent *);

private:
    Ui::AddItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
