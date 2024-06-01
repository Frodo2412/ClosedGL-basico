#pragma once

#include "../raster/point.h"

class viewport
{
    int width_;
    int height_;
    vector2 origin_;

public:
    viewport(const int width, const int height, const vector2 origin) : width_(width), height_(height), origin_(origin)
    {
    }

    //traduce las coordenadas de la perspectiva a la de los pixeles en la imagen
    vector2 transform(vector2 vector) const;
};
