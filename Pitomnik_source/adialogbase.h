#ifndef ADIALOGBASE_H
#define ADIALOGBASE_H

#include <stdafx.h>
#include <addnewrecorddialog.h>
#include <fieldvariant.h>

class SQLiteManager;
class QSqlRelationalTableModel;
class AddNewRecordDialog;
class SQLiteReader;
class SQLiteWriter;

// базовый класс диалога для показа данных из БД в визуальной таблице;
// классы наследники сами выбирают, какую табицу БД отобразить путем загрузки
// нужных данных в QSqlRelationalTableModel
class ADialogBase : public QDialog, ICompletionHandler
{
    Q_OBJECT

    QTableView *mTableView;          // визуальная таблица
    SQLiteManager *mSqliteManager;
    // модель, с помощью которой осуществляется доступ к БД и вывод данных в визуальную таблицу
    QSqlRelationalTableModel *mModel;
    AddNewRecordDialog *mAddNewRecordDialog; // диалог добавления новой записи в таблицу БД

public:
    explicit ADialogBase(QWidget *parent, SQLiteManager *mgr);
    virtual ~ADialogBase();

    void showModal();
    int showDoYouWantRemoveRecordbMessageBox();
    static void showMessageBox(QWidget *parent, QString msg, QMessageBox::Icon icon);

public slots:
     void addRecordSlot();  // пользователь нажал кнопку "Добавить" новую запись в таблицу
     void deleteRecordSlot(); // пользователь нажал кнопку "Удалить" запись из таблицы

     // этот метод вызвается из AddNewRecordDialog, когда пользователь ввел все данные
     // для создания новой строки в таблилце БД и нажал кнопку "Создать"
     void complete(AddNewRecordDialog *addNewRecordDialog) override;

private:
     void populateTable();
     void showWriteError();

     // метод запрашивает данные для показа в таблице у класса наследника
     virtual QSqlRelationalTableModel *readData(SQLiteReader *reader) = 0;

     // метод запрашивает список FieldVariant у класса наследника, каждый из которых представляет
     // одно поле в создаваемой строке, т.к. мы получим новые данные от пользователя, то здесь
     // данные пустые (кроме внешних ключей и пола животного, т.к. они показываются в комбобоксах)
     virtual QList<FieldVariant> createEmptyRecord(SQLiteReader *reader) = 0;

     // метод говорит классу наследнику, что новые данные строки для записи в таблицу БД получены
     // от пользователя, можно их записать в нужную таблицу БД
     virtual bool writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer) = 0;
};

#endif // ADIALOGBASE_H
