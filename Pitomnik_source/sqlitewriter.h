#ifndef SQLITEWRITER_H
#define SQLITEWRITER_H

#include <stdafx.h>
#include <fieldvariant.h>

class SQLiteWriter
{

    bool parseField(FieldVariant &fieldVariant, QString &outValue);
public:
    SQLiteWriter();

    bool writePosition(QList<FieldVariant> fieldsVariant);
    bool writeEmployee(QList<FieldVariant> fieldsVariant);
    bool writeClient(QList<FieldVariant> fieldsVariant);
    bool writeOrder(QList<FieldVariant> fieldsVariant);
    bool writeAnimal(QList<FieldVariant> fieldsVariant);
};

#endif // SQLITEWRITER_H
