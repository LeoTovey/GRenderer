//
// Created by LeoTovey on 2023/6/24.
//

#ifndef GRENDERER_VECTOR3_H
#define GRENDERER_VECTOR3_H

#include "Tuple3.h"

namespace GRender
{
    template<typename T>
    class Point3;
    template<typename T>
    class Normal3;

    template<typename T>
    class Vector3 : public Tuple3<Vector3, T>
    {
    public:

        using Tuple3<Vector3, T>::x;
        using Tuple3<Vector3, T>::y;
        using Tuple3<Vector3, T>::z;

        Vector3() = default;
        Vector3(T x, T y, T z) : Tuple3<GRender::Vector3, T>(x, y, z){}

        template<typename U>
        explicit Vector3(const Tuple3<Vector3, U>& v) : Tuple3<GRender::Vector3, T>(T(v.x), T(v.y), T(v.z)){}

        /**
        * \deprecated
        */
        template <typename U>
        explicit Vector3(Point3<U> p){}
        template <typename U>
        explicit Vector3(Normal3<U> n){}
    };

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;
    using Vector3i = Vector3<int>;
    using Vector3u = Vector3<unsigned int>;


    template<typename T>
    inline auto LengthSquared(const Vector3<T>& v) -> typename TupleLength<T>::type
    {
        return Sqr(v.x) + Sqr(v.y) + Sqr(v. z);
    }

    template<typename T>
    inline auto Length(const Vector3<T>& v) -> typename TupleLength<T>::type
    {
        using std::sqrt;
        return sqrt(LengthSquared(v));
    }

    template<typename T>
    inline auto Normalize(const Vector3<T>& v)
    {
        using std::sqrt;
        return v / Length(v);
    }

    template<typename T>
    inline T Dot(const Vector3<T>& v, const Vector3<T>& w)
    {
        return v.x * w.x + v.y * w.y + v.z * w.z;
    }

    template<typename T>
    inline T AbsDot(const Vector3<T>& v, const Vector3<T>& w)
    {
        return std::abs(Dot(v, w));
    }


    /**
     * /Deprecated : sin and
     */
    template<typename T>
    inline float AngleBetween(const Vector3<T>& v, const Vector3<T>& w)
    {
        if (Dot(v, w) < 0)
        {
            return Pi - 2 * SafeASin(Length(v + w) / 2);
        }else
        {
            return 2 * SafeASin(Length(w - v) / 2);
        }
    }
}

#endif //GRENDERER_VECTOR3_H
