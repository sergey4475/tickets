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
    // Параметры вводимого числа
    Q_PROPERTY(int length READ length WRITE setLength)
    Q_PROPERTY(int digit READ digit WRITE setDigit)

    Q_ENUMS(Type_Select)

public:
    enum Type_Select{
        Values,
        Calendare,
        Nothing
    };

    explicit avSelectEdit(QWidget *parent = nullptr);

    bool buttonVisible(){return p_visible;}
    void setButtonVisible(bool visible);

    Type_Select typeSelect(){return p_typeSelect;}
    void setTypeSelect(Type_Select typeSelect);

    int length(){return p_length;}
    void setLength(int length);

    int digit(){return p_digit;}
    void setDigit(int digit);

    const QDate date();
    void setDateCalendar(QDate date);

    // Функция возвращает число
    double Value(){ return p_qleEdit->text().toDouble();}

private:
    QLineEdit *p_qleEdit;
    QToolButton *p_button;
    bool p_visible;

    Type_Select p_typeSelect;

    int p_length;
    int p_digit;
    bool f_dec;

    void setConnects();
    void slotCalendar();
    void updateControl();
    // Получение параметров вводимого числа (длина, точность)

    virtual bool eventFilter(QObject *obj, QEvent *event);

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
