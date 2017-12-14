#include "qimagewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>


QImageWidget::QImageWidget(QWidget *parent) : QWidget(parent)
{
    _noImageMessage = "NO IMAGE";
    _backgroundColor= Qt::white;
    _margin         = 4;
    connect(this,SIGNAL(marginChanged()),SLOT(repaint()));
    connect(this,SIGNAL(pixmapChanged()),SLOT(repaint()));

}

QImageWidget::~QImageWidget()
{

}

QRect QImageWidget::actualImageRect()
{
    QRect imageRect = rect();
    imageRect.setSize(_originalImage.size().scaled(size(),Qt::KeepAspectRatio));
    imageRect.moveCenter(rect().center());
    return imageRect;
}

void QImageWidget::updateMargins()
{
    double ratio = (double)_originalImage.height()/_originalImage.width();
    int hMargin = _margin * ratio;
    int vMargin = _margin;

    _margins.setBottom(hMargin);
    _margins.setTop(hMargin);
    _margins.setRight(vMargin);
    _margins.setLeft(vMargin);

}

void QImageWidget::setPixmap(QPixmap pixmap)
{
    _originalImage = pixmap;
    updateMargins();
    emit pixmapChanged();
}

void QImageWidget::setNoImageMessage(QString message)
{
    _noImageMessage = message;
    emit noImageMessageChanged();
}

void QImageWidget::setBackgroundColor(QColor color)
{
    _backgroundColor = color;
    emit backgroundColorChanged();
}

void QImageWidget::setMargin(int value)
{
    if (value < 2)
        value = 2;

    if (value > 20)
        value = 20;

    if (value != _margin){
        _margin = value;
        updateMargins();
        emit marginChanged();
    }
}

void QImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();

    painter.setBrush(_backgroundColor);
    painter.drawRect(rect());

    painter.restore();

    if (_originalImage.isNull()){
        painter.drawText(rect(),Qt::AlignCenter,_noImageMessage);
    }
    else{
        QRect imageRect = actualImageRect();
        painter.drawPixmap(imageRect.marginsRemoved(_margins),_originalImage);

    }

}

void QImageWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;
    QString filename = QFileDialog::getOpenFileName();
    if (filename.isEmpty())
        return;
    setPixmap(QPixmap(filename));
}
