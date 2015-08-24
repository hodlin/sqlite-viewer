#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QTableView>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    closeConnection();
}

void MainWindow::on_OpenDatabase_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"), QString(),
                                                    tr("All Files (*.*);;Database Files (*.sqlite *.sqlite3 *.db)"));

    qDebug() << fileName;
    if (!fileName.isEmpty()) {

        if (!createConnection(fileName))
            ui->status->setText("Impossible to open database");
        else
        {
        ui->status->setText("Database has been opened");
//        ui->comboBox->clear();

//        QStringList lst = db.tables();
//        foreach (QString str, lst)
//        {
//            ui->comboBox->addItem(str);
//        }
        updateComboBox();
        showTable(ui->comboBox->currentText());
        }
    }
}

void MainWindow::on_NewDatabase_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("New Database"), QString(),
                                                    tr("All Files (*.*);;Database Files (*.sqlite *.sqlite3 *.db)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "Imposible to create database!";
        } else {
            file.close();
        }
    }
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    qDebug() << arg1;

    showTable(arg1);
    ui->status->setText("Table '"+arg1+"' displayed");
}

bool MainWindow::createConnection(QString databaseName)
{
    if (db.isOpen())
    {
        db.close();
        //qDebug() << "+1";
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);


    if (!db.open())
    {
        qDebug() << "Can't open database: " << db.lastError().text();
        return false;
    }

    query = new QSqlQuery;
    QStringList lst = db.tables();

    foreach (QString str, lst)
    {
        qDebug() << "Table: " << str;
    }

    return true;
}

void MainWindow::closeConnection()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

void MainWindow::updateComboBox()
{
    ui->comboBox->clear();

    QStringList lst = db.tables();
    foreach (QString str, lst)
    {
        ui->comboBox->addItem(str);
    }
}

void MainWindow::showTable(QString tableName)
{
    QSqlTableModel * model = new QSqlTableModel();

    model->setTable(tableName);
    model->select();

    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_pushButtonNewRecord_clicked()
{
    if(db.isOpen())
    {
        if (!query->exec("INSERT INTO "+ui->comboBox->currentText()+" DEFAULT VALUES"))
        {
            qDebug() << "INSERT INTO "+ui->comboBox->currentText()+" DEFAULT VALUES";
            qDebug() << "Insertion error: " << query->lastError().text();
        }

        showTable(ui->comboBox->currentText());
        ui->status->setText("New record inserted");
    }
    else
        ui->status->setText("No database connection!");
}

void MainWindow::on_pushButtonDeleteRecord_clicked()
{
    if(db.isOpen())
    {
        QSqlTableModel * model = new QSqlTableModel();

        model->setTable(ui->comboBox->currentText());

        model->select();

        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();

        for (int i = 0; i < selected.size(); ++i)
            model->removeRows(selected.at(i).row(), 1);

        if(!model->submitAll())
        {
            qDebug() << "Insertion error!";
        }

        showTable(ui->comboBox->currentText());
        ui->status->setText("Record(s) deleted");
    }
    else
        ui->status->setText("No database connection!");

}

void MainWindow::on_CreateTable_clicked()
{
    if(db.isOpen())
    {
        qDebug() << "creating table..";
        tableCre = new CreateTable(0, query);
        connect(tableCre, SIGNAL(done()), this, SLOT(onTableCreate()));
        tableCre->show();
    }
    else
        ui->status->setText("No database connection!");
}

void MainWindow::on_DeleteTable_clicked()
{
    if (db.isOpen())
    {
        qDebug() << "deleting table..";
        tableDel = new deleteTable(0, query, ui->comboBox->currentText());
        connect(tableDel, SIGNAL(done()), this, SLOT(onTableDelete()));
        tableDel->show();
    }
    else
        ui->status->setText("No database connection!");
}

void MainWindow::onTableCreate()
{
    updateComboBox();
    showTable(ui->comboBox->currentText());
    ui->status->setText("Table created");
}

void MainWindow::onTableDelete()
{
    updateComboBox();
    showTable(ui->comboBox->currentText());
    ui->status->setText("Table deleted");
}
