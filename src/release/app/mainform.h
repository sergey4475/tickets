#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "avcore.h"
#include <avModules>

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(AvSQL *sql, QWidget *parent = 0);
    ~MainForm();

    void setAvSQL(AvSQL *avSQL);

private slots:


    void on_settings_triggered();

private:
    Ui::MainForm *ui;

    AvSQL *p_sql;

    void buildMenu();

};

#endif // MAINFORM_H
