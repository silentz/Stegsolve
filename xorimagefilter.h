#ifndef XORIMAGEFILTER_H
#define XORIMAGEFILTER_H

#include "imagefilter.h"

class XorImageFilter : public ImageFilter
{
public:
    XorImageFilter();
    ~XorImageFilter();
    QImage filter(QImage *image);
};

#endif // XORIMAGEFILTER_H
