//
// Created by leo on 23-6-27.
//

#ifndef GRENDERER_NORMAL3_H
#define GRENDERER_NORMAL3_H
#include "Tuple3.h"
#include "Vector3.h"

namespace GRender
{
    template<typename T>
    class Normal3 : public Tuple3<Normal3, T>
    {
    public:

        using Tuple3<Normal3, T>::x;
        using Tuple3<Normal3, T>::y;
        using Tuple3<Normal3, T>::z;

        Normal3() = default;
        Normal3(T x, T y, T z) : Tuple3<GRender::Normal3, T>(x, y, z){}

        template<typename U>
        explicit Normal3(const Tuple3<Normal3, U>& v) : Tuple3<GRender::Normal3, T>(T(v.x), T(v.y), T(v.z)){}
        template <typename U>
        explicit Normal3(const Vector3<U>& v): Tuple3<GRender::Normal3, T>(T(v.x), T(v.y), T(v.z)){}
    };

    using Normal3f = Normal3<float>;

}
#endif //GRENDERER_NORMAL3_H
