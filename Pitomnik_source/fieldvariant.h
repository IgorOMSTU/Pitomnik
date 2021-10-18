#ifndef FIELDVARIANT_H
#define FIELDVARIANT_H

#include <stdafx.h>
#include <alternatives.h>

enum FieldType { Int, String, Date, FK };

class FieldVariant
{
private:
    QString mTableName;
    QString mColumnName;

    std::optional<QString> mString;
    std::optional<int> mInt;

    std::optional<Alternatives> mAlternatives;

    FieldType mFieldType;

    bool mIsHidden;
    bool mIsRequired;

public:
    static FieldVariant createInt(QString tableName, QString domainName, std::optional<int> value, bool isRequired = true, bool isHidden = false);
    static FieldVariant createString(QString tableName, QString domainName, std::optional<QString> value, bool isRequired = true, bool isHidden = false);
    static FieldVariant createDate(QString tableName, QString domainName, std::optional<QString> value, bool isRequired = true, bool isHidden = false);

    // value - значение поля, т.е. значение FK
    static FieldVariant createFK(QString tableName, QString domainName, std::optional<int> value, Alternatives alternatives, bool isRequired = true, bool isHidden = false);

    FieldType getFieldType();

    QString getTableName();
    QString getColumnName();

    bool isEmpty();

    int toInteger_or(int valueIfNullopt);
    QString toString_or(QString valueIfNullopt);

    void setValue(int newValue);
    void setValue(QString newValue);

    std::optional<Alternatives> &getAlternatives();

    bool isHidden();
    bool isRequired();
};

#endif // FIELDVARIANT_H
