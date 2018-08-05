#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent): QWidget(parent)
{
    this->label = new QLabel();
    this->label->setStyleSheet("background-color: white;");
    QHBoxLayout *layer = new QHBoxLayout();
    layer->addWidget(label);
    this->setLayout(layer);
}


void ImageWidget::paint(QImage *image, int channel, float scale) {
    int new_width = static_cast<int>(image->width() * scale);
    int new_height = static_cast<int>(image->height() * scale);
    qDebug() << new_width << new_height;
    QImage working = image->scaled(new_width, new_height);
    this->label->setGeometry(0, 0, new_width, new_height);
    this->setGeometry(0, 0, new_width, new_height);
    this->label->setScaledContents(true);
    this->label->setPixmap(QPixmap::fromImage(working));
}
