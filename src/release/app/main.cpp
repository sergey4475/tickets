#include <avModules>
#include "tickets.h"
#include <QMessageBox>
#include "mainform.h"
#include <QApplication>
#include "avsettings/avsettings.h"
#include "frmsettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    avUsers* usr;

    avSettings *set = new avSettings("");
    QMap<QString,QVariant> params = set->loadSettings("database","db_sqlDriver"
                                                                 ",db_server"
                                                                 ",db_port"
                                                                 ",db_username"
                                                                 ",db_password"
                                                                 ",db_name"
                                                                 ",db_prefix");

    AvSQL *lSql = new AvSQL(params["db_prefix"].toString());

    lSql->set_dbName(       params["db_name"].toString());
    lSql->set_dbHost(       params["db_server"].toString());
    lSql->set_dbUserName(   params["db_username"].toString());
    lSql->set_dbPassword(   params["db_password"].toString());
    lSql->set_dbPort(       params["db_port"].toInt());
    lSql->set_dbDriver(     params["db_sqlDriver"].toString());

    if (lSql->open() != true){
        QMessageBox::warning(0,QObject::tr("Ошибка подключания к базе данных"),
                               QObject::tr("Невозможно подключиться к базе данных! "
                                           "Настройте подключение к базе и перезапустите программу"));
        frmSettings* frm = new frmSettings();
        frm->show();
        //return 0;
    }
    else
    {

        usr = new avUsers(lSql);
        usr->showLoginDlg();

        Tickets ticket(lSql);
        ticket.initialize();

    }

    MainForm w(lSql);
    QObject::connect(usr,SIGNAL(accepted()),&w,SLOT(show()));
    QObject::connect(usr,SIGNAL(rejected()),&a,SLOT(closeAllWindows()));

    return a.exec();
}

void openLoginDialog(AvSQL *sql){

}
