#include <avModules>
#include "tickets.h"
#include <QMessageBox>
#include "mainform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString str("db_tickets");

    QString prefix("");
    AvSQL *lSql = new AvSQL(prefix);
    qDebug() << lSql->drivers();

    lSql->set_dbName(str);
    lSql->set_dbHost("192.168.1.9");
    lSql->set_dbUserName("postgres");
    lSql->set_dbPassword("postgres");
    lSql->set_dbPort(5432);
    lSql->set_dbDriver("QPSQL");
    if (lSql->open() != true){
        QMessageBox::warning(0,QObject::tr("Ошибка подключания к базе данных"),
                               QObject::tr("Невозможно подключиться к базе данных"));
        return 0;
    }

    avUsers usr(lSql);
    usr.showLoginDlg();

    Tickets ticket(lSql);
    ticket.initialize();

    MainForm w(lSql);

    QObject::connect(&usr,SIGNAL(accepted()),&w,SLOT(show()));
    QObject::connect(&usr,SIGNAL(rejected()),&a,SLOT(closeAllWindows()));

    return a.exec();
}
