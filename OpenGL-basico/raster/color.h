#pragma once
#include <FreeImage.h>

class color
{
    unsigned char red_, green_, blue_, alpha_;

public:
    color(): red_(0), green_(0), blue_(0), alpha_(0)
    {
    }

    color(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alpha = 255)
        : red_(red), green_(green), blue_(blue), alpha_(alpha)
    {
    }

    RGBQUAD to_rgb() const;
};
