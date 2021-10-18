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

class ADialogBase : public QDialog, ICompletionHandler
{
    Q_OBJECT

    QTableView *mTableView;
    SQLiteManager *mSqliteManager;
    QSqlRelationalTableModel *mModel;
    AddNewRecordDialog *mAddNewRecordDialog;

public:
    explicit ADialogBase(QWidget *parent, SQLiteManager *mgr);
    virtual ~ADialogBase();

    void showModal();
    int showDoYouWantRemoveRecordbMessageBox();
    static void showMessageBox(QWidget *parent, QString msg, QMessageBox::Icon icon);

public slots:
     void addRecordSlot();
     void deleteRecordSlot();
     void complete(AddNewRecordDialog *addNewRecordDialog) override;

private:
     void populateTable();
     void showWriteError();

     virtual QSqlRelationalTableModel *readData(SQLiteReader *reader) = 0;
     virtual QList<FieldVariant> createEmptyRecord(SQLiteReader *reader) = 0;
     virtual bool writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer) = 0;
};

#endif // ADIALOGBASE_H
