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

private:
    Ui::frmSettings *ui;
};

#endif // FRMSETTINGS_H
