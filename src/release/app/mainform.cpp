#include "mainform.h"
#include "ui_mainform.h"
#include "frmsettings.h"
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


}

//****** Пункты меню

/**
 * @brief MainForm::on_settings_triggered - Параметры
 */
void MainForm::on_settings_triggered()
{
    frmSettings* frm = new frmSettings();
    ui->mdiArea->addSubWindow(frm);
    frm->show();
}
