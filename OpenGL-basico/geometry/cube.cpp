#include "cube.h"

std::array<square, 6> cube::get_faces() const
{
    const auto front_face = square(a_, b_, c_, d_);
    const auto back_face = square(e_, f_, g_, h_);
    const auto top_face = square(d_, c_, g_, h_);
    const auto bottom_face = square(a_, b_, f_, e_);
    const auto left_face = square(a_, d_, h_, e_);
    const auto right_face = square(b_, c_, g_, f_);

    return {front_face, back_face, top_face, bottom_face, left_face, right_face};
}
