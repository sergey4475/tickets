#include "frmsettings.h"
#include "ui_frmsettings.h"
#include "avsettings/avsettings.h"

frmSettings::frmSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmSettings)
{
    ui->setupUi(this);
    avSettings *set = new avSettings("",this);
    QMap<QString,QVariant> params = set->loadSettings("database","db_sqlDriver"
                                                                 ",db_server"
                                                                 ",db_port"
                                                                 ",db_username"
                                                                 ",db_password"
                                                                 ",db_name"
                                                                 ",db_prefix");
    ui->db_sqlDriver->setCurrentText(params["db_sqlDriver"].toString());
    ui->db_server   ->setText(params["db_server"].toString());
    ui->db_port     ->setText(params["db_port"].toString());
    ui->db_username ->setText(params["db_username"].toString());
    ui->db_password ->setText(params["db_password"].toString());
    ui->db_name     ->setText(params["db_name"].toString());
    ui->db_prefix   ->setText(params["db_prefix"].toString());
    updateForm();
}

frmSettings::~frmSettings()
{
    delete ui;
}

void frmSettings::on_db_sqlDriver_currentIndexChanged(const QString &arg1)
{
    updateForm();
}

/**
 * @brief frmSettings::updateForm - Обновление отображения элементов формы
 */
void frmSettings::updateForm()
{
    if (ui->db_sqlDriver->currentText() == "Postgresql"){

        ui->db_name     ->setDisabled(false);
        ui->db_name     ->setTypeSelect(avSelectEdit::String);
        ui->db_server   ->setDisabled(false);
        ui->db_port     ->setDisabled(false);
        ui->db_password ->setDisabled(false);
        ui->db_username ->setDisabled(false);
        ui->db_prefix   ->setDisabled(false);

    }else if (ui->db_sqlDriver->currentText() == "SQLite"){

        ui->db_name     ->setDisabled(false);
        ui->db_name     ->setTypeSelect(avSelectEdit::OpenFileDialog);
        ui->db_name     ->setAnyFolder(true);
        ui->db_name     ->setFilterMask("*.db *.sqlite");
        ui->db_server   ->setDisabled(true);
        ui->db_port     ->setDisabled(true);
        ui->db_password ->setDisabled(true);
        ui->db_username ->setDisabled(true);
        ui->db_prefix   ->setDisabled(true);
    }

}

/**
 * @brief frmSettings::on_btnSave_clicked - Сохранить
 */
void frmSettings::on_btnSave_clicked()
{
    avSettings *set = new avSettings("",this);

    QMap<QString,QVariant> params;
    params["db_sqlDriver"]  = ui->db_sqlDriver->currentText();
    params["db_server"]     = ui->db_server->text();
    params["db_port"]       = ui->db_port->text();
    params["db_username"]   = ui->db_username->text();
    params["db_password"]   = ui->db_password->text();
    params["db_name"]       = ui->db_name->text();
    params["db_prefix"]     = ui->db_prefix->text();

    QString groupName = "database";
    set->saveSettings(groupName,params);
    emit saveAndApply();
}

/**
 * @brief frmSettings::on_btCancel_clicked - Отмена
 */
void frmSettings::on_btCancel_clicked()
{
    close();
}
