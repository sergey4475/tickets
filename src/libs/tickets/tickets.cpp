#include "tickets.h"

/**
 * @brief Tickets::Tickets
 * @param sql
 */
Tickets::Tickets(AvSQL *sql)
{
    setObjectName("Tickets");
    setAvSQL(sql);
}

/**
 * @brief Tickets::setAvSQL
 * @param avSQL
 */
void Tickets::setAvSQL(AvSQL *avSQL){
    p_sql = avSQL;
}

/**
 * @brief Tickets::Init
 * @return
 */
bool Tickets::initialize(QWidget *w){
    QString text;
    QSqlQuery q;
    QSqlGenerator g(q);
    text = g.select("name")
            .select("config")
            .where("id_config = '100'")
            .from(p_sql->TableName("config")).asString();

    q.exec(text);
    if (!q.next())
    {
        QMap<QString,QVariant> rec;
        rec.insert("id_config","100");
        rec.insert("name","tickets");
        rec.insert("config","["
                            "parm:123"
                            "]");

        text = g.insert(rec).insertInto(p_sql->TableName("config")).asString();
        q.exec(text);
    }
    else
    {
        while (q.next()){
            qDebug() << q.value(0).toString();
        }
    }



    return true;

 }
