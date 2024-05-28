#pragma once
#include <FreeImage.h>

#include "camera.h"
#include "../geometry/cube.h"
#include "../geometry/square.h"

class scene
{
    camera camera_;
    int width_ = 800;
    int heigth_ = 600;
    square square_;
    cube walls_;
public:
    scene(const square& square) : camera_({0, 0, 0}, {0, 0, 1}, {0, 1, 0}, 3.14159265f / 4, 0.1, 100), square_(square),
                                           walls_(cube(100, vector3::zero()))
    {
    }
    static RGBQUAD get_background_color();
    square get_square() const;
    cube get_cube() const;
    camera get_camera() const;
    int get_width();
    int get_heigth();
};
