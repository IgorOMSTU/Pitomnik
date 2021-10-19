#include "addnewrecorddialog.h"

AddNewRecordDialog::AddNewRecordDialog(QWidget *parent, QList<FieldVariant> fieldsVariant)
    : QDialog(parent),
      mFieldsVariant(fieldsVariant),
      mWidgetPropertyName("IndexInFieldsVariant"),
      mCompletionHandler(nullptr),
      mGender("Пол")
{
    setWindowTitle("Создание новой записи");

    createUI();
    mIsUserChoseCreate = false;
}

void AddNewRecordDialog::createUI()
{
    QGridLayout *grdLayout = new QGridLayout();
    grdLayout->setContentsMargins(5, 5, 5, 5);
    grdLayout->setSpacing(5);
    grdLayout->setVerticalSpacing(5);
    QVBoxLayout *vbox = new QVBoxLayout();
    setLayout(vbox);

    QLabel *caption = new QLabel(this);
    caption->setText("Поля со звездочкой (*) обязательны к заполнению");
    vbox->addWidget(caption);
    vbox->addStretch();

    vbox->addItem(grdLayout);

    // Контролы для ввода данных создаются во время выполнения,
    // в зависимости от типа полей, который есть в таблице

    for (int i = 0; i < mFieldsVariant.size(); i++)
    {
        auto &fieldVariant = mFieldsVariant[i];
        if (fieldVariant.isHidden())
            continue;
        QLabel *titleWidget = new QLabel(this);
        QWidget *valueWidget = nullptr;

        QString requiredAsterix = fieldVariant.isRequired() ? "*" : "";
        titleWidget->setText(fieldVariant.getColumnName() + requiredAsterix);

        if (fieldVariant.getColumnName() == mGender)
        {
             valueWidget = new QComboBox(this);
             auto combobox = ((QComboBox*)valueWidget);
             combobox->addItem("М");
             combobox->addItem("Ж");
        }
        else if (fieldVariant.getFieldType() == FieldType::Date
                || fieldVariant.getFieldType() == FieldType::String)
        {
            valueWidget = new QLineEdit(this);
            QString value = fieldVariant.toString_or("");
            ((QLineEdit*)valueWidget)->setText(value);
        }
        else if (fieldVariant.getFieldType() == FieldType::Int)
        {
            valueWidget = new QSpinBox(this);
            ((QSpinBox*)valueWidget)->setMaximum(std::numeric_limits<int>::max());
            int value = fieldVariant.toInteger_or(0);
            ((QSpinBox*)valueWidget)->setValue(value);
        }
        // в combobox записывается внешний ключ (скрыт) и строка для отображения
        else if (fieldVariant.getFieldType() == FieldType::FK) {
            valueWidget = new QComboBox(this);
            auto combobox = ((QComboBox*)valueWidget);
            auto &alternatives = fieldVariant.getAlternatives();
            for (int i = 0; i < alternatives->size(); i++) {

                QString displayedStr = alternatives.value().getStrinigValue(i);
                int fk = alternatives.value().getKeyValue(i);

                combobox->addItem(
                            QString("%1 (Код %2)").arg(displayedStr).arg(fk),
                            fk);
            }
        }

        // Записываем номер поля в талице в т.н. user property, это нужно для упрощения получения данных.
        // user property - это словарь с данными, который привязан к некоторому контролу
        valueWidget->setProperty(mWidgetPropertyName.toLocal8Bit().constData(), QVariant(i));

        grdLayout->addWidget(titleWidget, i+1, 0);
        grdLayout->addWidget(valueWidget, i+1, 1);

        mWidgets.append(valueWidget);
    }

    vbox->addStretch();

    QPushButton *createButton = new QPushButton(this);
    QPushButton* cancelButton = new QPushButton(this);
    createButton->setText("Создать");
    cancelButton->setText("Отменить");
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addWidget(createButton);
    hbox->addWidget(cancelButton);

    vbox->addLayout(hbox);

    connect(createButton, SIGNAL(clicked()), this, SLOT(createSlot()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelSlot()));
}

bool AddNewRecordDialog::validateData()
{
    bool isValid = true;
    for (auto widget : mWidgets)
    {
        int index = widget->property(mWidgetPropertyName.toLocal8Bit().constData()).toInt();
        auto &fieldVariant = mFieldsVariant[index];
        if (!fieldVariant.isRequired())
            continue;

        if (widget->inherits(QComboBox::staticMetaObject.className()))
                continue;

        if (fieldVariant.getFieldType() == FieldType::String)
        {
           isValid &= !((QLineEdit*)widget)->text().trimmed().isEmpty();
        }
        else if (fieldVariant.getFieldType() == FieldType::Date)
        {
           QString dateValue = ((QLineEdit*)widget)->text().trimmed();
           QRegularExpression re("^\\d\\d-\\d\\d-\\d\\d\\d\\d$");
           QRegularExpressionMatch match = re.match(dateValue);
           return match.hasMatch();
        }
    }
    return isValid;
}

void AddNewRecordDialog::collectData()
{
    for (auto widget : mWidgets)
    {
        int index = widget->property(mWidgetPropertyName.toLocal8Bit().constData()).toInt();
        auto &fieldVariant = mFieldsVariant[index];

        if (fieldVariant.getColumnName() == mGender)
        {
            QString genderValue = ((QComboBox*)widget)->currentText();
            fieldVariant.setValue(genderValue);
        }
        else if (fieldVariant.getFieldType() == FieldType::Date
                || fieldVariant.getFieldType() == FieldType::String)
        {
            QString text = ((QLineEdit*)widget)->text();
            fieldVariant.setValue(text.trimmed());
        }
        else if (fieldVariant.getFieldType() == FieldType::Int)
        {
            int value = ((QSpinBox*)widget)->value();
            fieldVariant.setValue(value);
        }
        else if (fieldVariant.getFieldType() == FieldType::FK)
        {
            int fk = ((QComboBox*)widget)->currentData().toInt();
            fieldVariant.setValue(fk);
        }
    }
}

QList<FieldVariant> AddNewRecordDialog::fieldsVariant() const
{
    return mFieldsVariant;
}

void AddNewRecordDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    if (mCompletionHandler != nullptr)
        mCompletionHandler->complete(this);
    mCompletionHandler = nullptr;
}

void AddNewRecordDialog::showDialog(ICompletionHandler *completionHandler)
{
    mCompletionHandler = completionHandler;
    show();
}

void AddNewRecordDialog::createSlot()
{
    if (!validateData()) {
        showValidationError();
        return;
    }
    collectData();
    mIsUserChoseCreate = true;
    close();
}

void AddNewRecordDialog::cancelSlot()
{
    close();
}

void AddNewRecordDialog::showValidationError()
{
    QString msg = "Не все обязательные поля заполнены (или заполнены неверно)! Вернитесь к форме и заполните все поля помеченные звездочкой (*).";
    QMessageBox mbox(this);
    mbox.setText(msg);
    mbox.setIcon(QMessageBox::Warning);
    mbox.exec();
}
