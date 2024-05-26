#pragma once

class vector4
{
private:
    float x_, y_, z_, w_;
public:
    vector4(float x, float y, float z, float w);
    float get_x() const;
    float get_y() const;
    float get_z() const;
    float get_w() const;
    void set_x(float x);
    void set_y(float y);
    void set_z(float z);
    void set_w(float w);
};
