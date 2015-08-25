#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <createtable.h>
#include <deletetable.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_OpenDatabase_clicked();

    void on_NewDatabase_clicked();

    void on_comboBox_activated(const QString &arg1);

    bool createConnection(QString databaseName);

    void closeConnection();

    void showTable(QString tableName);

    void on_pushButtonNewRecord_clicked();

    void on_pushButtonDeleteRecord_clicked();

    void on_CreateTable_clicked();

    void on_DeleteTable_clicked();

    void updateComboBox();

    void onTableCreate();

    void onTableDelete();

    void buttonEnable(bool flag);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    deleteTable * tableDel;
    CreateTable * tableCre;


};

#endif // MAINWINDOW_H
