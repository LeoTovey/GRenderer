//
// Created by leo on 23-6-19.
//

#ifndef GRENDERER_TUPLE2_H
#define GRENDERER_TUPLE2_H

#include "Math.h"
namespace HJK
{

}
namespace GRender
{
    template <template <typename> class Child, typename T>
    class Tuple2
    {
    public:

        Tuple2() = default;
        Tuple2(T x, T y);

    public:
        static const int m_dimension = 2;
        T x{}, y{};
    };




}

#include "Tuple2.inl"
#endif //GRENDERER_TUPLE2_H
