#include "sqlitemanager.h"

#include <settingsrepository.h>
#include <sqlitereader.h>
#include <sqlitewriter.h>

SQLiteManager::SQLiteManager(QString dbName) :
    mDbName(dbName)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mSqliteReader = nullptr;
    mSqliteWriter = nullptr;
}

bool SQLiteManager::connect()
{
    mDb.setDatabaseName(mDbName);

    if (!mDb.open()) {
        qDebug() << "Cannot open database: " << mDb.lastError();
        return false;
    }
    qDebug() << mDb.isValid();
    mSqliteReader = new SQLiteReader();
    mSqliteWriter = new SQLiteWriter();
    return true;
}

void SQLiteManager::close()
{
    if (mDb.isOpen())
        mDb.close();
}

// удаляет все таблицы, а затем создает их и заполняет заново,
// SQL команды берутся из файла create_pytomnik_db.sql
bool SQLiteManager::resetDb()
{
    QFile sqlFile(SettingsRepository::creationDbSqlScriptPath);
    if (!sqlFile.exists())
        return false;

    bool isOpen = sqlFile.open(QIODevice::ReadOnly);
    if (!isOpen)
        return false;

    QTextStream in(&sqlFile);
    QString text = in.readAll();

    if (text.size() == 0)
        return false;

    if (!removeDbFile())
        return false;

    bool isOK = true;
    mDb.transaction();
    QStringList sqlStatementsWithEmptyLines = text.split('\n');
    for (auto& sqlStatement : sqlStatementsWithEmptyLines) {
        if (sqlStatement.isEmpty())
            continue;
       QSqlQuery query;
       isOK &= query.exec(sqlStatement);
       if (!isOK) break;
    }
    if (!isOK) {
        mDb.rollback();
    } else {
        mDb.commit();
    }
    return isOK;
}

// удаляет файл базы данных SQLite
bool SQLiteManager::removeDbFile()
{
    close();
    bool result = QFile("pitomnic_db.sqlite").remove();
    result &= connect();
    return result;
}

QString SQLiteManager::getLastError()
{
    QString error = mDb.lastError().text();
    QString dbError = mDb.lastError().databaseText();
    QString driverError = mDb.lastError().driverText();

    QString result;
    if (!error.isEmpty()) {
        result += error;
    }

    if (!dbError.isEmpty()) {
        result = result + "\n" + dbError;
    }

    if (!driverError.isEmpty()) {
        result = result + "\n" + driverError;
    }
    return result.isEmpty() ? "Действие не выполнено: произошла неизвестная ошибка!" : result;
}

SQLiteReader *SQLiteManager::getSqliteReader() const
{
    return mSqliteReader;
}

SQLiteWriter *SQLiteManager::getSqliteWriter() const
{
    return mSqliteWriter;
}
