#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <stdafx.h>

class SQLiteReader;
class SQLiteWriter;

// класс отвечает за соединение с базой данный и
// получение ошибок от драйвера СУБД
class SQLiteManager
{
private:
    QString mDbName;
    QSqlDatabase mDb;
    SQLiteReader *mSqliteReader;  // используется для записи данных в БД
    SQLiteWriter *mSqliteWriter;  // используется для чтения данных из БД

    bool removeDbFileAndCreateOne();  // удалить БД и создать заново
public:
    SQLiteManager(QString dbName);

    bool connect();
    void close();

    bool resetDb(); // удалить БД и создать заново

    QString getLastError();

    SQLiteReader *getSqliteReader() const;
    SQLiteWriter *getSqliteWriter() const;
};

#endif // SQLITEMANAGER_H
