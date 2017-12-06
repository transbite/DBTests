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
    enum class AddType
    {
        ADD_PERSON,
        ADD_HOURS
    };

public:
    explicit AddItemDialog(QWidget *parent = 0);
    ~AddItemDialog();

    void setData(const QString &firstName, const QString &lastName, const QString &id);
    void data(QString &firstName, QString &lastName, QString &id);
    void setType(AddType type);
    void setHours(const QString &hours);
    void hours(QString &hours);

protected:
    void accept() override;
    void showEvent(QShowEvent *);

private:
    Ui::AddItemDialog *ui;
    AddType m_type;
};

#endif // ADDITEMDIALOG_H
