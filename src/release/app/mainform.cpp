#include "mainform.h"
#include "ui_mainform.h"
#include <QDebug>
#include <QStandardItemModel>


MainForm::MainForm(AvSQL *sql, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    setAvSQL(sql);
    //Построение интерфейса
    buildMenu();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::setAvSQL(AvSQL *avSQL)
{
    p_sql = avSQL;
}

void MainForm::buildMenu(){
//    QSqlGenerator g = *p_sql->getSqlGenerator();
//    QString query = g.select("name")
//            .select("icon")
//            .from(p_sql->TableName("category_menu")).asString();

//    QSqlQuery q = p_sql->execQuery(query);

//    QTreeView *tr = new QTreeView();
//    QStandardItemModel model();
//    QList<QStandardItem*> lst;
//    while (q.next()){
//        QIcon i(":/main/img/"+q.value(1).toString());
// //       ui->toolBox->addItem(new QWidget,i, q.value(0).toString());
//        QStandardItem *it = new QStandardItem(q.value(0).toString());
//        it->setIcon(i);
//        lst.append(it);
//        //model.setItem(0,1,it);
//    }
//    model.appendColumn(lst);
   //tr->setModel(model);

    //ui->quickWidget->setSource(QUrl("qrc:/main.qml"));
}
