#include "mainform.h"
#include "ui_mainform.h"
#include <QDebug>
#include <QStandardItemModel>
#include "frmsettings.h"


MainForm::MainForm(AvSQL *sql, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    setAvSQL(sql);
    //Построение интерфейса
    buildMenu();
    //frmSettings* frm = new frmSettings();
    //ui->mdiArea->addSubWindow(frm);
    //frm->show();
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

}
