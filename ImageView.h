#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QObject>
#include <QWidget>
#include <QImage>

class ImageView : public QWidget {
    Q_OBJECT
public:
    ImageView(QWidget *parent = nullptr);
    void update(const QString &filename);
    void update(const QImage &image);
    void update(QSize size = QSize());
protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent *) override;
private:
    QImage m_image;
    // Cached
    QImage m_scaled;
    QRect m_view;
};

#endif // IMAGEVIEW_H
