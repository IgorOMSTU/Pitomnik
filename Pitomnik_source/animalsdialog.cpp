#include "animalsdialog.h"

#include <fieldvariant.h>
#include <sqlitereader.h>
#include <sqlitewriter.h>

AnimalsDialog::AnimalsDialog(QWidget *parent, SQLiteManager *mgr)
    : ADialogBase(parent, mgr)
{
    setWindowTitle("Список животных");
    setMinimumSize(700, 300);
}

AnimalsDialog::~AnimalsDialog()
{
}

QSqlRelationalTableModel *AnimalsDialog::readData(SQLiteReader *reader)
{
    return reader->readAnimals();
}

QList<FieldVariant> AnimalsDialog::createEmptyRecord(SQLiteReader *reader)
{
    return reader->createEmptyEnimals();
}

bool AnimalsDialog::writeRecord(QList<FieldVariant> &fieldsVariant, SQLiteWriter *writer)
{
    return writer->writeAnimal(fieldsVariant);
}
