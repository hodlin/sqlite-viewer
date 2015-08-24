#ifndef DELETETABLE_H
#define DELETETABLE_H

#include <QDialog>
#include <QDebug>
#include <QtSql>

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
