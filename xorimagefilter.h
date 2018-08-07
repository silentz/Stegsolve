#ifndef XORIMAGEFILTER_H
#define XORIMAGEFILTER_H

#include "imagefilter.h"

class XorImageFilter : public ImageFilter
{
public:
    XorImageFilter(QString name = "");
    ~XorImageFilter();
    QImage filter(QImage *image);
};

#endif // XORIMAGEFILTER_H
