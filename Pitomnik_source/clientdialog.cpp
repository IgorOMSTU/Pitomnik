#include "clientdialog.h"

#include <fieldvariant.h>
#include <sqlitereader.h>
#include <sqlitewriter.h>

ClientsDialog::ClientsDialog(QWidget *parent, SQLiteManager *mgr)
    : ADialogBase(parent, mgr)
{
    setWindowTitle("Список клиентов");
    setMinimumSize(700, 300);
}

ClientsDialog::~ClientsDialog()
{
}

QSqlRelationalTableModel *ClientsDialog::readData(SQLiteReader *reader)
{
    return reader->readClients();
}

QList<FieldVariant> ClientsDialog::createEmptyRecord(SQLiteReader *reader)
{
    return reader->createEmptyClients();
}

bool ClientsDialog::writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer)
{
    return writer->writeClient(fieldsVariant);
}
