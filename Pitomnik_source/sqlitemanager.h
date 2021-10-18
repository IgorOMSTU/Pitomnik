#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <stdafx.h>

class SQLiteReader;
class SQLiteWriter;

class SQLiteManager
{
private:
    QString mDbName;
    QSqlDatabase mDb;
    SQLiteReader *mSqliteReader;
    SQLiteWriter *mSqliteWriter;

    bool removeDbFile();
public:
    SQLiteManager(QString dbName);

    bool connect();
    void close();

    bool resetDb();

    QString getLastError();

    SQLiteReader *getSqliteReader() const;
    SQLiteWriter *getSqliteWriter() const;
};

#endif // SQLITEMANAGER_H
