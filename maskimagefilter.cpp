#include "maskimagefilter.h"

MaskImageFilter::MaskImageFilter(QString name) : mask(0, 0)
{
    this->name = name;
}

MaskImageFilter::MaskImageFilter(QString name, Mask mask): mask(mask)
{
    this->name = name;
}

MaskImageFilter::~MaskImageFilter() {
    // empty
}


QImage MaskImageFilter::filter(QImage *image) {
    QImage result(image->width(), image->height(), QImage::Format_ARGB32);
    for (int w = 0; w < image->width(); ++w) {
        for (int h = 0; h < image->height(); ++h) {
            QRgb pixel = image->pixel(w, h);
            pixel = this->mask.get_pixel(pixel);
            result.setPixel(w, h, pixel);
        }
    }
    return result;
}
