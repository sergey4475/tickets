#ifndef AVMAINMENU_H
#define AVMAINMENU_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QToolButton>

class avToolButton : public QToolButton{
    Q_OBJECT

public:
    avToolButton(QWidget *parent);
    ~avToolButton();
    void setImageBtnMenu(QPixmap pixmap);
    QPixmap imageBtnMenu(){return p_imageBtnMenu;}

private:
    QPixmap p_imageBtnMenu;


protected:
    void paintEvent(QPaintEvent*);
};

///////******************************************************************
class avMainMenu : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int widthBtnMenu READ widthBtnMenu WRITE setWidthBtnMenu)
    Q_PROPERTY(int heightBtnMenu READ heightBtnMenu WRITE setHeightBtnMenu)
    Q_PROPERTY(QPixmap imageBtnMenu READ imageBtnMenu WRITE setImageBtnMenu)


public:
    avMainMenu(QWidget *parent = nullptr);

signals:

public:
    void setImageBtnMenu(QPixmap pixmap);
    void setWidthBtnMenu(int width);
    void setHeightBtnMenu(int height);

private:
    avToolButton *btnMenu;
    int widthBtnMenu(){return btnMenu->width();}

    int heightBtnMenu(){return btnMenu->height();}

    QPixmap imageBtnMenu(){return btnMenu->imageBtnMenu();}

    int p_widthBtnMenu;
    int p_heightBtnMenu;
    void collapse_menu();
    void expand_menu();
    int begin_width;
    int p_status_panel; //0 - свернута 1 - развернута


private slots:
    void on_btnMenu_clicked();

protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // AVMAINMENU_H
