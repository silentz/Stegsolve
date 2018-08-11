#include "imagecombiner.h"

#include <QDebug>

ImageCombiner::ImageCombiner(QImage first, QWidget *parent) : QDialog(parent)
{
    this->operation = 0;
    this->first = first;
    this->screen = new ImageWidget(this);
    this->init_interface();
    this->load_second_image();
    this->setWindowFlags(Qt::Window);
    this->setWindowTitle("Image Combiner");
    this->update_screen();
}

QImage ImageCombiner::get_image() {
    switch (this->operation) {
        case 0: return this->image_xor();
        case 1: return this->image_or();
        case 2: return this->image_and();
        case 3: return this->image_add();
        case 4: return this->image_add_separate();
        case 5: return this->image_sub();
        case 6: return this->image_sub_separate();
        case 7: return this->image_mul();
        case 8: return this->image_mul_separate();
        case 9: return this->image_lightest();
        case 10: return this->image_darkest();
        case 11: return this->image_horizontal_interlace();
        case 12: return this->image_vertiacal_interlace();
    }
    return QImage();
}

QString ImageCombiner::get_title() {
    switch (this->operation) {
        case 0: return "Xor";
        case 1: return "Or";
        case 2: return "And";
        case 3: return "Add";
        case 4: return "Add (r,g,b separate)";
        case 5: return "Sub";
        case 6: return "Sub (r,g,b separate)";
        case 7: return "Mul";
        case 8: return "Mul (r,g,b separate)";
        case 9: return "Lightest";
        case 10: return "Darkest";
        case 11: return "Horizontal interlace";
        case 12: return "Vertical interlace";
    }
    return "";
}


void ImageCombiner::load_second_image() {
    QString filename = QFileDialog::getOpenFileName(this, "Open", ".",
                                                    "Images (*.png *.xpm *.jpg *.bmp *.gif *.jpeg *.pbm *.pgm *.ppm *.xbm)");
    if (filename.length() > 0) {
        this->second = QImage(filename);
    } else {
        this->close();
    }
}

void ImageCombiner::update_screen() {
    QImage img = this->get_image();
    QString title = this->get_title();
    this->screen->paint(title, img, 1.0);
}

void ImageCombiner::save_slot() {
    QString filename = QFileDialog::getSaveFileName(this, "Save", "solved.bmp");
    if (filename.length() > 0) {
        QImage result = this->get_image();
        result.save(filename, "BMP");
    }
}

void ImageCombiner::left_slot() {
    this->operation = this->operation - 1;
    if (this->operation < 0) {
        this->operation = 12;
    }
    this->update_screen();
}

void ImageCombiner::right_slot() {
    this->operation = (this->operation + 1) % 13;
    this->update_screen();
}

void ImageCombiner::init_interface() {
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

QRgb ImageCombiner::get_first_pixel(int x, int y)  {
    int width = this->first.width();
    int height = this->first.height();
    if (x >= width || y >= height) {
        return QRgb(0);
    } else {
        return this->first.pixel(x, y);
    }
}

QRgb ImageCombiner::get_second_pixel(int x, int y) {
    int width = this->second.width();
    int height = this->second.height();
    if (x >= width || y >= height) {
        return QRgb(0);
    } else {
        return this->second.pixel(x, y);
    }
}

// image operations

QImage ImageCombiner::image_xor() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, first ^ second);
        }
    }
    return result;
}

QImage ImageCombiner::image_and() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, first & second);
        }
    }
    return result;
}

QImage ImageCombiner::image_or() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, first | second);
        }
    }
    return result;
}

QImage ImageCombiner::image_add() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, first + second);
        }
    }
    return result;
}

QImage ImageCombiner::image_add_separate() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            uint red = (first >> 16 % 256) + (second >> 16 % 256);
            uint green = (first >> 8 % 256) + (second >> 8 % 256);
            uint blue = (first % 256) + (second % 256);
            red %= 256; green %= 256; blue %= 256;
            result.setPixel(a, b, (red << 16) + (green << 8) + blue);
        }
    }
    return result;
}


QImage ImageCombiner::image_sub() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, first - second);
        }
    }
    return result;
}

QImage ImageCombiner::image_sub_separate() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            uint red = (first >> 16 % 256) - (second >> 16 % 256);
            uint green = (first >> 8 % 256) - (second >> 8 % 256);
            uint blue = (first % 256) - (second % 256);
            red %= 256; green %= 256; blue %= 256;
            result.setPixel(a, b, (red << 16) + (green << 8) + blue);
        }
    }
    return result;
}

QImage ImageCombiner::image_mul() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, first * second);
        }
    }
    return result;
}

QImage ImageCombiner::image_mul_separate() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            uint red = (first >> 16 % 256) * (second >> 16 % 256);
            uint green = (first >> 8 % 256) * (second >> 8 % 256);
            uint blue = (first % 256) * (second % 256);
            red %= 256; green %= 256; blue %= 256;
            result.setPixel(a, b, (red << 16) + (green << 8) + blue);
        }
    }
    return result;
}

QImage ImageCombiner::image_lightest() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, qMax(first & 0xffffff, second & 0xffffff));
        }
    }
    return result;
}

QImage ImageCombiner::image_darkest() {
    int width = qMax(this->first.width(), this->second.width());
    int height = qMax(this->first.height(), this->second.height());
    QImage result(width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, b, qMin(first & 0xffffff, second & 0xffffff));
        }
    }
    return result;
}

QImage ImageCombiner::image_horizontal_interlace() {
    int width = qMin(this->first.width(), this->second.width());
    int height = qMin(this->first.height(), this->second.height());
    QImage result(width, 2 * height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(a, 2 * b, first);
            result.setPixel(a, 2 * b + 1, second);
        }
    }
    return result;
}

QImage ImageCombiner::image_vertiacal_interlace() {
    int width = qMin(this->first.width(), this->second.width());
    int height = qMin(this->first.height(), this->second.height());
    QImage result(2 * width, height, QImage::Format_RGB32);
    for (int a = 0; a < width; ++a) {
        for (int b = 0; b < height; ++b) {
            QRgb first = this->get_first_pixel(a, b);
            QRgb second = this->get_second_pixel(a, b);
            result.setPixel(2 * a, b, first);
            result.setPixel(2 * a + 1, b, second);
        }
    }
    return result;
}
