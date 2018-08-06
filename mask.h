#ifndef MASK_H
#define MASK_H

#include <QColor>

class Mask
{
private:
    uint and_mask;
    uint or_mask;

public:
    Mask(uint and_mask, uint or_mask);
    QRgb get_pixel(QRgb pixel);

};

#endif // MASK_H
