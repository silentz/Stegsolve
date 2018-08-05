#include "mask.h"

Mask::Mask(uint and_mask, uint or_mask)
{
    this->and_mask = and_mask;
    this->or_mask = or_mask;
}


QRgb Mask::get_pixel(QRgb pixel) {
    int color = static_cast<int>(pixel);
    color &= this->and_mask;
    color |= this->or_mask;
    return static_cast<QRgb>(color);
}
