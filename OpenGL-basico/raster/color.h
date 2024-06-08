#pragma once
#include <FreeImage.h>
#include <ostream>

class color
{
    double red_, green_, blue_, alpha_;

public:
    color()
    {
        red_ = 0;
        green_ = 255;
        blue_ = 0;
        alpha_ = 255;
    }
    
    color(double red, double green, double blue, double alpha = 255)
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
    void set_alpha(double alpha);
    double get_alpha() const;
    void set_red(double red) { red_ = red; }
    void set_green(double green) { green_ = green; }
    void set_blue(double blue) { blue_ = blue; }
    double get_red() const { return red_; }
    double get_green() const { return green_; }
    double get_blue() const { return blue_; }
    color operator+= (const color &c);
    color operator/ (double f) const;

    color operator+(const color &c) const;
    color operator*(double f) const;
    friend std::ostream& operator<<(std::ostream& os, const color& c);
};
