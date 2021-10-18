#ifndef PositionDialog_H
#define PositionDialog_H

#include <stdafx.h>
#include <fieldvariant.h>
#include <adialogbase.h>

class SQLiteReader;
class SQLiteWriter;

class PositionsDialog : public ADialogBase
{
    Q_OBJECT
private:

public:
    explicit PositionsDialog(QWidget *parent, SQLiteManager *mgr);
    virtual ~PositionsDialog();

    // ADialogBase interface
private:
    QSqlRelationalTableModel *readData(SQLiteReader *reader) override;
    QList<FieldVariant> createEmptyRecord(SQLiteReader *reader) override;
    bool writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer) override;
};

#endif // PositionDialog_H
