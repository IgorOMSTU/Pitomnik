#ifndef ALTERNATIVES_H
#define ALTERNATIVES_H

#include <stdafx.h>

// Класс осуществляет отображение внешних ключей на строки,
// которые будут показаны в комбобоксе в диалоге AddNewRecordDialog.
// Например, внешний ключ в таблице Employee в поле Position - это 1.
// 1 отображается в наименование должности "Директор" из таблицы Positions.
class Alternatives
{
    QList<int> mKeys;
    QHash<int, QString> mAlternatives;

public:
    Alternatives(QHash<int, QString> alternatives);

    int size();
    QString getStrinigValue(int index);
    int getKeyValue(int index);
};

#endif // ALTERNATIVES_H
