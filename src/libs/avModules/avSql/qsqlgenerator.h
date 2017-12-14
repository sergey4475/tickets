#ifndef QSQLGENERATOR_H
#define QSQLGENERATOR_H

//------------------------------------------------------------------------------
#include <QtCore>
#include <QSqlQuery>
#include "avmodules_global.h"

//------------------------------------------------------------------------------
class AVMODULESSHARED_EXPORT QSqlGenerator
{
public:
    //----------------------------------------------------------------------
    enum queryTypes {UnknownQuery, SelectQuery, InsertQuery, UpdateQuery, DeleteQuery};
    //----------------------------------------------------------------------
    enum fieldFuncTypes {SimpleField, MaxFunc, MinFunc, AvgFunc, SumFunc, CountFunc};
    //----------------------------------------------------------------------
    enum tableJoinTypes {NoJoin, LeftJoin, RightJoin, InnerJoin, OuterJoin, FullJoin};
    //----------------------------------------------------------------------
    enum chainTypes {AndChain, OrChain};
    //----------------------------------------------------------------------
    enum whereTypes {RawWhere, CondWhere, InWhere};
    //----------------------------------------------------------------------
    enum havingTypes {RawHaving, KeyValueHaving};
    //----------------------------------------------------------------------
    enum escapeTypes {DefaultEscape, UseEscape, NoEscape};
    //----------------------------------------------------------------------
    struct fieldDef
    {
        QString name;
        QString alias;
        fieldFuncTypes funcType;
        escapeTypes escapeType;
    };

    //----------------------------------------------------------------------
    struct tableDef
    {
        QString name;
        QString alias;
        QString cond;
        tableJoinTypes joinType;
    };
    //----------------------------------------------------------------------
    struct whereDef
    {
        whereTypes whereType;
        QString raw; // for Raw type
        QString key;  // for Cond and In type
        QString cond; // for Cond type
        QVariant value; // for Cond and In type
        bool negative; //for In type
        chainTypes chain;
    };
    //----------------------------------------------------------------------
    struct havingDef
    {
        havingTypes havingType;
        QString raw; // for Raw type
        QString key;
        QString value;
        chainTypes chain;
        bool escape;
    };
    //----------------------------------------------------------------------
    struct orderbyDef
    {
        QString orderby;
        QString direction;
    };
    //----------------------------------------------------------------------
    struct insertDef
    {
        QString field;
        QVariant value;
        escapeTypes escapeType;
    };
    //----------------------------------------------------------------------
    struct updateDef
    {
        QString field;
        QVariant value;
        escapeTypes escapeType;
    };


private:
    QSqlQuery *query;

    bool              m_escapeNames;
    queryTypes        m_queryType;
    QList<fieldDef>   m_select;
    bool              m_distinct;
    tableDef          m_from;
    QList<tableDef>   m_join;
    QList<whereDef>   m_where;
    QStringList       m_groupby;
    QList<havingDef>  m_having;
    QList<orderbyDef> m_orderby;
    int               m_limit;
    int               m_offset;
    bool              m_haveLimit;
    bool              m_haveOffset;
    QList<insertDef>  m_insert;
    QList<updateDef>  m_update;

    QString escapeIdentifer(QString value);
    QString converVariantToSQLString(QVariant value);

    QString buildSelectQuery();
    QString buildSelectQueryFieldsSection();
    QString buildSelectQueryJoinSection();

    QString buildInsertQuery();
    QString buildInsertQueryFieldsSection();
    QString buildInsertQueryValuesSection();
    QString buildUpdateQuery();
    QString buildUpdateQueryFieldsSection();
    QString buildDeleteQuery();

    QString buildTableSection();
    QString buildWhereSection();

public:
    QSqlGenerator();
    QSqlGenerator(QSqlQuery &value);
    ~QSqlGenerator();

    // default false
    // use <"> char
    bool isEscape();
    void setEscape(bool value);

    void clear();

    QSqlGenerator & select(QString field = "*", QString alias = "",
                           escapeTypes escape = DefaultEscape);
    // with alias
    QSqlGenerator & select(QMap<QString, QString> fields);
    // without alias
    QSqlGenerator & select(QList<QString> fields);

    QSqlGenerator & select_max(QString field, QString alias = "",
                               escapeTypes escape = DefaultEscape);
    QSqlGenerator & select_min(QString field, QString alias = "",
                               escapeTypes escape = DefaultEscape);
    QSqlGenerator & select_avg(QString field, QString alias = "",
                               escapeTypes escape = DefaultEscape);
    QSqlGenerator & select_sum(QString field, QString alias = "",
                               escapeTypes escape = DefaultEscape);
    QSqlGenerator & select_count(QString field, QString alias = "",
                                 escapeTypes escape = DefaultEscape);
    QSqlGenerator & _max_min_avg_sum(QString field, QString alias,
                                   fieldFuncTypes type, escapeTypes escape);
    QSqlGenerator & distinct();

    QSqlGenerator & from(QString table, QString alias = "");
    QSqlGenerator & join(QString table, QString cond, QString alias = "",
                         tableJoinTypes type = LeftJoin);

    QSqlGenerator & where(QString raw, chainTypes chain = AndChain);
    QSqlGenerator & where(QString key, QString cond, QVariant value,
                          chainTypes chain = AndChain);
    QSqlGenerator & where_in(QString key, QList<QVariant> values,
                             chainTypes chain = AndChain);
    QSqlGenerator & where_not_in(QString key, QList<QVariant> values,
                                 chainTypes chain = AndChain);
    QSqlGenerator & _where_in(QString raw, chainTypes chain);
    QSqlGenerator & _where_in(QString key, QString cond, QVariant value,
                              chainTypes chain);
    QSqlGenerator & _where_in(QString key, QList<QVariant> values,
                              bool negative, chainTypes chain);
    QSqlGenerator & group_by(QString by);

    QSqlGenerator & having(QString raw);
    QSqlGenerator & or_having(QString raw);
    QSqlGenerator & having(QString key, QString value, bool escape = false);
    QSqlGenerator & or_having(QString key, QString value, bool escape = false);
    QSqlGenerator & order_by(QString orderby, QString direction = "");
    QSqlGenerator & limit(int value, int offset = 0);
    QSqlGenerator & offset(int offset);

    QSqlGenerator & insertInto(QString table);
    QSqlGenerator & insert(QString field, QVariant values,
                           escapeTypes escape = DefaultEscape);
    QSqlGenerator & insert(QMap<QString, QVariant> fields,
                           escapeTypes escape = DefaultEscape);

    QSqlGenerator & updateTable(QString table);
    QSqlGenerator & update(QString field, QVariant value,
                           escapeTypes escape = DefaultEscape);
    QSqlGenerator & update(QMap<QString, QVariant> fields,
                           escapeTypes escape = DefaultEscape);

    QSqlGenerator & deleteFrom(QString table);

    QString asString();
    bool buildSql();
};
#endif // QSQLGENERATOR_H
