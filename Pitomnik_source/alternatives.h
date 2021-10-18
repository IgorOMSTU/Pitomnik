#ifndef ALTERNATIVES_H
#define ALTERNATIVES_H

#include <stdafx.h>

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
