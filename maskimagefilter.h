#ifndef MASKIMAGEFILTER_H
#define MASKIMAGEFILTER_H

#include "imagefilter.h"
#include "mask.h"

class MaskImageFilter : public ImageFilter
{
private:
    Mask mask;
public:
    MaskImageFilter(QString name = "");
    MaskImageFilter(QString name, Mask mask);
    ~MaskImageFilter();
    QImage filter(QImage *image);
};

#endif // MASKIMAGEFILTER_H
