#pragma once
#include <FreeImage.h>

class color
{
    float red_, green_, blue_, alpha_;

public:
    color()
    {
        red_ = 0;
        green_ = 255;
        blue_ = 0;
        alpha_ = 255;
    }
    
    color(float red, float green, float blue, float alpha = 255)
        : red_(red), green_(green), blue_(blue), alpha_(alpha)
    {
    }

    RGBQUAD to_rgb() const;
    void set_alpha(float alpha);
    float get_alpha() const;
    void set_red(float red) { red_ = red; }
    void set_green(float green) { green_ = green; }
    void set_blue(float blue) { blue_ = blue; }
    float get_red() const { return red_; }
    float get_green() const { return green_; }
    float get_blue() const { return blue_; }

};
