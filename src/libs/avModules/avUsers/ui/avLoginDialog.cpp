#include "avLoginDialog.h"
#include <QDebug>


avLoginDialog::avLoginDialog(QVector<User> users, QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle(tr("Авторизация пользователя"));

    p_login     = new QComboBox(this);
    p_login->setEditable(true);

    lUsers = users;
    QVector<User>::const_iterator iter;

    for (iter = lUsers.constBegin();iter != lUsers.constEnd();++iter){
        p_login->addItem(iter->full_name,iter->password);
    }

    p_password  = new QLineEdit(this);
    p_password->setEchoMode(QLineEdit::Password);

    connect(p_login,SIGNAL(activated(QString)),this,SLOT(moveFocusToPasswordLine())); // Перенос фокуса на поле пароль
    connect(p_password,SIGNAL(editingFinished()),this,SLOT(moveFocusToAcceptButton())); // Перенос фокуса на кнопку OK

    p_lab_login     = new QLabel("Пользователь:",this);
    p_lab_password  = new QLabel("Пароль:",this);

    p_acceptButton  = new QPushButton("ОК",this);
    p_acceptButton->setAutoDefault(false);
    connect(p_acceptButton,SIGNAL(clicked()),this,SLOT(onAcceptButtonPressed()));

    p_cancelButton = new QPushButton(tr("Cancel"),this);
    p_cancelButton->setAutoDefault(false);
    connect(p_cancelButton, SIGNAL(clicked()),this, SLOT(reject()));

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->setAlignment(Qt::AlignCenter);
    buttonsLayout->addWidget(p_acceptButton);
    buttonsLayout->addWidget(p_cancelButton);

    // компановка окна
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(p_lab_login);
    mainLayout->addWidget(p_login);
    mainLayout->addWidget(p_lab_password);
    mainLayout->addWidget(p_password);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
    //Error window
    errorWindow = new QDialog;
    errorWindow->setWindowTitle(tr("Ошибка авторизации"));
    errorAcceptButton = new QPushButton(tr("Ok"), errorWindow);
    connect(errorAcceptButton, SIGNAL(clicked()),this, SLOT(onAcceptErrorButtonPressed()));
    QLabel* errorLabel = new QLabel(tr("Авторизация не выполнена"), errorWindow);
    QVBoxLayout* errorLayout = new QVBoxLayout(errorWindow);
    errorLayout->setAlignment(Qt::AlignCenter);
    errorLayout->addWidget(errorLabel);
    errorLayout->addWidget(errorAcceptButton);
    errorWindow->setLayout(errorLayout);

}

void avLoginDialog::onAcceptButtonPressed(){
    if (checkAuth()) {
        emit accepted();
        delete errorWindow;
        hide();
    }
    else {
        this->setDisabled(true);
        errorWindow->show();
        p_password->clear();
    }

}

void avLoginDialog::onAcceptErrorButtonPressed(){
    errorWindow->hide();
    this->setDisabled(false);
    p_login->setFocus();
    p_acceptButton->setDefault(false);
}

void avLoginDialog::moveFocusToPasswordLine(){
    p_password->setFocus();
}

void avLoginDialog::moveFocusToAcceptButton(){
    p_acceptButton->setFocus();
    p_acceptButton->setDefault(true);
}

bool avLoginDialog::checkAuth(){
    QString passwd = p_login->currentData().toString();

    if (AvCore::md5(p_password->text()) == passwd) {
        return true;
    }
    else {
        return false;
    }
}
