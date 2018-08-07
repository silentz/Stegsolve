#ifndef RANDOMCOLORMAPIMAGEFILTER_H
#define RANDOMCOLORMAPIMAGEFILTER_H

#include "imagefilter.h"
#include <QMap>
#include <QDateTime>

class RandomColorMapImageFilter : public ImageFilter
{
public:
    RandomColorMapImageFilter(QString name = "");
    QImage filter(QImage *image);
};

#endif // RANDOMCOLORMAPIMAGEFILTER_H
