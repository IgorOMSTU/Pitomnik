#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <stdafx.h>
#include <fieldvariant.h>
#include <adialogbase.h>

class SQLiteReader;
class SQLiteWriter;

// Диалог, показывающий таблицу "Клиенты"
class ClientsDialog : public ADialogBase
{
    Q_OBJECT
private:

public:
    explicit ClientsDialog(QWidget *parent, SQLiteManager *mgr);
    virtual ~ClientsDialog();

    // ADialogBase interface
private:
    QSqlRelationalTableModel *readData(SQLiteReader *reader) override;
    QList<FieldVariant> createEmptyRecord(SQLiteReader *reader) override;
    bool writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer) override;
};

#endif // CLIENTDIALOG_H
