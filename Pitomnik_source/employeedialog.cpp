#include "employeedialog.h"

#include <fieldvariant.h>
#include <sqlitereader.h>
#include <sqlitewriter.h>

EmployeesDialog::EmployeesDialog(QWidget *parent, SQLiteManager *mgr)
    : ADialogBase(parent, mgr)
{
    setWindowTitle("Список сотрудников");
    setMinimumSize(790, 300);
}

EmployeesDialog::~EmployeesDialog()
{
}

QSqlRelationalTableModel *EmployeesDialog::readData(SQLiteReader *reader)
{
    return reader->readEmployees();
}

QList<FieldVariant> EmployeesDialog::createEmptyRecord(SQLiteReader *reader)
{
    return reader->createEmptyEmployee();
}

bool EmployeesDialog::writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer)
{
    return writer->writeEmployee(fieldsVariant);
}
