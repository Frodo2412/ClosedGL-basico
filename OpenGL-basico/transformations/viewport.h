#pragma once

#include "../geometry/vector4.h"
#include "../geometry/vector2.h"

class viewport 
{
    int width_;
    int height_;
    vector2* origin_;
public:
    viewport(int width, int height, vector2* origin) : width_(width), height_(height), origin_(origin){};
    //transforma las coordenadas a coordenadas normalizadas del dispositivo
    void to_NDC(vector4* vector);
    //traduce las coordenadas de la perspectiva a la de los pixeles en la imagen
    vector2* transform(vector4* vector);
};
