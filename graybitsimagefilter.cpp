#include "graybitsimagefilter.h"

GrayBitsImageFilter::GrayBitsImageFilter()
{

}

QImage GrayBitsImageFilter::filter(QImage *image) {
    QImage result(image->width(), image->height(), QImage::Format_RGB32);
    for (int w = 0; w < image->width(); ++w) {
        for (int h = 0; h < image->height(); ++h) {
            QRgb pixel = image->pixel(w, h);
            char r = static_cast<char>(pixel >> 16 % 256);
            char g = static_cast<char>(pixel >> 8 % 256);
            char b = static_cast<char>(pixel % 256);
            if (r == g && g == b) {
                pixel = 0xffffffff;
            } else {
                pixel = 0xff000000;
            }
            result.setPixel(w, h, pixel);
        }
    }
    return result;
}

