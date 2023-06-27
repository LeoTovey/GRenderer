//
// Created by LeoTovey on 2023/6/24.
//

#ifndef GRENDERER_VECTOR2_H
#define GRENDERER_VECTOR2_H

#include "Tuple2.h"

namespace GRender
{
    template<typename T>
    class Point2;
    template<typename T>
    class Normal2;

    template<typename T>
    class Vector2 : public Tuple2<Vector2, T>
    {
    public:

        using Tuple2<Vector2, T>::x;
        using Tuple2<Vector2, T>::y;

        Vector2() = default;
        Vector2(T x, T y) : Tuple2<GRender::Vector2, T>(x, y){}

        template<typename U>
        explicit Vector2(const Tuple2<Vector2, U>& v) : Tuple2<GRender::Vector2, T>(T(v.x), T(v.y)){}

        /**
         * \deprecated
         */
        template <typename U>
        explicit Vector2(Point2<U> p){}
        template <typename U>
        explicit Vector2(Normal2<U> n){}
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int>;
    using Vector2u = Vector2<unsigned int>;


}
#endif //GRENDERER_VECTOR2_H
