#ifndef ALPHACHANNEL_H
#define ALPHACHANNEL_H

#include "imagewidget.h"

class AlphaChannel : public ImageWidget
{
public:
    AlphaChannel();
    void paint(QImage *image, int channel, int scale);
};

#endif // ALPHACHANNEL_H
