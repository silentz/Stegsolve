#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <QImage>

class ImageFilter {
protected:
    QString name;
public:
    ImageFilter(QString name = "") { this->name = name; }
    virtual QImage filter(QImage *image) = 0;
    virtual ~ImageFilter() {}
    QString get_name() { return this->name; }
};

#endif // IMAGEFILTER_H
