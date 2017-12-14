#ifndef AVWIDGETS_H
#define AVWIDGETS_H

#include "avmodules_global.h"
#include <QVector>
#include <QDialog>
#include <QLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "../avusers.h"

class AVMODULESSHARED_EXPORT avLoginDialog : public QDialog
{
    Q_OBJECT
public:

    QVector<User> lUsers;

    avLoginDialog(QVector<User> users,QWidget *parent = 0);

private slots:
    void onAcceptButtonPressed();
    void onAcceptErrorButtonPressed();
    void moveFocusToPasswordLine();
    void moveFocusToAcceptButton();


private:
    QComboBox *p_login;
    QLabel *p_lab_login;

    QLineEdit *p_password;
    QLabel *p_lab_password;

    QPushButton *p_acceptButton;
    QPushButton *p_cancelButton;
    QPushButton* errorAcceptButton;

    QDialog* errorWindow;

    bool checkAuth();

};

#endif // AVWIDGETS_H
