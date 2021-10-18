#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sqlitemanager.h>
#include <settingsrepository.h>
#include <employeedialog.h>
#include <positiondialog.h>
#include <clientdialog.h>
#include <ordersdialog.h>
#include <animalsdialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSqliteManager = new SQLiteManager(SettingsRepository::dbName);
    mSqliteManager->connect();

    mPositionsDlg = new PositionsDialog(this, mSqliteManager);
    mEmployeesDlg = new EmployeesDialog(this, mSqliteManager);
    mClientsDlg = new ClientsDialog(this, mSqliteManager);
    mOrdersDlg = new OrdersDialog(this, mSqliteManager);
    mAnimalsDlg = new AnimalsDialog(this, mSqliteManager);
}

MainWindow::~MainWindow()
{
    delete ui;

    mSqliteManager->close();
    delete mSqliteManager;
    mSqliteManager = nullptr;
}

// Функция удаляет файл базы данных и создает его заново.
// Затем БД заполняется данными (SQL код берется из файла с путем в SettingsRepository::dbName)
void MainWindow::on_action_triggered()
{
    int answer = showDoYouWantRecreateDbMessageBox();

    if (answer == QMessageBox::Ok) {
        bool isOK = mSqliteManager->resetDb();
        QString msg = isOK ? "База данных была успешно сброшена к исходному состоянию" : mSqliteManager->getLastError();
        ADialogBase::showMessageBox(this, msg, isOK ? QMessageBox::Information : QMessageBox::Critical);
    }
}

// Показать окно с содержимым БД "Сотрудники"
void MainWindow::on_pushButton_clicked()
{
    mEmployeesDlg->showModal();
}

// Показать окно с содержимым БД "Должности"
void MainWindow::on_pushButton_5_clicked()
{
    mPositionsDlg->showModal();
}

// Показать окно с содержимым БД "Клиенты"
void MainWindow::on_pushButton_2_clicked()
{
    mClientsDlg->showModal();
}

// Показать окно с содержимым БД "Животные"
void MainWindow::on_pushButton_3_clicked()
{
    mAnimalsDlg->showModal();
}

// Показать окно с содержимым БД "Заказы"
void MainWindow::on_pushButton_6_clicked()
{
    mOrdersDlg->showModal();
}

int MainWindow::showDoYouWantRecreateDbMessageBox()
{
    QMessageBox questionBbox(this);
    questionBbox.setText("Вы действительно хотите сбросить базу данных к исходному состоянию?");
    questionBbox.setInformativeText("Все сделанные вами изменения будут удалены.");
    questionBbox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    questionBbox.setDefaultButton(QMessageBox::No);
    questionBbox.setIcon(QMessageBox::Question);
    return questionBbox.exec();
}
