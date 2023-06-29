//
// Created by leo on 23-6-27.
//

#ifndef GRENDERER_POINT3_H
#define GRENDERER_POINT3_H

#include "Tuple3.h"
#include "Vector3.h"

namespace GRender
{
    template<typename T>
    class Point3 : public Tuple3<Point3, T>
    {
    public:

        using Tuple3<Point3, T>::x;
        using Tuple3<Point3, T>::y;
        using Tuple3<Point3, T>::z;

        using Tuple3<Point3, T>::HasNaN;
        using Tuple3<Point3, T>::operator+;
        using Tuple3<Point3, T>::operator+=;
        using Tuple3<Point3, T>::operator*;
        using Tuple3<Point3, T>::operator*=;


        Point3() = default;
        Point3(T x, T y, T z) : Tuple3<GRender::Point3, T>(x, y, z){}

        template<typename U>
        explicit Point3(const Tuple3<Point3, U>& v) : Tuple3<GRender::Point3, T>(T(v.x), T(v.y), T(v.z)){}
        template <typename U>
        explicit Point3(const Vector3<U>& v): Tuple3<GRender::Point3, T>(T(v.x), T(v.y), T(v.z)){}


        template <typename U>
        inline auto operator+(const Vector3<U> &v) const -> Point3<decltype(T{} + U{})>
        {
            return {x + v.x, y + v.y, z + v.z};
        }

        template <typename U>
        inline Point3<T>& operator+=(const Vector3<U> &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        template <typename U>
        inline auto operator-(const Point3<U> &p) const -> Vector3<decltype(T{} + U{})>
        {
            return {x - p.x, y - p.y, z - p.z};
        }

        template <typename U>
        inline auto operator-(const Vector3<U> &p) const -> Point3<decltype(T{} + U{})>
        {
            return {x - p.x, y - p.y, z - p.z};
        }


    };

    using Point3f = Point3<float>;
    using Point3i = Point3<int>;

    template<typename T>
    inline auto Distance(const Point3<T>& p1, const Point3<T>& p2)
    {
        return Length(p1 - p2);
    }

    template<typename T>
    inline auto DistanceSquared(const Point3<T>& p1, const Point3<T>& p2)
    {
        return LengthSquared(p1 - p2);
    }
}
#endif //GRENDERER_POINT3_H
