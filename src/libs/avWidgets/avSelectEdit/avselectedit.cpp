#include "avselectedit.h"
#include <QCalendarWidget>
#include <QDoubleValidator>
#include <QFileDialog>

avSelectEdit::avSelectEdit(QWidget *parent) : QWidget(parent)
{
    p_digit = 2;
    p_length= 10;
    f_dec = false;

    p_qleEdit= new QLineEdit(this);

    p_button=new QToolButton(this);
    p_button->setCursor(Qt::ArrowCursor);
    p_button->setGeometry(0,0,20,20);

    QHBoxLayout* qhblLayout=new QHBoxLayout(this);

    qhblLayout->addWidget(p_qleEdit);

    qhblLayout->addWidget(p_button);
    qhblLayout->setContentsMargins(0,0,0,0);
    qhblLayout->setSpacing(0);

    this->setLayout(qhblLayout);

    setConnects();
    updateControl();
}
//***** Обработка установки свойств
/**
 * @brief avSelectEdit::setButtonVisible
 * @param visible
 */
void avSelectEdit::setButtonVisible(bool visible)
{
    p_visible = visible;
    p_button->setVisible(visible);

}

/**
 * @brief avSelectEdit::setAnyFolder
 * @param anyFolder
 */
void avSelectEdit::setAnyFolder(bool anyFolder)
{
    p_anyFolder = anyFolder;
}

/**
 * @brief avSelectEdit::setTypeSelect
 * @param typeSelect
 */
void avSelectEdit::setTypeSelect(avSelectEdit::Type_Select typeSelect)
{
    p_typeSelect = typeSelect;
    updateControl();
}

/**
 * @brief avSelectEdit::setDigit
 * @param digit
 */
void avSelectEdit::setDigit(int digit)
{
    p_digit = digit;
}

/**
 * @brief avSelectEdit::date - Возвращает дату
 * @return
 */
const QDate avSelectEdit::date()
{
    return QDate::fromString(p_qleEdit->text(),"dd.MM.yyyy");
}

/**
 * @brief avSelectEdit::setDateCalendar - Установка даты
 * @param date
 */
void avSelectEdit::setDateCalendar(QDate date)
{
    if (date.isValid())
        p_qleEdit->setText(date.toString("dd.MM.yyyy"));
}

/**
 * @brief avSelectEdit::setLength
 * @param length
 */
void avSelectEdit::setLength(int length)
{
    p_length = length;
}

//********************************************************

void avSelectEdit::setConnects(){
    connect(p_qleEdit,SIGNAL(editingFinished()),this,SLOT(slotCheckValidate()));
    connect(p_qleEdit,SIGNAL(textChanged(const QString&)),this,SLOT(slotTextChanged(const QString&)));
    connect(p_button,SIGNAL(clicked()),this,SLOT(slotButtonClick()));
}

void avSelectEdit::updateControl(){
    setButtonVisible(false);
    p_qleEdit->setReadOnly(false);
    p_qleEdit->setAlignment(Qt::AlignLeft);
    if (p_typeSelect == Calendare){
        // Если параметр ввода даты
        p_qleEdit->removeEventFilter(this);
        p_button->setIcon(QIcon(":calendar.png"));
        p_qleEdit->setInputMask("00.00.0000");
        setButtonVisible(true);
    }else if (p_typeSelect == Nothing){

        p_qleEdit->setInputMask("");
        p_qleEdit->removeEventFilter(this);
        p_button->setText("...");
        p_button->setIcon(QIcon::fromTheme("edit-clear"));
        setButtonVisible(true);
    }else if (p_typeSelect == OpenFileDialog){
        p_qleEdit->setReadOnly(true);
        setButtonVisible(true);
    }else{
        // Если параметр ввода числа
        p_qleEdit->setAlignment(Qt::AlignRight);
        p_qleEdit->setInputMask("");
        p_qleEdit->installEventFilter(this);
        p_qleEdit->setValidator(new QDoubleValidator(0,0,p_digit,this));
        p_button->setIcon(QIcon::fromTheme("edit-clear"));
    }
    //p_button->setStyleSheet("border: solid 1px black;");
}

//*** SLOTS

void avSelectEdit::slotTextChanged(const QString& text)
{
    if (p_typeSelect == Calendare){
        QStringList qslTmp=text.split(".");
        if (qslTmp.at(0).toInt()>31 || qslTmp.at(0).toInt()>QDate(qslTmp.at(2).toInt(),qslTmp.at(1).toInt(),01) .daysInMonth())
        {
                p_qleEdit->setCursorPosition(0);
                p_qleEdit->setSelection(0,2);
        }
        if (qslTmp.at(1).toInt()>12)
        {
                p_qleEdit->setCursorPosition(3);
                p_qleEdit->setSelection(3,2);
        }
        QDate date=QDate::fromString(p_qleEdit->text(),"dd.MM.yyyy");
        if (date.isValid())
                emit dateChanged(date);
    }
}

void avSelectEdit::slotCalendar(){
    QCalendarWidget* qcwCalendar=new QCalendarWidget(this);
    qcwCalendar->setWindowFlags(Qt::Popup);
    qcwCalendar->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(qcwCalendar, SIGNAL(clicked(QDate)), this, SLOT(setDate(QDate)));
    QObject::connect(qcwCalendar, SIGNAL(clicked(QDate)), qcwCalendar, SLOT(close()));

    QPoint pos = (this->layoutDirection() == Qt::RightToLeft) ? this->rect().bottomRight() : this->rect().bottomLeft();
    pos = this->mapToGlobal(pos);
    qcwCalendar->move(pos);
    qcwCalendar->setSelectedDate(QDate().fromString(p_qleEdit->text(),"dd.MM.yyyy"));
    qcwCalendar->show();
}

void avSelectEdit::slotOpenFileDialog(){
    if (anyFolder())
        p_qleEdit->setText(QFileDialog::getExistingDirectory());
    else
        p_qleEdit->setText(QFileDialog::getOpenFileName());
}

void avSelectEdit::slotButtonClick()
{
    if (p_typeSelect == Calendare){
        slotCalendar();
    }
    else if (p_typeSelect == OpenFileDialog){
        slotOpenFileDialog();
    }else
        emit buttonClicked();

}

void avSelectEdit::setDate(QDate date)
{
        if (date.isValid())
                p_qleEdit->setText(date.toString("dd.MM.yyyy"));
}

void avSelectEdit::slotCheckValidate()
{
    QDate date=QDate::fromString(p_qleEdit->text(),"dd.MM.yyyy");
    if (!date.isValid())
    {
        if (p_qleEdit->text()!="..")
        {
            p_qleEdit->setFocus();
            p_qleEdit->setCursorPosition(0);
        }
        else
        {
            emit editingFinished();
        }
    }
    else
        emit editingFinished();
}

//***********************

void avSelectEdit::keyPressEvent(QKeyEvent *event){
    QWidget::keyPressEvent(event);
}

// Отбираем события по нажатию клавиш.
// Фильтруем только числовые и "."
// Если длина строки привысила допустимой то печатем дробную часть
bool avSelectEdit::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *pKeyEvent = static_cast<QKeyEvent *>(event);
        if ((pKeyEvent->key() >= Qt::Key_0 && pKeyEvent->key() <= Qt::Key_9)||(pKeyEvent->text()==".")){
            if ((p_qleEdit->text().indexOf(".",0,Qt::CaseInsensitive) == -1)&&(p_qleEdit->text().length() >= p_length)) {
                p_qleEdit->setText(p_qleEdit->text()+".");
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}
