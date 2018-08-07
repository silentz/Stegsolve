#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent): QWidget(parent)
{
    this->name = new QLabel("");
    this->board = new ImageBoard();
    this->setStyleSheet("border: 0px none; margin: 0px;");

    QGridLayout *layer = new QGridLayout();
    layer->setSpacing(0);
    layer->setMargin(0);
    layer->addWidget(this->name, 0, 0);
    layer->addWidget(this->board, 1, 0);
    this->setLayout(layer);
}


void ImageWidget::paint(QString name, const QImage &image, const double scale) {
    int new_width = static_cast<int>(image.width() * scale);
    int new_height = static_cast<int>(image.height() * scale);
    QImage result = image.scaled(new_width, new_height);

    this->name->setText(name);
    new_width = qMax(this->name->width(), new_width);
    new_height = new_height + this->name->height();
    this->setGeometry(0, 0, new_width, new_height);
    this->board->set_image(result);
}
