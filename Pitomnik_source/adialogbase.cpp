#include "adialogbase.h"

#include <fieldvariant.h>
#include <sqlitemanager.h>
#include <sqlitereader.h>
#include <sqlitewriter.h>

ADialogBase::ADialogBase(QWidget *parent, SQLiteManager *mgr)
    : QDialog(parent),
      mSqliteManager(mgr),
      mAddNewRecordDialog(nullptr),
      mModel(nullptr)
{
    mTableView = new QTableView(this);
    mTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    mTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    mTableView->setAlternatingRowColors(true);
    QPushButton *addRecordButton = new QPushButton(this);
    addRecordButton->setText("Добавить");
    QPushButton *deleteRecordButton = new QPushButton(this);
    deleteRecordButton->setText("Удалить");

    QVBoxLayout *_layout = new QVBoxLayout(this);
    _layout->addWidget(mTableView);
    _layout->addWidget(addRecordButton);
    _layout->addWidget(deleteRecordButton);
    setLayout(_layout);

    connect(addRecordButton, SIGNAL(clicked()), this, SLOT(addRecordSlot()));
    connect(deleteRecordButton, SIGNAL(clicked()), this, SLOT(deleteRecordSlot()));
}

ADialogBase::~ADialogBase()
{
    layout()->removeWidget(mTableView);
    delete mTableView;
    if (mModel != nullptr) {
        delete mModel;
        mModel = nullptr;
    }
    if (mAddNewRecordDialog != nullptr) {
        delete mAddNewRecordDialog;
        mAddNewRecordDialog = nullptr;
    }
}

void ADialogBase::showModal()
{
    populateTable();
    setModal(true);
    show();
    mTableView->setFocus();
}

void ADialogBase::populateTable()
{
    auto reader = mSqliteManager->getSqliteReader();
    mModel = readData(reader); // запрашиваем у класса наследника модель QSqlRelationalTableModel

    // получим от класса наследника имена столбцов на русском языке
    QList<FieldVariant> fieldVariants = createEmptyRecord(reader);
    for (int i = 0; i < fieldVariants.size(); i++) {
        mModel->setHeaderData(i, Qt::Horizontal, fieldVariants[i].getColumnName());
    }

    // Привязываем визуальную таблицу к модели QSqlRelationalTableModel,
    // теперь визуальная таблица будет отображать данные из этой модели.
    // Сама модель QSqlRelationalTableModel привязана к таблице БД и получает
    // данные непосредственно из нее.

    mTableView->setModel(mModel);
    mTableView->setItemDelegate(new QSqlRelationalDelegate(mTableView));
    mTableView->selectRow(0);
}

void ADialogBase::addRecordSlot()
{
    if (mAddNewRecordDialog != nullptr) {
        delete mAddNewRecordDialog;
        mAddNewRecordDialog = nullptr;
    }

    // Пользователь нажал кнопку "Добавить" новую запись в таблицу.
    // Значит теперь нужно запросить у класса наследника набор полей для добавления
    // и показать AddNewRecordDialog диалог, который отвечает за добавление новой записи.

    auto reader = mSqliteManager->getSqliteReader();
    QList<FieldVariant> fieldVariants = createEmptyRecord(reader);
    mAddNewRecordDialog = new AddNewRecordDialog(this, fieldVariants);
    mAddNewRecordDialog->showDialog(this);
}

void ADialogBase::deleteRecordSlot()
{
    // Пользователь нажал кнопку "Удалить" запись из таблицы.
    // Значит теперь нужно получить номер строки из визуальной таблицы и удалить
    // эту строку из модели QSqlRelationalTableModel. Удаление записи из таблилцы
    // БД произойдет автоматически, т.к. модель связана с таблицей в БД

    QModelIndex index = mTableView->currentIndex();

    int answer = showDoYouWantRemoveRecordbMessageBox();
    if (answer == QMessageBox::Ok) {
        mTableView->model()->removeRow(index.row());
        populateTable();
    } else {
        mTableView->setFocus();
    }
}

void ADialogBase::complete(AddNewRecordDialog *addNewRecordDialog)
{
    bool result = false;
    auto writer = mSqliteManager->getSqliteWriter();
    if (addNewRecordDialog->isUserChoseCreate())
    {
        auto fv = addNewRecordDialog->fieldsVariant();
        result = writeRecord(fv, writer);

        if(!result)
            ADialogBase::showMessageBox(this, "Ошибка при добавлении записи", QMessageBox::Critical);
        else
            populateTable();
    }
}

void ADialogBase::showMessageBox(QWidget *parent, QString msg, QMessageBox::Icon icon)
{
    QMessageBox mbox(parent);
    mbox.setText(msg);
    mbox.setIcon(icon);
    mbox.exec();
}

int ADialogBase::showDoYouWantRemoveRecordbMessageBox()
{
    QMessageBox questionBbox(this);
    questionBbox.setText("Вы действительно хотите удалить запись?");
    questionBbox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    questionBbox.setDefaultButton(QMessageBox::No);
    questionBbox.setIcon(QMessageBox::Question);
    return questionBbox.exec();
}
