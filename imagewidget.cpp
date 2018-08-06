#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent): QWidget(parent)
{
    this->name = new QLabel();
    this->board = new ImageBoard();

    QVBoxLayout *layer = new QVBoxLayout();
    layer->addWidget(this->name);
    layer->addWidget(this->board);
    this->setLayout(layer);
}


void ImageWidget::paint(QString name, const QImage &image, const double scale) {
    int new_width = static_cast<int>(image.width() * scale);
    int new_height = static_cast<int>(image.height() * scale);
    QImage result = image.scaled(new_width, new_height);

    this->name->setText(name);
    this->setGeometry(0, 0, new_width, new_height);
    this->board->set_image(result);
}
