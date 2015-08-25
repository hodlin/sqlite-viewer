#ifndef DELETETABLE_H
#define DELETETABLE_H

#include <QDialog>
#include <QDebug>
#include <QtSql>

/**
 * deleteTable class
 *
 * Implement deleteTable confirmation
 * dialog and executes 'DROP TABLE..' statement
 *
 * @parent     QWidget*    Establishing parent to this class, default is '0'
 * @query      QSqlQuery*  Query object to execute 'DROP TABLE..' statement, default in new query
 * @tableName  QString     Name of a table to delete in current database
 */

namespace Ui {
class deleteTable;
}

class deleteTable : public QDialog
{
    Q_OBJECT

public:
    explicit deleteTable(QWidget *parent = 0, QSqlQuery * qry = new QSqlQuery, QString tableName = "");
    ~deleteTable();
signals:
    void done();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::deleteTable *ui;
    QSqlQuery * query;
    QString tblNm;
};

#endif // DELETETABLE_H
