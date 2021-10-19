#ifndef ORDERSDIALOG_H
#define ORDERSDIALOG_H

#include <stdafx.h>
#include <fieldvariant.h>
#include <adialogbase.h>

class SQLiteReader;
class SQLiteWriter;

// Диалог, показывающий таблицу "Заказы"
class OrdersDialog : public ADialogBase
{
    Q_OBJECT
private:

public:
    explicit OrdersDialog(QWidget *parent, SQLiteManager *mgr);
    virtual ~OrdersDialog();

    // ADialogBase interface
private:
    QSqlRelationalTableModel *readData(SQLiteReader *reader) override;
    QList<FieldVariant> createEmptyRecord(SQLiteReader *reader) override;
    bool writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer) override;
};

#endif // ORDERSDIALOG_H
