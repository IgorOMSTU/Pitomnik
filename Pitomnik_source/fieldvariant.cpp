#include "fieldvariant.h"

FieldVariant FieldVariant::createInt(QString tableName, QString domainName, std::optional<int> value, bool isRequired, bool isHidden)
{
    FieldVariant fv;
    fv.mTableName = tableName;
    fv.mColumnName = domainName;
    fv.mInt = value;
    fv.mFieldType = FieldType::Int;
    fv.mIsHidden = isHidden;
    fv.mIsRequired = isHidden ? false : isRequired;
    fv.mAlternatives = std::nullopt;
    return fv;
}

FieldVariant FieldVariant::createString(QString tableName, QString domainName, std::optional<QString> value, bool isRequired, bool isHidden)
{
    FieldVariant fv;
    fv.mTableName = tableName;
    fv.mColumnName = domainName;
    fv.mString = value;
    fv.mFieldType = FieldType::String;
    fv.mIsHidden = isHidden;
    fv.mIsRequired = isHidden ? false : isRequired;
    fv.mAlternatives = std::nullopt;
    return fv;
}

FieldVariant FieldVariant::createDate(QString tableName, QString domainName, std::optional<QString> value, bool isRequired, bool isHidden)
{
    FieldVariant fv;
    fv.mTableName = tableName;
    fv.mColumnName = domainName;
    fv.mString = value;
    fv.mFieldType = FieldType::Date;
    fv.mIsHidden = isHidden;
    fv.mIsRequired = isHidden ? false : isRequired;
    fv.mAlternatives = std::nullopt;
    return fv;
}

FieldVariant FieldVariant::createFK(QString tableName, QString domainName, std::optional<int> value, Alternatives alternatives, bool isRequired, bool isHidden)
{
    FieldVariant fv;
    fv.mTableName = tableName;
    fv.mColumnName = domainName;
    fv.mInt = value;
    fv.mFieldType = FieldType::FK;
    fv.mIsHidden = isHidden;
    fv.mIsRequired = isHidden ? false : isRequired;
    fv.mAlternatives = alternatives;
    return fv;
}

FieldType FieldVariant::getFieldType()
{
    return mFieldType;
}

QString FieldVariant::getTableName()
{
    return mTableName;
}

QString FieldVariant::getColumnName()
{
    return mColumnName;
}

bool FieldVariant::isEmpty()
{
    switch (mFieldType) {
    case Int:
    case FK:
        return mInt == std::nullopt;
    case String:
    case Date:
        return mString == std::nullopt;
    }
}

int FieldVariant::toInteger_or(int valueIfNullopt)
{
    return mInt.value_or(valueIfNullopt);
}

QString FieldVariant::toString_or(QString valueIfNullopt)
{
    return mString.value_or(valueIfNullopt);
}

void FieldVariant::setValue(int newValue)
{
    mInt = newValue;
}

void FieldVariant::setValue(QString newValue)
{
    mString = newValue;
}

bool FieldVariant::isHidden()
{
    return mIsHidden;
}

bool FieldVariant::isRequired()
{
    return mIsRequired;
}

std::optional<Alternatives> &FieldVariant::getAlternatives()
{
    return mAlternatives;
}
