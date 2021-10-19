#ifndef FIELDVARIANT_H
#define FIELDVARIANT_H

#include <stdafx.h>
#include <alternatives.h>

// тип поля FieldVariant
enum FieldType { Int, String, Date, FK };

// хранит одно поле строки в таблице БД
class FieldVariant
{
private:
    QString mTableName;    // имя таблицы
    QString mColumnName;   // имя колонки

    std::optional<QString> mString;   // данные для типов String и Date
    std::optional<int> mInt;          // данные для типов Int и FK

    std::optional<Alternatives> mAlternatives;  // см. описание класса Alternatives

    FieldType mFieldType;

    bool mIsHidden;     // показывать поле в диалоге AddNewRecordDialog
    bool mIsRequired;   // поле обязательно для заполнения пользователем в диалоге AddNewRecordDialog

public:
    static FieldVariant createInt(QString tableName, QString domainName, std::optional<int> value, bool isRequired = true, bool isHidden = false);
    static FieldVariant createString(QString tableName, QString domainName, std::optional<QString> value, bool isRequired = true, bool isHidden = false);
    static FieldVariant createDate(QString tableName, QString domainName, std::optional<QString> value, bool isRequired = true, bool isHidden = false);

    // value - значение поля, т.е. значение FK

    // Создает объект FieldVariant типа FK.
    // Т.е. объект FieldVariant представляет собой набор внешних ключей, которые доступны для записи в данное поле,
    // которое является ссылкой на другую талицу. В Alternatives передаются числовые значения внешнего ключа и замещающий текст для
    // показа пользователю, в value текущее значение внешнего ключа в данном поле в БД.
    static FieldVariant createFK(QString tableName, QString domainName, std::optional<int> value, Alternatives alternatives, bool isRequired = true, bool isHidden = false);

    FieldType getFieldType();

    QString getTableName();
    QString getColumnName();

    bool isEmpty();

    int toInteger_or(int valueIfNullopt); // т.к. поля mString и mInt являются nullable, то мы вернем valueIfNullopt,
                                            // если они null и значение в них отсутствует
    QString toString_or(QString valueIfNullopt);

    void setValue(int newValue);
    void setValue(QString newValue);

    std::optional<Alternatives> &getAlternatives();

    bool isHidden();
    bool isRequired();
};

#endif // FIELDVARIANT_H
