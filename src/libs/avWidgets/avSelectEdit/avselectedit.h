#ifndef AVSELECTEDIT_H
#define AVSELECTEDIT_H

#include <QWidget>
#include <QVBoxLayout>

#include <QKeyEvent>
#include "../avwidgets_global.h"

#include <QDate>
#include <QToolButton>
#include <QLineEdit>
#include <QFileDialog>

class AVWIDGETSSHARED_EXPORT avSelectEdit:public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool buttonVisible READ buttonVisible WRITE setButtonVisible)
    Q_PROPERTY(Type_Select typeSelect READ typeSelect WRITE setTypeSelect)
    Q_PROPERTY(bool anyFolder READ anyFolder WRITE setAnyFolder)
    // Параметры вводимого числа
    Q_PROPERTY(int length READ length WRITE setLength)
    Q_PROPERTY(int digit READ digit WRITE setDigit)

    Q_PROPERTY(QLineEdit::EchoMode echoMode READ echoMode WRITE setEchoMode)
    Q_PROPERTY(QString filterMask READ filterMask WRITE setFilterMask)

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QDate date READ date WRITE setDateCalendar NOTIFY dateChanged)

    Q_ENUMS(Type_Select)

public:
    enum Type_Select{
        String,
        Values,
        Calendare,
        OpenFileDialog,
        Nothing
    };

    explicit avSelectEdit(QWidget *parent = nullptr);

    bool buttonVisible(){return p_visible;}
    void setButtonVisible(bool visible);

    bool anyFolder(){return p_anyFolder;}
    void setAnyFolder(bool anyFolder);

    Type_Select typeSelect(){return p_typeSelect;}
    void setTypeSelect(Type_Select typeSelect);

    int length(){return p_length;}
    void setLength(int length);

    int digit(){return p_digit;}
    void setDigit(int digit);

    QString filterMask(){return p_filterMask;}
    void setFilterMask(QString FilterMask);

    QLineEdit::EchoMode echoMode() {return p_echoMode;}
    void setEchoMode(QLineEdit::EchoMode echoMode);

    QString text(){return p_qleEdit->text();}
    void setText(QString text);

    const QDate date();
    void setDateCalendar(QDate date);

    // Функция возвращает число
    double Value(){ return p_qleEdit->text().toDouble();}

private:
    QLineEdit *p_qleEdit;
    QToolButton *p_button;
    bool p_visible;
    bool p_anyFolder;

    Type_Select p_typeSelect;

    int p_length;
    int p_digit;
    bool f_dec;
    QString p_filterMask;

    void setConnects();
    void slotCalendar();
    void slotOpenFileDialog();
    void updateControl();
    // Получение параметров вводимого числа (длина, точность)

    virtual bool eventFilter(QObject *obj, QEvent *event);

    Type_Select m_typeSelect;

    QLineEdit::EchoMode p_echoMode;

private slots:
    void slotTextChanged(const QString& text);
    void setDate(const QDate date);
    void slotCheckValidate();
    void slotButtonClick();

signals:
    void dateChanged(QDate &Date);
    void editingFinished();
    void buttonClicked();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // AVSELECTEDIT_H
