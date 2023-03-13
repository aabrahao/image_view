#include "ImageView.h"
#include <QPainter>

#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>

QImage scale(const QImage &image, QSize size, bool keepAspectioRatio = true) {
    QImage scaled;
    if (image.isNull() or size.isNull() )
        return scaled;
    if (keepAspectioRatio) {
        if (size.height() < size.width())
            scaled = image.scaledToHeight(size.height());
        else
            scaled = image.scaledToWidth(size.width());

    }
    else
        scaled = image.scaled(size);
    return scaled;
}

ImageView::ImageView(QWidget *parent) :
    QWidget(parent) {

}

void ImageView::update(const QString &filename) {
    QImage image;
    bool ok = image.load(filename);
    if (!ok)
        qDebug() << "Ops, image '"<< filename << "' not found!";
    else
        update(image);
}

void ImageView::update(const QImage &image) {
    m_image = image;
    update();
    QWidget::update();
}

void ImageView::update(QSize size) {
    if (size.isEmpty())
        size = this->size();
    m_scaled = scale(m_image, size);
    m_view.setRect((size.width() - m_scaled.width()) /2,
                   (size.height() - m_scaled.height()) / 2,
                   m_scaled.width(),
                   m_scaled.height());
}

void ImageView::resizeEvent(QResizeEvent* event) {
    update(event->size());
    QWidget::resizeEvent(event);
}

void ImageView::paintEvent(QPaintEvent *) {
    if (m_scaled.isNull())
        return;
    QPainter painter(this);
    painter.drawImage(m_view, m_scaled);
}
