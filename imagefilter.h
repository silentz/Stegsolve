#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <QImage>

class ImageFilter {
public:
    virtual QImage filter(QImage *image) = 0;
    virtual ~ImageFilter() {}
};

#endif // IMAGEFILTER_H
