#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QWidget>

namespace Ui {
class frmSettings;
}

class frmSettings : public QWidget
{
    Q_OBJECT

public:
    explicit frmSettings(QWidget *parent = 0);
    ~frmSettings();


private slots:
    void on_db_sqlDriver_currentIndexChanged(const QString &arg1);

    void on_btnSave_clicked();

    void on_btCancel_clicked();

private:
    Ui::frmSettings *ui;
    void updateForm();

signals:
    void saveAndApply();

};


#endif // FRMSETTINGS_H
