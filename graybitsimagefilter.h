#ifndef GRAYBITSIMAGEFILTER_H
#define GRAYBITSIMAGEFILTER_H

#include "imagefilter.h"

class GrayBitsImageFilter : public ImageFilter
{
public:
    GrayBitsImageFilter();
    QImage filter(QImage *image);
};

#endif // GRAYBITSIMAGEFILTER_H
