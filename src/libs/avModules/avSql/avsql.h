#ifndef AVSQL_H
#define AVSQL_H

#include "avmodules_global.h"
#include "qsqlgenerator.h"
#include "QSqlDatabase"

namespace AvSQL_types{
enum type_field{
    avVARCHAR,
    avTINYINT,
    avINT,
    avINT64,
    avINTEGER,
    avDATE,
    avDATETIME,
    avTIMESTAMP,
    avDOUBLE,
    avTEXT,
    avBLOB,
    avBINARY
};
}

struct fieldTable{
    QString name;
    AvSQL_types::type_field type;
    bool NotNULL;
    int size;
    bool key;
    QVariant Default;
    QStringList UNIQUE;
};

class AVMODULESSHARED_EXPORT AvSQL
{

public:
    AvSQL(QString &prefix);
    bool open();
    void close();
    void set_dbName(QString &name,bool include_prefix = false);
    void set_dbPassword(QString Password);
    void set_dbUserName(QString UserName);
    void set_dbHost(QString Host);
    void set_dbPort(int port);
    void set_dbDriver(QString Driver);
    void set_Prefix(QString &prefix);
    QString TableName(QString tableName);

    QStringList drivers();

    QSqlQuery execQuery(const QString& query);

    QSqlDatabase getDb();
    QSqlQuery getQuery();

    QSqlGenerator* newSqlGenerator();
    QSqlGenerator* newSqlGenerator(QSqlQuery query);
    QSqlGenerator* getSqlGenerator();

    bool CreateTable(QString tName, QList<fieldTable> fields);

private:
    QSqlDatabase p_db;
    QString p_dbName;
    QString p_dbPassword;
    QString p_dbUserName;
    QString p_dbHost;
    int     p_dbPort;
    QString p_dbDriver;
    QString p_prefix;
    QStringList p_dbDrivers;
    QSqlGenerator* p_sqlGenerator;

    QSqlQuery p_query;

    QString get_type(AvSQL_types::type_field type);
};

#endif // AVSQL_H
