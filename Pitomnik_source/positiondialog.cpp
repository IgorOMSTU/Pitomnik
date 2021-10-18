#include "positiondialog.h"

#include <fieldvariant.h>
#include <sqlitereader.h>
#include <sqlitewriter.h>

PositionsDialog::PositionsDialog(QWidget *parent, SQLiteManager *mgr)
    : ADialogBase(parent, mgr)
{
    setWindowTitle("Список должностей");
}

PositionsDialog::~PositionsDialog()
{ 
}

QSqlRelationalTableModel *PositionsDialog::readData(SQLiteReader *reader)
{
    return reader->readPositions();
}

QList<FieldVariant> PositionsDialog::createEmptyRecord(SQLiteReader *reader)
{
    return reader->createEmptyPosition();
}

bool PositionsDialog::writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer)
{
    return writer->writePosition(fieldsVariant);
}
