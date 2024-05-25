#pragma once

class vector4
{
private:
    float r_, g_, b_, alpha_;
public:
    vector4(float r, float g, float b, float alpha);
    void set_r(float r);
    void set_g(float g);
    void set_b(float b);
    void set_alpha(float alpha);
    float get_r();
    float get_g();
    float get_b();
    float get_alpha();
};
