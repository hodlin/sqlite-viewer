#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <QDialog>
#include <QDebug>
#include <QtSql>

/**
 *  CreateTable class
 *
 * CreateTable class processes creating new table
 * procedure in currently opened database
 *
 * @parent QWidget*    Establishing parent to this class, default is '0'
 * @query  QSqlQuery*  Query object to execute 'CREATE TABLE..' statement, default in new query
 *
 */

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
