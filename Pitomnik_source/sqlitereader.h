#ifndef SQLITEREADER_H
#define SQLITEREADER_H

#include <stdafx.h>
#include <fieldvariant.h>

class QSqlRelationalTableModel;

// чтение данных из БД
class SQLiteReader
{
    Alternatives positionList();
    Alternatives clientsList();
    Alternatives employeesList();
    Alternatives animalsList();

public:
    SQLiteReader();

    // чтение данных в QSqlRelationalTableModel;
    // нужно для показа данных в визуальных таблицах
    QSqlRelationalTableModel *readEmployees();
    QSqlRelationalTableModel *readPositions();
    QSqlRelationalTableModel *readClients();
    QSqlRelationalTableModel *readAnimals();
    QSqlRelationalTableModel *readOrders();

    // создание пустого набора данных для записи в него
    // пользовательского ввода в диалоге AddNewRecordDialog
    QList<FieldVariant> createEmptyPosition();
    QList<FieldVariant> createEmptyEmployee();
    QList<FieldVariant> createEmptyClients();
    QList<FieldVariant> createEmptyEnimals();
    QList<FieldVariant> createEmptyOrders();
};

#endif // SQLITEREADER_H
