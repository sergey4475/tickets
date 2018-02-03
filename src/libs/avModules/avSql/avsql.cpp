#include "avsql.h"

//------------------------------------------------------------------------------
AvSQL::AvSQL(QString prefix)
{
    p_dbDrivers = drivers();
    p_sqlGenerator = 0;
    set_Prefix(prefix);
}

//------------------------------------------------------------------------------
/**
* @brief AvSQL::set_dbName - Установка параметра DatabaseName
* @param name - Имя базы данных
*/
void AvSQL::set_dbName(QString name, bool include_prefix){
    if (!p_prefix.isEmpty() && include_prefix)
        p_dbName = p_prefix+"_"+name;
    else
        p_dbName = name;
}

/**
* @brief AvSQL::set_dbPassword - Установка параметра Password
* @param Password - Пароль пользователя СУБД
*/
void AvSQL::set_dbPassword(QString Password){
    p_dbPassword = Password;
}

/**
* @brief AvSQL::set_dbUserName - Установка параметра UserName
* @param UserName - Имя пользователя СУБД
*/
void AvSQL::set_dbUserName(QString UserName){
    p_dbUserName = UserName;
}

/**
* @brief AvSQL::set_dbHost
* @param Host
*/
void AvSQL::set_dbHost(QString Host){
    p_dbHost = Host;
}

/**
* @brief AvSQL::set_dbHost
* @param Host
*/
void AvSQL::set_dbPort(int port){
    p_dbPort = port;
}
/**
 * @brief AvSQL::set_dbDriver
 * @param Driver
 */
void AvSQL::set_dbDriver(QString Driver){

    if (Driver == "Postgresql")
        Driver = "QPSQL";

    if (Driver == "SQLite")
        Driver = "QSQLITE";

    p_dbDriver = Driver;
}

/**
 * @brief AvSQL::set_Prefix
 * @param prefix
 */
void AvSQL::set_Prefix(QString prefix){
    p_prefix = prefix;
}

//------------------------------------------------------------------------------
/**
 * @brief AvSQL::TableName
 * @param tableName
 * @return
 */
QString AvSQL::TableName(QString tableName){
    if (!p_prefix.isEmpty())
        return p_prefix+"_"+tableName;
    else
        return tableName;
}

/**
 * @brief AvSQL::db - Возвращает объект QSqlDatabase
 * @return
 */
QSqlDatabase AvSQL::getDb(){
    return p_db;
}

/**
 * @brief AvSQL::open - Открывает базу данных
 * @return - Истина если открыто, ложь если ошибка
 */
bool AvSQL::open(){
    if (p_dbDriver.isEmpty())
        p_dbDriver = "QSQLITE";

    p_db = QSqlDatabase::addDatabase(p_dbDriver);
    p_db.setDatabaseName(p_dbName);
    p_db.setHostName(p_dbHost);
    p_db.setUserName(p_dbUserName);

    if (p_dbPort > 0)
        p_db.setPort(p_dbPort);

    p_db.setPassword(p_dbPassword);
    return p_db.open();
}

/**
 * @brief AvSQL::close - Закрывает базу данных
 */
void AvSQL::close(){
    p_db.close();
}

/**
 * @brief AvSQL::drivers - Возвращает список доступных Драйверов СУБД
 * @return
 */
QStringList AvSQL::drivers(){
    return QSqlDatabase::drivers();
}

/**
 * @brief AvSQL::execQuery - Выполняет запрос
 * @param query
 * @return
 */
QSqlQuery AvSQL::execQuery(const QString &query)
{
    return getDb().exec(query);
}

//------------------------------------------------------------------------------
/**
 * @brief AvSQL::SqlGenerator
 * @return
 */
QSqlGenerator *AvSQL::newSqlGenerator()
{
    if (p_sqlGenerator == 0)
        p_sqlGenerator = new QSqlGenerator();

    return p_sqlGenerator;
}

/**
 * @brief AvSQL::SqlGenerator
 * @param query
 * @return
 */
QSqlGenerator *AvSQL::newSqlGenerator(QSqlQuery query)
{
    p_sqlGenerator = new QSqlGenerator(query);
    return p_sqlGenerator;
}

// get------

/**
 * @brief AvSQL::SqlGenerator - Возвращает ссылку на SqlGenerator
 * @return
 */
QSqlGenerator *AvSQL::getSqlGenerator()
{
    //if (p_sqlGenerator == NULL)
        return newSqlGenerator();
    //else
        //return p_sqlGenerator;
}

/**
 * @brief AvSQL::getQuery - Возвращает объект SqlQuery
 * @return
 */
QSqlQuery AvSQL::getQuery()
{
    return p_query;
}


/**
 * @brief AvSQL::get_type
 * @return QString
 */
QString AvSQL::get_type(AvSQL_types::type_field type){
    QString res;
    switch(type)
        {
        case AvSQL_types::avVARCHAR:    return "VARCHAR"; break;
        case AvSQL_types::avTINYINT:    return "TINYINT"; break;
        case AvSQL_types::avINT:        return "INT"; break;
        case AvSQL_types::avINT64:      return "INT64"; break;
        case AvSQL_types::avINTEGER:    return "INTEGER"; break;
        case AvSQL_types::avDATE:       return "DATE"; break;
        case AvSQL_types::avDATETIME:   return "DATETIME"; break;
        case AvSQL_types::avTIMESTAMP:  return "TIMESTAMP"; break;
        case AvSQL_types::avDOUBLE:     return "DOUBLE"; break;
        case AvSQL_types::avTEXT:       return "TEXT"; break;
        case AvSQL_types::avBLOB:       return "BLOB"; break;
        case AvSQL_types::avBINARY:     return "BINARY"; break;
        default:      return "VARCHAR";
        }
    return res;
}

bool AvSQL::CreateTable(QString tName, QList<fieldTable> fields)
{
    QString tQuery = "CREATE TABLE " + tName+" (";
    fieldTable field;
    QString sql;
    foreach (field, fields) {
        sql += field.name +" "+get_type(field.type)+"("+QString::number(field.size)+")";
                if(field.NotNULL)
                    sql += " NOT NULL";
                if(field.key)
                    sql += " PRIMARY KEY";
                if(field.UNIQUE.count()>0){

                };
        sql+= ", ";
    }

    sql = sql.left(sql.length()-2);
    sql += ")";

    execQuery(tQuery+sql);
    fields.clear();
    return true;
}
