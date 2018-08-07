#include "channelimagefilter.h"

ChannelImageFilter::ChannelImageFilter(QString name) : mask(0, 0)
{
    this->name = name;
}

ChannelImageFilter::ChannelImageFilter(QString name, Mask mask) : mask(mask)
{
    this->name = name;
}

ChannelImageFilter::~ChannelImageFilter() {

}

QImage ChannelImageFilter::filter(QImage *image) {
    QImage result(image->width(), image->height(), QImage::Format_ARGB32);
    for (int w = 0; w < image->width(); ++w) {
        for (int h = 0; h < image->height(); ++h) {
            QRgb pixel = image->pixel(w, h);
            pixel = this->mask.get_pixel(pixel);
            if (pixel) {
                pixel = 0xffffffff;
            } else {
                pixel = 0xff000000;
            }
            result.setPixel(w, h, pixel);
        }
    }
    return result;
}
