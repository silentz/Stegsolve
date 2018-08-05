#include "xorimagefilter.h"

XorImageFilter::XorImageFilter()
{
    // nothing
}

XorImageFilter::~XorImageFilter() {

}

QImage XorImageFilter::filter(QImage *image) {
    QImage result(image->width(), image->height(), QImage::Format_RGB32);
    for (int w = 0; w < image->width(); ++w) {
        for (int h = 0; h < image->height(); ++h) {
            QRgb pixel = image->pixel(w, h);
            pixel = ~pixel;
            result.setPixel(w, h, pixel);
        }
    }
    return result;
}
