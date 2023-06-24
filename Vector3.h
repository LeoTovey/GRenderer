//
// Created by LeoTovey on 2023/6/24.
//

#ifndef GRENDERER_VECTOR3_H
#define GRENDERER_VECTOR3_H

#include "Tuple3.h"

namespace GRender
{
    template<typename T>
    class Vector3 : public Tuple3<Vector3, T>
    {
    public:

        using Tuple3<Vector3, T>::x;
        using Tuple3<Vector3, T>::y;
        using Tuple3<Vector3, T>::z;

        Vector3() = default;
        Vector3(T x, T y, T z) : Tuple3<GRender::Vector3, T>(x, y, z){}
    };
}

#endif //GRENDERER_VECTOR3_H
