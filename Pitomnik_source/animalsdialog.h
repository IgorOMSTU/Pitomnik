#ifndef ANIMALSDIALOG_H
#define ANIMALSDIALOG_H

#include <stdafx.h>
#include <fieldvariant.h>
#include <adialogbase.h>

class SQLiteReader;
class SQLiteWriter;

class AnimalsDialog : public ADialogBase
{
    Q_OBJECT
private:

public:
    explicit AnimalsDialog(QWidget *parent, SQLiteManager *mgr);
    virtual ~AnimalsDialog();

    // ADialogBase interface
private:
    QSqlRelationalTableModel *readData(SQLiteReader *reader) override;
    QList<FieldVariant> createEmptyRecord(SQLiteReader *reader) override;
    bool writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer) override;
};

#endif // ANIMALSDIALOG_H
