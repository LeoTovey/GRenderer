//
// Created by leo on 23-6-19.
//

#ifndef GRENDERER_MATH_H
#define GRENDERER_MATH_H
#include <Eigen/Core>
#include <Eigen/Dense>

namespace GRENDER
{
    template<class T, int rows, int cols>
    using Matrix = Eigen::Matrix<T, rows, cols>;

    template<class T, int rows>
    using Vector = Eigen::Matrix<T, rows, 1>;

    using Vector3d = Vector<double, 3>;
    using Vector2d = Vector<double, 2>;



}

#endif //GRENDERER_MATH_H
