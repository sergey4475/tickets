#ifndef AVUSERS_H
#define AVUSERS_H

#include <QObject>
#include "avmodules_global.h"
#include "../avCore/avcore.h"
#include "avSql/avsql.h"

class User{
public:
     QString login;
     QString full_name;
     QString password;

 };

Q_DECLARE_METATYPE(User)

class AVMODULESSHARED_EXPORT avUsers : public QObject
{
    Q_OBJECT
public:
    explicit avUsers(AvSQL *sql, QObject *parent = 0);
    void showLoginDlg();

Q_SIGNALS:
    void accepted();
    void rejected();

private:
    void p_addUser(User usr);
    bool p_delUser();
    bool p_setPassword();
    QVector<User> p_getListUser();

    AvSQL *p_lSql;

private slots:
    void accept();
    void reject();


};

#endif // AVUSERS_H
