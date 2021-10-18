#include "sqlitereader.h"

SQLiteReader::SQLiteReader()
{
}

QList<FieldVariant> SQLiteReader::createEmptyPosition()
{
    FieldVariant fvPK = FieldVariant::createString("Должности", "Код должности", std::nullopt, false, true);
    FieldVariant fvPosition = FieldVariant::createString("Должности", "Должность", std::nullopt);
    QList<FieldVariant> fieldVariants;
    fieldVariants.append(fvPK);
    fieldVariants.append(fvPosition);
    return fieldVariants;
}

QList<FieldVariant> SQLiteReader::createEmptyEmployee()
{
    QList<FieldVariant> fieldVariants;
    FieldVariant fvPK = FieldVariant::createInt("Сотрудники", "Код сотрудника", std::nullopt, false, true);
    FieldVariant fvName = FieldVariant::createString("Сотрудники", "ФИО", std::nullopt);
    FieldVariant fvAddress = FieldVariant::createString("Сотрудники", "Адрес", std::nullopt);
    FieldVariant fvSalary = FieldVariant::createInt("Сотрудники", "Зарплата (руб.)", std::nullopt);
    FieldVariant fvPhoneNumber = FieldVariant::createString("Сотрудники", "Телефон", std::nullopt);
    FieldVariant fvPosition = FieldVariant::createFK("Сотрудники", "Должность", std::nullopt, positionList());

    fieldVariants.append(fvPK);
    fieldVariants.append(fvName);
    fieldVariants.append(fvAddress);
    fieldVariants.append(fvSalary);
    fieldVariants.append(fvPhoneNumber);
    fieldVariants.append(fvPosition);

    return fieldVariants;
}

QList<FieldVariant> SQLiteReader::createEmptyClients()
{
    QList<FieldVariant> fieldVariants;
    FieldVariant fvPK = FieldVariant::createInt("Клиенты", "Код клиента", std::nullopt, false, true);
    FieldVariant fvName = FieldVariant::createString("Клиенты", "ФИО", std::nullopt);
    FieldVariant fvAddress = FieldVariant::createString("Клиенты", "Адрес", std::nullopt, false);
    FieldVariant fvPhoneNumber = FieldVariant::createString("Клиенты", "Телефон", std::nullopt, false);
    FieldVariant fvEmail = FieldVariant::createString("Клиенты", "Почта", std::nullopt, false);

    fieldVariants.append(fvPK);
    fieldVariants.append(fvName);
    fieldVariants.append(fvAddress);
    fieldVariants.append(fvPhoneNumber);
    fieldVariants.append(fvEmail);

    return fieldVariants;
}

QList<FieldVariant> SQLiteReader::createEmptyEnimals()
{
    QList<FieldVariant> fieldVariants;
    FieldVariant fvPK = FieldVariant::createInt("Животные", "Код животного", std::nullopt, false, true);
    FieldVariant fvNickName = FieldVariant::createString("Животные", "Кличка", std::nullopt);
    FieldVariant fvGender = FieldVariant::createString("Животные", "Пол", std::nullopt);
    FieldVariant fvBreed = FieldVariant::createString("Животные", "Порода", std::nullopt);
    FieldVariant fvDoc = FieldVariant::createFK("Животные", "Ветеринар", std::nullopt, employeesList());
    FieldVariant fvPrice = FieldVariant::createInt("Животные", "Цена (руб.)", std::nullopt);

    fieldVariants.append(fvPK);
    fieldVariants.append(fvNickName);
    fieldVariants.append(fvGender);
    fieldVariants.append(fvBreed);
    fieldVariants.append(fvDoc);
    fieldVariants.append(fvPrice);

    return fieldVariants;
}

QList<FieldVariant> SQLiteReader::createEmptyOrders()
{
    QString currentDate = QDate::currentDate().toString("dd-MM-yyyy");

    QList<FieldVariant> fieldVariants;
    FieldVariant fvPK = FieldVariant::createInt("Заказы", "Код заказа", std::nullopt, false, true);
    FieldVariant fvDate= FieldVariant::createDate("Заказы", "Дата", currentDate);
    FieldVariant fvAnimal = FieldVariant::createFK("Заказы", "Животное", std::nullopt, animalsList());
    FieldVariant fvClient = FieldVariant::createFK("Заказы", "Клиент", std::nullopt, clientsList());

    fieldVariants.append(fvPK);
    fieldVariants.append(fvDate);
    fieldVariants.append(fvAnimal);
    fieldVariants.append(fvClient);

    return fieldVariants;
}

QSqlRelationalTableModel *SQLiteReader::readEmployees()
{
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
    model->setTable("Employees");
    model->setRelation(5, QSqlRelation("Positions", "ID_position", "Position"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->select();
    return model;
}

QSqlRelationalTableModel *SQLiteReader::readPositions()
{
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
    model->setTable("Positions");
    model->select();

    return model;
}

QSqlRelationalTableModel *SQLiteReader::readClients()
{
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
    model->setTable("Clients");
    model->select();
    return model;
}

QSqlRelationalTableModel *SQLiteReader::readAnimals()
{
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
    model->setTable("Animals");
    model->setRelation(4, QSqlRelation("Employees", "ID_employee", "FullName"));
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->select();

    return model;
}

QSqlRelationalTableModel *SQLiteReader::readOrders()
{
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
    model->setTable("Orders");
    model->setRelation(2, QSqlRelation("Animals", "ID_animal", "Nickname"));
    model->setRelation(3, QSqlRelation("Clients", "ID_client", "FullName"));
    model->select();
    return model;
}

Alternatives SQLiteReader::positionList()
{
    QHash<int, QString> positions;
    QSqlQuery query("SELECT ID_position, Position FROM Positions ORDER BY ID_position");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString position = query.value(1).toString();
        positions[id] = position;
    }
    return Alternatives(positions);
}

Alternatives SQLiteReader::clientsList()
{
    QHash<int, QString> fullNames;
    QSqlQuery query("SELECT ID_client, FullName FROM Clients ORDER BY ID_client");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString fullName = query.value(1).toString();
        fullNames[id] = fullName;
    }
    return Alternatives(fullNames);
}

Alternatives SQLiteReader::employeesList()
{
    QHash<int, QString> fullNames;
    QSqlQuery query("SELECT ID_employee, FullName FROM Employees ORDER BY ID_employee");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString fullName = query.value(1).toString();
        fullNames[id] = fullName;
    }
    return Alternatives(fullNames);
}

Alternatives SQLiteReader::animalsList()
{
    QHash<int, QString> nickNames;
    QSqlQuery query("SELECT ID_animal, NickName FROM Animals ORDER BY ID_animal");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString nickName = query.value(1).toString();
        nickNames[id] = nickName;
    }
    return Alternatives(nickNames);
}
