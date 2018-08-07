#ifndef CHANNELIMAGEFILTER_H
#define CHANNELIMAGEFILTER_H

#include "mask.h"
#include "imagefilter.h"

class ChannelImageFilter : public ImageFilter
{
private:
    Mask mask;

public:
    ChannelImageFilter(QString name = "");
    ChannelImageFilter(QString name, Mask mask);
    ~ChannelImageFilter();
    QImage filter(QImage *image);
};

#endif // CHANNELIMAGEFILTER_H
