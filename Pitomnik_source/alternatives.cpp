#include "alternatives.h"

Alternatives::Alternatives(QHash<int, QString> alternatives)
{
    mAlternatives = alternatives;
    mKeys = alternatives.keys();
    std::sort(mKeys.begin(), mKeys.end());
}

int Alternatives::size()
{
    return mKeys.size();
}

QString Alternatives::getStrinigValue(int index)
{
    int key = mKeys[index];
    return mAlternatives[key];
}

int Alternatives::getKeyValue(int index)
{
    return mKeys[index];
}
