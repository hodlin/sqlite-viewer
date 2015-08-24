#include "deletetable.h"
#include "ui_deletetable.h"

deleteTable::deleteTable(QWidget *parent, QSqlQuery * qry, QString tableName) :
    QDialog(parent),
    ui(new Ui::deleteTable)
{
    ui->setupUi(this);
    query = qry;
    tblNm = tableName;
}

deleteTable::~deleteTable()
{
    delete ui;
}

void deleteTable::on_buttonBox_accepted()
{
    if(!query->exec("DROP TABLE "+tblNm))
        qDebug() << "Deleting table error!" << query->lastError().text();
    emit done();
}
