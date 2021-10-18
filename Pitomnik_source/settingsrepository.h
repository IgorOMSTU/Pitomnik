#ifndef SETTINGSREPOSITORY_H
#define SETTINGSREPOSITORY_H

#include <stdafx.h>

class SettingsRepository
{
public:
    static const QString dbName; // файл с БД SQLite

    // имя файла файл с SQL командами, с помощью которых создается и заполняется БД
    static const QString creationDbSqlScriptPath;
};

#endif // SETTINGSREPOSITORY_H
