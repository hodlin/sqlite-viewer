#include "createtable.h"
#include "ui_createtable.h"


CreateTable::CreateTable(QWidget *parent, QSqlQuery * qry) :
    QDialog(parent),
    ui(new Ui::CreateTable)
{
    ui->setupUi(this);
    query = qry;
    ui->tableName->setPlaceholderText("enter new table's' name..");
    ui->columns->setPlaceholderText("\"Specify column_name column_type pairs separated by ',' \"\n"
                                 "ex.:\n"
                                 "column1_name column1_type,\n"
                                 "column2_name column2_type,\n"
                                 "...");
}

CreateTable::~CreateTable()
{
    delete ui;
}

void CreateTable::on_buttonBox_accepted()
{
    /**
     * Creating table proccessing
     *
     * Reads value from text edits for
     * tableName and columns configuration
     * and executes 'CREATE TABLE..' statement
     * at the and emits done() signal
     *
     * @return void
     */
    QString tableName;
    QString tableParams;
    tableName = ui->tableName->text();
    tableParams = ui->columns->toPlainText();

    if(!tableName.isEmpty() && !tableParams.isEmpty())
    {
        if(!query->exec("CREATE TABLE IF NOT EXISTS "+tableName+" ("+tableParams+")"))
        qDebug() << "Somthing wrong!" << query->lastError().text();

        //qDebug() << "CREATE TABLE IF NOT EXISTS "+tableName+" ("+tableParams+")";
    }
    emit done();
}

void CreateTable::on_buttonBox_rejected()
{

}
