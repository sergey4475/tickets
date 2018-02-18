#ifndef TICKETS_H
#define TICKETS_H

#include "tickets_global.h"
#include <avModules>
#include "avcore.h"

class TICKETSSHARED_EXPORT Tickets : public QObject
{

public:
    Tickets(AvSQL *sql);
    void setAvSQL(AvSQL *avSQL);
    bool initialize(QWidget *w);
private:
    AvSQL *p_sql;
};

#endif // TICKETS_H
