#include "image.h"

image::image(const int width, const int height, std::vector<pixel>& vector): width(width), height(height),
                                                                             pixels(vector)
{
}
