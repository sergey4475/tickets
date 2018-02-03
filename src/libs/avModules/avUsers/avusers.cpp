#include "avusers.h"
#include "ui/avLoginDialog.h"

avUsers::avUsers(AvSQL *sql, QObject *parent) : QObject(parent)
{
    p_lSql = sql;
}

//###### PRIVATE #######
/**
 * @brief avUsers::p_getListUser - Получает список пользователей Базы данных
 * @return - Вектор структуры (login, name, password)
 */
QVector<User> avUsers::p_getListUser()
{
    QString text;
    QVector<User> lUsers;
    QSqlGenerator g = *p_lSql->getSqlGenerator();
    text = g.select("login")
            .select("full_name")
            .select("password")
            .from(p_lSql->TableName("users")).asString();

    QSqlQuery q = p_lSql->execQuery(text);

    while (q.next()){
        User usr;

        usr.login      = q.value(0).toString();
        usr.full_name  = q.value(1).toString();
        usr.password   = q.value(2).toString();

        lUsers.append(usr);
    }
    return lUsers;
}

void avUsers::p_addUser(User usr){
    QMap<QString, QVariant> lRec;
    QString sqlText;
    QSqlGenerator g = *p_lSql->getSqlGenerator();

    lRec.insert("login",usr.login);
    lRec.insert("full_name",usr.full_name);
    lRec.insert("password",AvCore::md5(usr.password));

    sqlText = g.insert(lRec).insertInto(p_lSql->TableName("users")).asString();
    p_lSql->execQuery(sqlText);

}

//## DIALOG ##

/**
 * @brief avUsers::showLoginDlg
 */
void avUsers::showLoginDlg(){
    avLoginDialog *loginDlg = new avLoginDialog(p_getListUser());
    loginDlg->show();

    QObject::connect(loginDlg,SIGNAL(accepted()),this,SLOT(accept()));
    QObject::connect(loginDlg,SIGNAL(rejected()),this,SLOT(reject()));
}

//## SLOTS

void avUsers::accept(){
    emit accepted();
}

void avUsers::reject(){
    emit rejected();
}
