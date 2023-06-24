//
// Created by LeoTovey on 2023/6/24.
//

#ifndef GRENDERER_VECTOR2_H
#define GRENDERER_VECTOR2_H

#include "Tuple2.h"

namespace GRender
{
    template<typename T>
    class Vector2 : public Tuple2<Vector2, T>
    {
    public:

        using Tuple2<Vector2, T>::x;
        using Tuple2<Vector2, T>::y;

        Vector2() = default;
        Vector2(T x, T y) : Tuple2<GRender::Vector2, T>(x, y){}
    };
}
#endif //GRENDERER_VECTOR2_H
