#ifndef EMPLOYEEDIALOG_H
#define EMPLOYEEDIALOG_H

#include <stdafx.h>
#include <fieldvariant.h>
#include <adialogbase.h>

class SQLiteReader;
class SQLiteWriter;

// Диалог, показывающий таблицу "Сотрудники"
class EmployeesDialog : public ADialogBase
{
    Q_OBJECT

public:
    explicit EmployeesDialog(QWidget *parent, SQLiteManager *mgr);
    virtual ~EmployeesDialog();

    // ADialogBase interface
private:
    QSqlRelationalTableModel *readData(SQLiteReader *reader) override;
    QList<FieldVariant> createEmptyRecord(SQLiteReader *reader) override;
    bool writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer) override;
};

#endif // EMPLOYEEDIALOG_H
