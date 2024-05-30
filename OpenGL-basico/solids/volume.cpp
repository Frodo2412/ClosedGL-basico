#include "volume.h"

point3 volume::get_position() const
{
    return position_;
}

color volume::get_color()
{
    return color_;
}
