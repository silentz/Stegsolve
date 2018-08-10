#include "framebrowser.h"

FrameBrowser::FrameBrowser(QByteArray image, QWidget *parent): QDialog(parent)
{
    this->current_frame = 0;
    this->data = new QByteArray(image);
    QBuffer *buffer = new QBuffer(this->data);
    buffer->open(QIODevice::ReadOnly);
    this->movie = new QMovie(buffer);
    this->screen = new ImageWidget(this);
    this->init_interface();
    this->set_current_frame();
}


QImage FrameBrowser::get_current_frame() {
    this->movie->jumpToFrame(this->current_frame);
    return this->movie->currentImage();
}

void FrameBrowser::set_current_frame() {
    QImage result = this->get_current_frame();
    QString status = "Frame: " + QString::number(this->current_frame);
    this->screen->paint(status, result, 1.0);
}

void FrameBrowser::left_slot() {
    if (this->movie->frameCount() >= 2) {
        this->current_frame -= 1;
        if (this->current_frame < 0) {
            this->current_frame = this->movie->frameCount() - 1;
        }
        this->set_current_frame();
    }
}

void FrameBrowser::right_slot() {
    if (this->movie->frameCount() >= 2) {
        this->current_frame = (this->current_frame + 1) % this->movie->frameCount();
        this->set_current_frame();
    }
}

void FrameBrowser::save_slot() {
    QString filename = QFileDialog::getSaveFileName(this, "Save", "solved.bmp");
    if (filename.length() > 0) {
        QImage result = this->get_current_frame();
        result.save(filename, "BMP", 100);
    }
}

void FrameBrowser::init_interface() {
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
    this->setWindowTitle("Frame Browser");
}
