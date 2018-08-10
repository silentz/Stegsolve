#include "stereogramsolver.h"

StereogramSolver::StereogramSolver(QImage image, QWidget *parent): QDialog(parent)
{
    this->offset = 0;
    this->image = image;
    this->screen = new ImageWidget();
    this->init_interface();
    this->paint_with_offset();
    this->setWindowTitle("Stereogram Solver");
}

QColor StereogramSolver::get_new_color(QColor a, QColor b) {
    int new_red =   a.red() ^ b.red();
    int new_green = a.green() ^ b.green();
    int new_blue =  a.blue() ^ b.blue();
    return QColor(new_red, new_green, new_blue);
}

QImage StereogramSolver::get_with_offset() {
    int width = this->image.width();
    int height = this->image.height();
    QImage result(width, height, QImage::Format_RGB32);
    for (int w = 0; w < width; ++w) {
        for (int h = 0; h < height; ++h) {
            QColor first = this->image.pixelColor(w, h);
            QColor second = this->image.pixelColor((w + this->offset) % width, h);
            result.setPixelColor(w, h, this->get_new_color(first, second));
        }
    }
    return result;
}

void StereogramSolver::paint_with_offset() {
    QImage result = this->get_with_offset();
    QString status = "Offset: " + QString::number(this->offset);
    this->screen->paint(status, result, 1.0);
}

void StereogramSolver::save_slot() {
    QString filename = QFileDialog::getSaveFileName(this, "Save", "solved.bmp");
    if (filename.length() > 0) {
        QImage result = this->get_with_offset();
        result.save(filename, "BMP", 100);
    }
}

void StereogramSolver::left_slot() {
    this->offset += 1;
    this->offset %= this->image.width();
    this->paint_with_offset();
}

void StereogramSolver::right_slot() {
    this->offset -= 1;
    if (this->offset < 0) {
        this->offset = this->image.width() - 1;
    }
    this->paint_with_offset();
}

void StereogramSolver::init_interface() {
    QPushButton *left = new QPushButton("<");
    QPushButton *right = new QPushButton(">");
    QPushButton *save = new QPushButton("Save");
    this->connect(left, SIGNAL(clicked(bool)), this, SLOT(left_slot()));
    this->connect(right, SIGNAL(clicked(bool)), this, SLOT(right_slot()));
    this->connect(save, SIGNAL(clicked(bool)), this, SLOT(save_slot()));

    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addStretch(3);
    buttons->addWidget(left);
    buttons->addSpacing(6);
    buttons->addWidget(right);
    buttons->addSpacing(6);
    buttons->addWidget(save);
    buttons->addStretch(3);

    QScrollArea *area = new QScrollArea;
    area->setWidget(this->screen);

    QVBoxLayout *layer = new QVBoxLayout();
    layer->addWidget(area);
    layer->addLayout(buttons);
    this->setLayout(layer);
}

StereogramSolver::~StereogramSolver() {

}
