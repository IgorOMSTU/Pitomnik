#ifndef SQLITEWRITER_H
#define SQLITEWRITER_H

#include <stdafx.h>
#include <fieldvariant.h>

// запись данных в таблицы БД
class SQLiteWriter
{
    // преобразоване значения, хранящегося в FieldVariant в строку
    bool parseField(FieldVariant &fieldVariant, QString &outValue);
public:
    SQLiteWriter();

    // Когда пользователь закончил ввод новых данных в диалоге
    // AddNewRecordDialog, то эти данные передаются сюда для записи в БД.
    // См. описание классов AddNewRecordDialog и FieldVariant
    bool writePosition(QList<FieldVariant> fieldsVariant);
    bool writeEmployee(QList<FieldVariant> fieldsVariant);
    bool writeClient(QList<FieldVariant> fieldsVariant);
    bool writeOrder(QList<FieldVariant> fieldsVariant);
    bool writeAnimal(QList<FieldVariant> fieldsVariant);
};

#endif // SQLITEWRITER_H
