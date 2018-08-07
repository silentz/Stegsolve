#include "randomcolormapimagefilter.h"

RandomColorMapImageFilter::RandomColorMapImageFilter(QString name)
{
    this->name = name;
    qsrand(static_cast<uint>(QDateTime::currentSecsSinceEpoch()));
}

QImage RandomColorMapImageFilter::filter(QImage  *image) {
    QImage result(image->width(), image->height(), QImage::Format_ARGB32);
    QMap<QRgb, QRgb> colors;
    for (int w = 0; w < image->width(); ++w) {
        for (int h = 0; h < image->height(); ++h) {
            QRgb pixel = image->pixel(w, h);
            if (colors.contains(pixel)) {
                pixel = colors[pixel];
            } else {
                QRgb new_color = static_cast<QRgb>(qrand()) | 0xff000000;
                colors[pixel] = new_color;
                pixel = new_color;
            }
            result.setPixel(w, h, pixel);
        }
    }
    return result;
}
