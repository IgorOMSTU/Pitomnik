#ifndef SQLITEREADER_H
#define SQLITEREADER_H

#include <stdafx.h>
#include <fieldvariant.h>

class QSqlRelationalTableModel;

class SQLiteReader
{
    Alternatives positionList();
    Alternatives clientsList();
    Alternatives employeesList();
    Alternatives animalsList();

public:
    SQLiteReader();

    QSqlRelationalTableModel *readEmployees();
    QSqlRelationalTableModel *readPositions();
    QSqlRelationalTableModel *readClients();
    QSqlRelationalTableModel *readAnimals();
    QSqlRelationalTableModel *readOrders();

    QList<FieldVariant> createEmptyPosition();
    QList<FieldVariant> createEmptyEmployee();
    QList<FieldVariant> createEmptyClients();
    QList<FieldVariant> createEmptyEnimals();
    QList<FieldVariant> createEmptyOrders();
};

#endif // SQLITEREADER_H
