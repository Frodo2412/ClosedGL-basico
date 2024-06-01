#include "line3.h"

line3::line3(vector3 start, vector3 end): start_(start), end_(end)
{
}

vector3 line3::get_start() const
{
    return start_;
}

vector3 line3::get_end() const
{
    return end_;
}
