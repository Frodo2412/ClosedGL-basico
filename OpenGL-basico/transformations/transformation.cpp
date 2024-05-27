#include "transformation.h"

transformation::transformation() = default;

transformation::transformation(const std::initializer_list<float> values)
{
    auto it = values.begin();
    for (auto& i : matrix_)
        for (float& j : i)
            j = *it++;
}

vector4 transformation::transform(const vector4& vector) const
{
    return vector4{
        matrix_[0][0] * vector.get_x() + matrix_[0][1] * vector.get_y() + matrix_[0][2] * vector.get_z() + matrix_[
            0][3] * vector .get_w(),
        matrix_[1][0] * vector.get_x() + matrix_[1][1] * vector.get_y() + matrix_[1][2] * vector.get_z() + matrix_[
            1][3] * vector .get_w(),
        matrix_[2][0] * vector.get_x() + matrix_[2][1] * vector.get_y() + matrix_[2][2] * vector.get_z() + matrix_[
            2][3] * vector .get_w(),
        matrix_[3][0] * vector.get_x() + matrix_[3][1] * vector.get_y() + matrix_[3][2] * vector.get_z() + matrix_[
            3][3] * vector .get_w()
    };
}

transformation* transformation::operator>>(transformation* other) 
{
    // Multiply the matrices
    transformation * result = new transformation();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                result->matrix_[i][j] += matrix_[i][k] * other->matrix_[k][j];
    return result;
}
