#ifndef QIMAGEWIDGET_H
#define QIMAGEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMargins>

class QImageWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString noImageMessage READ noImageMessage WRITE setNoImageMessage NOTIFY noImageMessageChanged)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap NOTIFY pixmapChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(int margin READ margin WRITE setMargin NOTIFY marginChanged)
public:
    explicit QImageWidget(QWidget *parent = nullptr);
    ~QImageWidget();

private:
    QPixmap _originalImage;
    QString _noImageMessage;
    int _margin;
    QMargins _margins;
    QColor _backgroundColor;
    QRect actualImageRect();
    void updateMargins();

public:
    void setPixmap(QPixmap pixmap);
    QPixmap pixmap() {return _originalImage; }

    int margin() {return _margin;}

    void setNoImageMessage(QString message);
    QString noImageMessage() {return _noImageMessage;}

    void setBackgroundColor(QColor color);
    QColor backgroundColor(){return _backgroundColor;}

signals:
    void pixmapChanged();
    void marginChanged();
    void noImageMessageChanged();
    void backgroundColorChanged();

public slots:
    void setMargin(int value);
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // QIMAGEWIDGET_H
