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
    {
        red_ = red;
        green_ = green;
        blue_ = blue;
        alpha_ = alpha;
        if ( red < 0 ) red_ = 0;
        if ( red > 255 ) red_ = 255;
        if ( green < 0 ) green_ = 0;
        if ( green > 255 ) green_ = 255;
        if ( blue < 0 ) blue_ = 0;
        if ( blue > 255 ) blue_ = 255;
        if ( alpha < 0 ) alpha_ = 0;
        if ( alpha > 255 ) alpha_ = 255;
        
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

    color operator+(const color &c) const;
};
