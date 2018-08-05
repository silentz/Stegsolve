#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent): QWidget(parent)
{
    this->label = new QLabel();
    this->label->setScaledContents(true);

    QHBoxLayout *layer = new QHBoxLayout();
    layer->addWidget(label);
    this->setLayout(layer);
}


void ImageWidget::paint(const QImage &image, const double scale) {
    int new_width = static_cast<int>(image.width() * scale);
    int new_height = static_cast<int>(image.height() * scale);
    QImage result = image.scaled(new_width, new_height);

    this->label->setGeometry(0, 0, new_width, new_height);
    this->setGeometry(0, 0, new_width, new_height);
    this->label->setPixmap(QPixmap::fromImage(result));
}
