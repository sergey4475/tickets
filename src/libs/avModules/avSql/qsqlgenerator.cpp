#include "qsqlgenerator.h"

//------------------------------------------------------------------------------
QSqlGenerator::QSqlGenerator()
{
    m_escapeNames = false;
    clear();
    query = 0;
}

//------------------------------------------------------------------------------
QSqlGenerator::QSqlGenerator(QSqlQuery &value)
{
    m_escapeNames = false;
    clear();
    query = &value;
}

//------------------------------------------------------------------------------
QSqlGenerator::~QSqlGenerator()
{
    clear();
}

//------------------------------------------------------------------------------
QString QSqlGenerator::escapeIdentifer(QString value)
{
    return QString("\"" + value + "\"");
}

//------------------------------------------------------------------------------
QString QSqlGenerator::converVariantToSQLString(QVariant value)
{
    if (value.type() == QVariant::String)
        return QString("'%1'").arg(value.toString());


    if (value.canConvert(QVariant::String))
        return value.toString();
    else
        return "";
}

//------------------------------------------------------------------------------
QString QSqlGenerator::asString()
{
    QString sql;
    switch (m_queryType)
    {
    case SelectQuery:
        sql = buildSelectQuery();
        break;
    case InsertQuery:
        sql = buildInsertQuery();
        break;
    case UpdateQuery:
        sql = buildUpdateQuery();
        break;
    case DeleteQuery:
        sql = buildDeleteQuery();
        break;
    default:
        return "";
    }
    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildSelectQuery()
{
    QString sql;
    sql = "SELECT ";
    if (m_distinct)
        sql += "DISTINCT ";
    sql += buildSelectQueryFieldsSection();
    sql += " FROM ";
    sql += buildTableSection();
    if (m_join.count() > 0)
        sql += buildSelectQueryJoinSection();
    if (m_where.count() > 0)
        sql += buildWhereSection();

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildSelectQueryJoinSection()
{
    QString sql;
    QString name;
    QString alias;
    for (int i = 0; i < m_join.size(); ++i)
    {
        tableDef item = m_join.at(i);

        if (m_escapeNames)
        {
            name = escapeIdentifer(item.name);
            alias = escapeIdentifer(item.alias);
        }
        else
        {
            name = item.name;
            alias = item.alias;
        }

        switch (item.joinType)
        {
        case NoJoin:
            if (item.alias.isEmpty())
                sql += QString(", %1").arg(name);
            else
                sql += QString(", %1 %2").arg(name, alias);
            break;
        case LeftJoin:
            if (item.alias.isEmpty())
                sql += QString(" LEFT JOIN %1 ON %2").arg(name, item.cond);
            else
                sql += QString(" LEFT JOIN %1 %2 on %3").arg(name, alias, item.cond);
            break;
        case RightJoin:
            if (item.alias.isEmpty())
                sql += QString(" RIGHT JOIN %1 ON %2").arg(name, item.cond);
            else
                sql += QString(" RIGHT JOIN %1 %2 on %3").arg(name, alias, item.cond);
            break;
        case InnerJoin:
            if (item.alias.isEmpty())
                sql += QString(" INNER JOIN %1 ON %2").arg(name, item.cond);
            else
                sql += QString(" INNER JOIN %1 %2 on %3").arg(name, alias, item.cond);
            break;
        case OuterJoin:
            if (item.alias.isEmpty())
                sql += QString(" OUTER JOIN %1 ON %2").arg(name, item.cond);
            else
                sql += QString(" OUTER JOIN %1 %2 on %3").arg(name, alias, item.cond);
            break;
        case FullJoin:
            if (item.alias.isEmpty())
                sql += QString(" FULL JOIN %1 ON %2").arg(name, item.cond);
            else
                sql += QString(" FULL JOIN %1 %2 on %3").arg(name, alias, item.cond);
            break;
        }
    }
    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildWhereSection()
{
    QString sql = " WHERE ";
    QString key;
    for (int i = 0; i < m_where.size(); ++i)
    {
        whereDef item = m_where.at(i);

        if (m_escapeNames)
            key = escapeIdentifer(item.key);
        else
            key = item.key;

        switch (item.whereType)
        {

        case RawWhere:
            sql += item.raw;
            break;
        case InWhere:
            if (item.value.canConvert(QVariant::List))
            {
                sql += key + " in (";
                for (int j = 0; j < item.value.toList().count(); ++j)
                {
                    QString value;
                    if (m_escapeNames)
                        value = escapeIdentifer(item.value.toList().at(j).toString());
                    else
                        value = item.value.toList().at(j).toString();
                    sql += value;
                    if (j < item.value.toList().count() - 1)
                        sql += ", ";
                }
                sql += ")";
            }
            break;
        case CondWhere:
            sql += QString("%1 %2 %3").arg(key, item.cond,
                                           converVariantToSQLString(item.value));
            break;
        }
        if (i < m_where.size()-1)
        {
            if (item.chain == AndChain) sql += " and ";
            if (item.chain == OrChain) sql += " or ";
        }
    }
    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildTableSection()
{
    QString sql;
    QString name;
    QString alias;
    if (m_escapeNames)
    {
        name = escapeIdentifer(m_from.name);
        alias = escapeIdentifer(m_from.alias);
    }
    else
    {
        name = m_from.name;
        alias = m_from.alias;
    }

    if (m_from.alias.isEmpty())
        sql = name;
    else
        sql = QString("%1 %2").arg(name, alias);

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildSelectQueryFieldsSection()
{
    QString sql = "";
    QString name;
    QString alias;

    for (int i = 0; i < m_select.size(); ++i)
    {
        fieldDef item = m_select.at(i);

        bool local_escape;
        if (item.escapeType == DefaultEscape)
            local_escape = m_escapeNames;
        else
            local_escape = item.escapeType == UseEscape;

        if (local_escape)
        {
            if (item.name == "*")
                name = item.name;
            else
                name = escapeIdentifer(item.name);
            alias = escapeIdentifer(item.alias);
        }
        else
        {
            name = item.name;
            alias = item.alias;
        }

        switch (item.funcType)
        {
        case SimpleField:
            if (item.alias.isEmpty())
                sql += QString("%1").arg(name);
            else
                sql += QString("%1 AS %2").arg(name, alias);
            break;
        case MaxFunc:
            if (item.alias.isEmpty())
                sql += QString("MAX(%1)").arg(name);
            else
                sql += QString("MAX(%1) AS %2").arg(name, alias);
            break;
        case MinFunc:
            if (item.alias.isEmpty())
                sql += QString("MIN(%1)").arg(name);
            else
                sql += QString("MIN(%1) AS %2").arg(name, alias);
            break;
        case AvgFunc:
            if (item.alias.isEmpty())
                sql += QString("AVG(%1)").arg(name);
            else
                sql += QString("AVG(%1) AS %2").arg(name, alias);
            break;
        case SumFunc:
            if (item.alias.isEmpty())
                sql += QString("SUM(%1)").arg(name);
            else
                sql += QString("SUM(%1) AS %2").arg(name, alias);
            break;
        case CountFunc:
            if (item.alias.isEmpty())
                sql += QString("COUNT(%1)").arg(name);
            else
                sql += QString("COUNT(%1) AS %2").arg(name, alias);
            break;
        }
        if (i < m_select.size() - 1)
            sql += ", ";
    }

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildInsertQuery()
{
    QString sql;
    sql = "INSERT INTO ";
    sql += buildTableSection();
    sql += " (";
    sql += buildInsertQueryFieldsSection();
    sql += ") VALUES (";
    sql += buildInsertQueryValuesSection();
    sql += ")";

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildInsertQueryFieldsSection()
{
    QString sql = "";
    QString field;

    for (int i = 0; i < m_insert.size(); ++i)
    {
        insertDef item = m_insert.at(i);

        bool local_escape;
        if (item.escapeType == DefaultEscape)
            local_escape = m_escapeNames;
        else
            local_escape = item.escapeType == UseEscape;

        if (local_escape)
            field = escapeIdentifer(item.field);
        else
            field = item.field;

        sql += QString("%1").arg(field);

        if (i < m_insert.size() - 1)
            sql += ", ";
    }

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildInsertQueryValuesSection()
{
    QString sql = "";
    QString value;

    for (int i = 0; i < m_insert.size(); ++i)
    {
        insertDef item = m_insert.at(i);

        value = converVariantToSQLString(item.value);

        sql += QString("%1").arg(value);

        if (i < m_insert.size() - 1)
            sql += ", ";
    }

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildUpdateQuery()
{
    QString sql;
    sql = "UPDATE ";
    sql += buildTableSection();
    sql += " SET ";
    sql += buildUpdateQueryFieldsSection();
    sql += buildWhereSection();

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildUpdateQueryFieldsSection()
{
    QString sql = "";
    QString field;
    QString value;

    for (int i = 0; i < m_update.size(); ++i)
    {
        updateDef item = m_update.at(i);

        bool local_escape;
        if (item.escapeType == DefaultEscape)
            local_escape = m_escapeNames;
        else
            local_escape = item.escapeType == UseEscape;

        if (local_escape)
            field = escapeIdentifer(item.field);
        else
            field = item.field;

        value = converVariantToSQLString(item.value);

        sql += QString("%1 = %2").arg(field, value);

        if (i < m_update.size() - 1)
            sql += ", ";
    }

    return sql;
}

//------------------------------------------------------------------------------
QString QSqlGenerator::buildDeleteQuery()
{
    QString sql;
    sql = "DELETE FROM ";
    sql += buildTableSection();
    sql += buildWhereSection();

    return sql;
}

//------------------------------------------------------------------------------
void QSqlGenerator::clear()
{
    m_queryType = UnknownQuery;
    m_select.clear();
    m_distinct = false;
    m_from.alias = "";
    m_from.name = "";
    m_from.cond = "";
    m_from.joinType = NoJoin;
    m_join.clear();
    m_where.clear();
    m_groupby.clear();
    m_having.clear();
    m_orderby.clear();
    m_haveLimit = false;
    m_haveOffset = false;
    m_insert.clear();
    m_update.clear();
}

//------------------------------------------------------------------------------
bool QSqlGenerator::isEscape()
{
    return m_escapeNames;
}

//------------------------------------------------------------------------------
void QSqlGenerator::setEscape(bool value)
{
    m_escapeNames = value;
}

//------------------------------------------------------------------------------
bool QSqlGenerator::buildSql()
{
    query->prepare(asString());
    // todo
    return true;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select(QString field, QString alias,
                                     escapeTypes escape)
{
    m_queryType = SelectQuery;
    fieldDef tmp;
    tmp.name = field;
    tmp.alias = alias;
    tmp.funcType = SimpleField;
    tmp.escapeType = escape;
    m_select.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select(QMap<QString, QString> fields)
{
    m_queryType = SelectQuery;
    QMap<QString, QString>::const_iterator i = fields.constBegin();
    while (i != fields.constEnd())
    {
        fieldDef tmp;
        tmp.name = i.key();
        tmp.alias = i.value();
        tmp.funcType = SimpleField;
        tmp.escapeType = DefaultEscape;
        m_select.append(tmp);
        ++i;
    }
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select(QList<QString> fields)
{
    m_queryType = SelectQuery;
    QList<QString>::const_iterator i = fields.constBegin();
    while (i != fields.constEnd())
    {
        fieldDef tmp;
        tmp.name = i[0];
        tmp.alias = "";
        tmp.funcType = SimpleField;
        tmp.escapeType = DefaultEscape;
        m_select.append(tmp);
        ++i;
    }
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select_max(QString field, QString alias,
                                         escapeTypes escape)
{
    _max_min_avg_sum(field, alias, MaxFunc, escape);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select_min(QString field, QString alias,
                                         escapeTypes escape)
{
    _max_min_avg_sum(field, alias, MinFunc, escape);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select_avg(QString field, QString alias,
                                         escapeTypes escape)
{
    _max_min_avg_sum(field, alias, AvgFunc, escape);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select_sum(QString field, QString alias,
                                         escapeTypes escape)
{
    _max_min_avg_sum(field, alias, SumFunc, escape);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::select_count(QString field, QString alias,
                                           escapeTypes escape)
{
    _max_min_avg_sum(field, alias, CountFunc, escape);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::_max_min_avg_sum(QString field, QString alias,
                                              fieldFuncTypes type, escapeTypes escape)
{
    m_queryType = SelectQuery;
    fieldDef tmp;
    tmp.name = field;
    tmp.alias = alias;
    tmp.funcType = type;
    tmp.escapeType = escape;
    m_select.append(tmp);
    return *this;
}
//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::distinct()
{
    m_distinct = true;
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::from(QString table, QString alias)
{
    m_from.name = table;
    m_from.alias = alias;
    m_from.cond = "";
    m_from.joinType = NoJoin;
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::join(QString table, QString cond, QString alias,
                                   tableJoinTypes type)
{
    tableDef tmp;
    tmp.name = table;
    tmp.alias = alias;
    tmp.cond = cond;
    tmp.joinType = type;
    m_join.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::where(QString raw, chainTypes chain)
{
    _where_in(raw, chain);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::where(QString key, QString cond, QVariant value,
                                    chainTypes chain)
{
    _where_in(key, cond, value, chain);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::where_in(QString key, QList<QVariant> values,
                                       chainTypes chain)
{
    _where_in(key, values, false, chain);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::where_not_in(QString key, QList<QVariant> values,
                                           chainTypes chain)
{
    _where_in(key, values, true, chain);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::_where_in(QString raw, chainTypes chain)
{
    whereDef tmp;
    tmp.whereType = RawWhere;
    tmp.raw = raw;
    tmp.chain = chain;
    m_where.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::_where_in(QString key, QString cond,
                                        QVariant value, chainTypes chain)
{
    whereDef tmp;
    tmp.whereType = CondWhere;
    tmp.key = key;
    tmp.cond = cond;
    tmp.value = value;
    tmp.chain = chain;
    m_where.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::_where_in(QString key, QList<QVariant> values,
                                        bool negative, chainTypes chain)
{
    whereDef tmp;
    tmp.whereType = InWhere;
    tmp.key = key;
    tmp.value = values;
    tmp.negative = negative;
    tmp.chain = chain;
    m_where.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::group_by(QString by)
{
    m_groupby.append(by);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::having(QString raw)
{
    havingDef tmp;
    tmp.havingType = RawHaving;
    tmp.raw = raw;
    tmp.chain = AndChain;
    m_having.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::or_having(QString raw)
{
    havingDef tmp;
    tmp.havingType = RawHaving;
    tmp.raw = raw;
    tmp.chain = OrChain;
    m_having.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::having(QString key, QString value, bool escape)
{
    havingDef tmp;
    tmp.havingType = KeyValueHaving;
    tmp.key = key;
    tmp.value = value;
    tmp.escape = escape;
    tmp.chain = AndChain;
    m_having.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::or_having(QString key, QString value, bool escape)
{
    havingDef tmp;
    tmp.havingType = KeyValueHaving;
    tmp.key = key;
    tmp.value = value;
    tmp.escape = escape;
    tmp.chain = OrChain;
    m_having.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::order_by(QString orderby, QString direction)
{
    orderbyDef tmp;
    tmp.orderby = orderby;
    tmp.direction = direction;
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::limit(int value, int offset)
{
    m_haveLimit = true;
    m_limit = value;
    if (offset > 0)
    {
        m_haveOffset = true;
        m_offset = offset;
    }
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::offset(int offset)
{
    m_haveOffset = true;
    m_offset = offset;
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::insertInto(QString table)
{
    m_queryType = InsertQuery;
    m_from.name = table;
    m_from.alias = "";
    m_from.cond = "";
    m_from.joinType = NoJoin;
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::insert(QString field, QVariant value,
                                     escapeTypes escape)
{
    m_queryType = InsertQuery;
    insertDef tmp;
    tmp.field = field;
    tmp.value = value;
    tmp.escapeType = escape;
    m_insert.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::insert(QMap<QString, QVariant> fields,
                                     escapeTypes escape)
{
    m_queryType = InsertQuery;
    QMap<QString, QVariant>::const_iterator i = fields.constBegin();
    while (i != fields.constEnd())
    {
        insertDef tmp;
        tmp.field = i.key();
        tmp.value = i.value();
        tmp.escapeType = escape;
        m_insert.append(tmp);
        ++i;
    }
    return *this;
}


//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::updateTable(QString table)
{
    m_queryType = UpdateQuery;
    m_from.name = table;
    m_from.alias = "";
    m_from.cond = "";
    m_from.joinType = NoJoin;
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::update(QString field, QVariant value, escapeTypes escape)
{
    m_queryType = UpdateQuery;
    updateDef tmp;
    tmp.field = field;
    tmp.value = value;
    tmp.escapeType = escape;
    m_update.append(tmp);
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::update(QMap<QString, QVariant> fields, escapeTypes escape)
{
    m_queryType = UpdateQuery;
    QMap<QString, QVariant>::const_iterator i = fields.constBegin();
    while (i != fields.constEnd())
    {
        updateDef tmp;
        tmp.field = i.key();
        tmp.value = i.value();
        tmp.escapeType = escape;
        m_update.append(tmp);
        ++i;
    }
    return *this;
}

//------------------------------------------------------------------------------
QSqlGenerator &QSqlGenerator::deleteFrom(QString table)
{
    m_queryType = DeleteQuery;
    m_from.name = table;
    m_from.alias = "";
    m_from.cond = "";
    m_from.joinType = NoJoin;
    return *this;
}
