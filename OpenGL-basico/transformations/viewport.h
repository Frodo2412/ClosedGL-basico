#pragma once

#include "../geometry/vector4.h"
#include "../geometry/vector3.h"
#include "../raster/point.h"

class viewport 
{
    int width_;
    int height_;
    point origin_;
public:
    viewport(int width, int height, point origin) : width_(width), height_(height), origin_(origin){};
    //transforma las coordenadas a coordenadas normalizadas del dispositivo
    vector3 to_NDC(vector4 vector);
    //traduce las coordenadas de la perspectiva a la de los pixeles en la imagen
    point transform(vector4  vector);
};
