#pragma once
#include "color.h"
#include "point.h"

struct pixel
{
    point point;
    color color;
};

// Scene -> Objetos segun la camara -> proyeccion -> rasterizacion -> dibujamos
