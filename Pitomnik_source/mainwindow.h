#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdafx.h>

class EmployeesDialog;
class PositionsDialog;
class ClientsDialog;
class OrdersDialog;
class AnimalsDialog;
class SQLiteManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    SQLiteManager *mSqliteManager;
    EmployeesDialog *mEmployeesDlg;
    PositionsDialog* mPositionsDlg;
    ClientsDialog *mClientsDlg;
    AnimalsDialog *mAnimalsDlg;
    OrdersDialog *mOrdersDlg;

    int showDoYouWantRecreateDbMessageBox();

};
#endif // MAINWINDOW_H
