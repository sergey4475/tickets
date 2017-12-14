#include "avmainmenu.h"
#include <QPainter>

avToolButton::avToolButton(QWidget *parent) : QToolButton(parent){

}

avToolButton::~avToolButton(){

}

void avToolButton::setImageBtnMenu(QPixmap pixmap)
{
    p_imageBtnMenu = pixmap;
    this->repaint();
}

void avToolButton::paintEvent(QPaintEvent *){
    QPainter p(this);
    //QLinearGradient gradient(0,0,height(),width());

//    gradient.setColorAt(0,QColor(50,113,176,100));
//    gradient.setColorAt(1,QColor(38,89,143,255));

    p.fillRect(rect(),Qt::black);
    //p.setBrush(gradient);
    p.drawRect(0,0,width(),height());

    this->setIcon(QIcon(imageBtnMenu()));
}

avMainMenu::avMainMenu(QWidget *parent) : QWidget(parent)
{
    setMaximumWidth(201);
    //setGeometry(0,0,201,parent->height());
    btnMenu = new avToolButton(this);
    begin_width = 201;

    setWidthBtnMenu(47);
    setHeightBtnMenu(47);

    connect(btnMenu,SIGNAL(clicked(bool)),this,SLOT(on_btnMenu_clicked()));
    expand_menu();
}

void avMainMenu::paintEvent(QPaintEvent *){
    QPainter p(this);
    QLinearGradient gradient(0,0,height(),width());

    gradient.setColorAt(0,QColor(50,113,176,100));
    gradient.setColorAt(1,QColor(38,89,143,255));

    p.fillRect(rect(),Qt::black);
    p.setBrush(gradient);
    p.drawRect(0,0,width(),height());

    //drawFrame(&p);

}

/**
 * @brief avMainMenu::setWidthBtnMenu - установка ширины кнопки меню
 * @param width - ширина кнопки в пикселях
 */
void avMainMenu::setWidthBtnMenu(int width){
    p_widthBtnMenu = width;
    btnMenu->setGeometry(btnMenu->x(),btnMenu->y(),width,heightBtnMenu());
    btnMenu->repaint();
}

/**
 * @brief avMainMenu::setHeightBtnMenu - установка высоты кнопки меню
 * @param height - высота кнопки в пикселях
 */
void avMainMenu::setHeightBtnMenu(int height){
    p_heightBtnMenu = height;
    btnMenu->setGeometry(btnMenu->x(),btnMenu->y(),widthBtnMenu(),height);
    btnMenu->repaint();
}

/**
 * @brief avMainMenu::setImageBtnMenu
 * @param pixmap
 */
void avMainMenu::setImageBtnMenu(QPixmap pixmap)
{
    btnMenu->setImageBtnMenu(pixmap);
}

void avMainMenu::collapse_menu(){
    btnMenu->setGeometry(0,0,p_widthBtnMenu,heightBtnMenu());
    btnMenu->setGeometry(0,0,47,47);
    this->setGeometry(this->x(),this->y(),p_widthBtnMenu,height());
    p_status_panel = 0;
}

void avMainMenu::expand_menu(){
    this->setGeometry(this->x(),this->y(),begin_width,height());
    //btnMenu->setGeometry(this->width()-btnMenu->width(),0,widthBtnMenu(),heightBtnMenu());
    btnMenu->setGeometry(begin_width-p_widthBtnMenu,0,47,47);
    p_status_panel = 1;
}
////SLOTS

void avMainMenu::on_btnMenu_clicked(){
    if (p_status_panel == 1)
        collapse_menu();
    else
        expand_menu();
}
