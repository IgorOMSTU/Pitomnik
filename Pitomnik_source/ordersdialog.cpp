#include "ordersdialog.h"

#include <fieldvariant.h>
#include <sqlitereader.h>
#include <sqlitewriter.h>

OrdersDialog::OrdersDialog(QWidget *parent, SQLiteManager *mgr)
    : ADialogBase(parent, mgr)
{
    setWindowTitle("Список заказов");
    setMinimumSize(450, 300);
}

OrdersDialog::~OrdersDialog()
{
}

QSqlRelationalTableModel *OrdersDialog::readData(SQLiteReader *reader)
{
    return reader->readOrders();
}

QList<FieldVariant> OrdersDialog::createEmptyRecord(SQLiteReader *reader)
{
    return reader->createEmptyOrders();
}

bool OrdersDialog::writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer)
{
    return writer->writeOrder(fieldsVariant);
}
