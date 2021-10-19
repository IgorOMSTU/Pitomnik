#ifndef ADDNEWRECORDDIALOG_H
#define ADDNEWRECORDDIALOG_H

#include <stdafx.h>
#include <fieldvariant.h>

class AddNewRecordDialog;

// колбэк-интерфейс,
// метод complete вызывсется из AddNewRecordDialog,
// когда пользователь закончил ввод данных и нажал "Создать";
// подписчиками здесь являются классы диалогов с таблицами,
// где по нажатию кнопки "Добавить", появляется окно AddNewRecordDialog
class ICompletionHandler
{
public:
    virtual void complete(AddNewRecordDialog* addNewRecordDialog) = 0;
};

// Класс диалога QDialog.
// Позволяет добавлять новые запси в базу данных.
class AddNewRecordDialog : public QDialog
{
    Q_OBJECT

    QList<FieldVariant> mFieldsVariant; // список полей, т.е. строка для добавления в таблицу

    // Контролы, в которые пользователь вводит данные.
    // Они сохраняются в массив, чтоб по ним было удобно
    // итерироваться для получения данных, т.к. для каждой таблицы
    // здесь будут свои контролы, т.е. набор контролов
    // определяется во время рабты программы по таблице в БД,
    // в которую мы добавляем запись.
    QList<QWidget*> mWidgets;

    // к каждому контролу мы добавляем т.н. пользовательские данные,
    // это номер поля в списке mWidgets, а эта строка является
    // идентификатором для записи и получения этих даннх
    const QString mWidgetPropertyName;

    // вызывается, когда пользователь успешно закончил ввод данных
    ICompletionHandler *mCompletionHandler;

    // пользователь нажал "Создать", а не "Отмена"
    bool mIsUserChoseCreate;

    // небольшой хак, чтоб показывать пол животного в комбобоксе: "М" и "Ж",
    // а не в обычном текстовом поле
    QString mGender;

public:
    AddNewRecordDialog(QWidget *parent, QList<FieldVariant> fieldsVariant);
    QList<FieldVariant> fieldsVariant() const;

    bool isUserChoseCreate() const { return mIsUserChoseCreate; }

    void showDialog(ICompletionHandler *completionHandler); // показать окно диалога

private:
    void createUI();
    void collectData();  // получить данные из полей ввода
    bool validateData(); // проверка данных на корректность
    void showValidationError();

protected:
    void closeEvent(QCloseEvent *) override;

public slots:
    void cancelSlot();
    void createSlot();
};

#endif // ADDNEWRECORDDIALOG_H
