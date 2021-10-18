#ifndef ADDNEWRECORDDIALOG_H
#define ADDNEWRECORDDIALOG_H

#include <stdafx.h>
#include <fieldvariant.h>

class AddNewRecordDialog;

class ICompletionHandler
{
public:
    virtual void complete(AddNewRecordDialog* addNewRecordDialog) = 0;
};

class AddNewRecordDialog : public QDialog
{
    Q_OBJECT

    QList<FieldVariant> mFieldsVariant;
    QList<QWidget*> mWidgets;

    const QString mWidgetPropertyName;
    ICompletionHandler *mCompletionHandler;
    bool mIsUserChoseCreate;

    QString mGender;

public:
    AddNewRecordDialog(QWidget *parent, QList<FieldVariant> fieldsVariant);
    QList<FieldVariant> fieldsVariant() const;

    bool isUserChoseCreate() const { return mIsUserChoseCreate; }

    void showDialog(ICompletionHandler *completionHandler);

private:
    void createUI();
    void collectData();
    bool validateData();
    void showValidationError();

protected:
    void closeEvent(QCloseEvent *) override;

public slots:
    void cancelSlot();
    void createSlot();
};

#endif // ADDNEWRECORDDIALOG_H
