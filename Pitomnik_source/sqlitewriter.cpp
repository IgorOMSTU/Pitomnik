#include "sqlitewriter.h"

SQLiteWriter::SQLiteWriter()
{
}

bool SQLiteWriter::writePosition(QList<FieldVariant> fieldsVariant)
{
    if (fieldsVariant.size() == 0)
        return false;

    QString position;
    bool isOk = parseField(fieldsVariant[1], position);

    if (isOk)
    {
        QSqlQuery query;
        QString sql = QString("INSERT INTO Positions VALUES (NULL, %1)").arg(position);
        isOk &= query.exec(sql);
    }
    return isOk;
}

bool SQLiteWriter::writeEmployee(QList<FieldVariant> fieldsVariant)
{
    if (fieldsVariant.size() == 0)
        return false;

     QString fullName, address, salary, phoneNumber, fkPosition;
     bool isOk = true;

     isOk &= parseField(fieldsVariant[1], fullName);
     isOk &= parseField(fieldsVariant[2], address);
     isOk &= parseField(fieldsVariant[3], salary);
     isOk &= parseField(fieldsVariant[4], phoneNumber);
     isOk &= parseField(fieldsVariant[5], fkPosition);

     if (isOk)
     {
         QSqlQuery query;
         QString sql = QString("INSERT INTO Employees VALUES (NULL, %1, %2, %3, %4, %5)")
                 .arg(fullName)
                 .arg(address)
                 .arg(salary)
                 .arg(phoneNumber)
                 .arg(fkPosition);

         isOk &= query.exec(sql);
     }
     return isOk;
}

bool SQLiteWriter::writeClient(QList<FieldVariant> fieldsVariant)
{
    if (fieldsVariant.size() == 0)
        return false;

     QString fullName, address, phoneNumber, email;
     bool isOk = true;

     isOk &= parseField(fieldsVariant[1], fullName);
     isOk &= parseField(fieldsVariant[2], address);
     isOk &= parseField(fieldsVariant[3], phoneNumber);
     isOk &= parseField(fieldsVariant[4], email);

     if (isOk)
     {
         QSqlQuery query;
         QString sql = QString("INSERT INTO Clients VALUES (NULL, %1, %2, %3, %4)")
                 .arg(fullName)
                 .arg(address)
                 .arg(phoneNumber)
                 .arg(email);

         isOk &= query.exec(sql);
     }
     return isOk;
}

bool SQLiteWriter::writeOrder(QList<FieldVariant> fieldsVariant)
{
    if (fieldsVariant.size() == 0)
        return false;

     QString date, fkAnimal, fkClient;
     bool isOk = true;

     isOk &= parseField(fieldsVariant[1], date);
     isOk &= parseField(fieldsVariant[2], fkAnimal);
     isOk &= parseField(fieldsVariant[3], fkClient);

     if (isOk)
     {
         QSqlQuery query;
         QString sql = QString("INSERT INTO Orders VALUES (NULL, %1, %2, %3)")
                 .arg(date)
                 .arg(fkAnimal)
                 .arg(fkClient);

         isOk &= query.exec(sql);
     }
     return isOk;
}

bool SQLiteWriter::writeAnimal(QList<FieldVariant> fieldsVariant)
{
    if (fieldsVariant.size() == 0)
        return false;

     QString nickName, sex, breed, fkEmployee, price;
     bool isOk = true;

     isOk &= parseField(fieldsVariant[1], nickName);
     isOk &= parseField(fieldsVariant[2], sex);
     isOk &= parseField(fieldsVariant[3], breed);
     isOk &= parseField(fieldsVariant[4], fkEmployee);
     isOk &= parseField(fieldsVariant[5], price);

     if (isOk)
     {
         QSqlQuery query;
         QString sql = QString("INSERT INTO Animals VALUES (NULL, %1, %2, %3, %4, %5)")
                 .arg(nickName)
                 .arg(sex)
                 .arg(breed)
                 .arg(fkEmployee)
                 .arg(price);

         isOk &= query.exec(sql);
     }
     return isOk;
}

bool SQLiteWriter::parseField(FieldVariant &fieldVariant, QString &outValue) {

    if (fieldVariant.isRequired() && fieldVariant.isEmpty())
        return false;

    if (fieldVariant.isEmpty())
    {
        outValue = "NULL";
        return true;
    }

     outValue = "\"%1\"";
     switch (fieldVariant.getFieldType()) {
     case Int:
     case FK:
         outValue = outValue.arg(fieldVariant.toInteger_or(0));
         break;
     case String:
     case Date:
         outValue = outValue.arg(fieldVariant.toString_or(""));
         break;
     default:
         return false;
     }
     return true;
}
