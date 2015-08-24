#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <QDialog>
#include <QDebug>
#include <QtSql>


namespace Ui {
class CreateTable;
}

class CreateTable : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTable(QWidget *parent = 0, QSqlQuery * qry = new QSqlQuery);
    ~CreateTable();
signals:
    void done();
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    QSqlQuery * query;
    Ui::CreateTable *ui;
};

#endif // CREATETABLE_H
