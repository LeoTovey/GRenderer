//
// Created by leo on 23-6-28.
//

#ifndef GRENDERER_POINT2_H
#define GRENDERER_POINT2_H

#include "Tuple2.h"
#include "Vector2.h"

namespace GRender
{
    template<typename T>
    class Point2 : public Tuple2<Point2, T>
    {
    public:

        using Tuple2<Point2, T>::x;
        using Tuple2<Point2, T>::y;

        using Tuple2<Point2, T>::HasNaN;
        using Tuple2<Point2, T>::operator+;
        using Tuple2<Point2, T>::operator+=;
        using Tuple2<Point2, T>::operator*;
        using Tuple2<Point2, T>::operator*=;


        Point2() = default;
        Point2(T x, T y) : Tuple2<GRender::Point2, T>(x, y){}

        template<typename U>
        explicit Point2(const Tuple2<Point2, U>& v) : Tuple2<GRender::Point2, T>(T(v.x), T(v.y)){}
        template <typename U>
        explicit Point2(const Vector2<U>& v): Tuple2<GRender::Point2, T>(T(v.x), T(v.y)){}


        template <typename U>
        inline auto operator+(const Vector2<U> &v) const -> Point2<decltype(T{} + U{})>
        {
            return {x + v.x, y + v.y};
        }

        template <typename U>
        inline Point2<T>& operator+=(const Vector2<U> &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        template <typename U>
        inline auto operator-(const Point2<U> &p) const -> Vector2<decltype(T{} + U{})>
        {
            return {x - p.x, y - p.y};
        }

        template <typename U>
        inline auto operator-(const Vector2<U> &p) const -> Point2<decltype(T{} + U{})>
        {
            return {x - p.x, y - p.y};
        }


    };

    using Point2f = Point2<float>;
    using Point2i = Point2<int>;

    template<typename T>
    inline auto Distance(const Point2<T>& p1, const Point2<T>& p2)
    {
        return Length(p1 - p2);
    }

    template<typename T>
    inline auto DistanceSquared(const Point2<T>& p1, const Point2<T>& p2)
    {
        return LengthSquared(p1 - p2);
    }
}

#endif //GRENDERER_POINT2_H
