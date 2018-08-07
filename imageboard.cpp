#include "imageboard.h"


ImageBoard::ImageBoard(QWidget *parent) : QWidget(parent)
{
    this->to_paint = QImage();
    this->painter = new QPainter();
}


void ImageBoard::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    if (!to_paint.isNull()) {
        this->painter->begin(this);
        this->painter->setRenderHint(QPainter::Antialiasing, false);
        this->painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
        int width = this->to_paint.width();
        int height = this->to_paint.height();
        this->setFixedSize(width, height);
        this->painter->drawImage(QRect(0, 0, width, height), this->to_paint);
        this->painter->end();
    }
}


void ImageBoard::set_image(QImage image) {
    this->to_paint = image;
    this->repaint();
}
