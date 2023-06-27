//
// Created by leo on 23-6-19.
//

#ifndef GRENDERER_TUPLE2_H
#define GRENDERER_TUPLE2_H

#include "MathUtil.h"

namespace GRender
{
    /**
     * @tparam Child: the child template class，which can be specialized as `Vector2<U>` or `Point2<U>`
     * @tparam T: type of element，float or double
     * @brief <template <typename> class Child, typename T>， Child前面的声明符说明Child可以是一个带一个参数的模板类，这是为了
     * 重载运算符的时候，可以知道另一个子类的类型是float还是double
     */
    template <template <typename> class Child, typename T>
    class Tuple2
    {
    public:
        Tuple2() = default;
        Tuple2(T x, T y) : x(x), y(y) { DCHECK(!HasNaN());}
        bool HasNaN() const {return IsNaN(x) || IsNaN(y);}

#ifdef GRENDER_DEBUG_BUILD

    /*
     * The default versions of these are fine for release builds; for debug
     * we define them so that we can add the Assert checks.
     * 默认的拷贝构造函数是符合要求的，这里只是为了debug
     */
    explicit Tuple2(const Child<T> & c)
    {
        DCHECK(!c.HasNaN());
        x = c.x;
        y = c.y;
    }


    Child<T> &operator=(const Child<T>& c)
    {
        DCHECK(!c.HasNaN());
        x = c.x;
        y = c.y;
        return static_cast<Child<T> &>(*this);
    }
#endif

        Child<T> operator-() const {return {-x, -y};}

        template<typename U>
        auto operator+(const Child<U> &c) const -> Child<decltype(T{} + U{})>
        {
            DCHECK(!c.HasNaN());
            return {x + c.x, y + c.y};
        }

        template<typename U>
        auto operator-(const Child<U> &c) const -> Child<decltype(T{} - U{})>
        {
            DCHECK(!c.HasNaN());
            return {x - c.x, y - c.y};
        }

        template<typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})>
        {
            DCHECK(!IsNaN(s));
            return {s * x, s * y};
        }

        template<typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})>
        {
            DCHECK(d != 0 && !IsNaN(d));
            return {x / d, y / d};
        }

        template<typename U>
        bool operator==(const Child<U>& c) const
        {
            return x == c.x && y == c.y;
        }

        template<typename U>
        bool operator!=(const Child<U>& c) const
        {
            return x != c.x || y != c.y;
        }

        template<typename U>
        Child<T> &operator+=(const Child<U>& c)
        {
            DCHECK(!c.HasNaN());
            x += c.x;
            y += c.y;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        Child<T> &operator-=(const Child<U>& c)
        {
            DCHECK(!c.HasNaN());
            x -= c.x;
            y -= c.y;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        Child<T> &operator*=(U s)
        {
            DCHECK(!IsNaN(s));
            x *= s;
            y *= s;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        Child<T> &operator/=(U d)
        {
            DCHECK_NE(d, 0);
            DCHECK(!IsNaN(d));
            x /= d;
            y /= d;
            return static_cast<Child<T> &>(*this);
        }

        T operator[](int i) const
        {
            DCHECK(i >= 0 && i <= 1);
            return (i == 0) ? x : y;
        }

        T &operator[](int i)
        {
            DCHECK(i >= 0 && i <= 1);
            return (i == 0) ? x : y;
        }


        /**
         * \deprecated
         * @return
         */
        std::string ToString() const
        {
            return std::to_string(x) + " " + std::to_string(y);
        }
    public:
        static const int m_dimension = 2;
        T x{}, y{};
    };

    template<template<class> class Child, typename T, typename U>
    inline auto operator*(U s, const Tuple2<Child, T>& t) -> Child<decltype(T{} * U{})>
    {
        DCHECK(!t.HasNaN());
        return t * s;
    }

    template<template<class> class Child, typename T>
    inline Child<T> Abs(const Tuple2<Child, T>& t)
    {
        using std::abs;
        return {abs(t.x), abs(t.y)};
    }

    template<template<class> class Child, typename T>
    inline Child<T> Ceil(const Tuple2<Child, T>& t)
    {
        using std::ceil;
        return {ceil(t.x), ceil(t.y)};
    }

    template<template<class> class Child, typename T>
    inline Child<T> Floor(const Tuple2<Child, T>& t)
    {
        using std::floor;
        return {floor(t.x), floor(t.y)};
    }

    template<template<class> class Child, typename T>
    inline auto Lerp(float t, const Tuple2<Child, T>& a, const Tuple2<Child, T>& b)
    {
        return (1 - t) * a + t * b;
    }

    /**
     * \deprecated
     */
    template<template<class> class Child, typename T, typename U>
    inline Child<T> FMA(U a, const Tuple2<Child, T>& b, const Tuple2<Child, T>& c)
    {
        return a * b + c;
    }

    template<template <class> class Child, typename T>
    inline Child<T> Min(const Tuple2<Child, T>& t1, const Tuple2<Child, T>& t2)
    {
        using std::min;
        return {min(t1.x, t2.x), min(t1.y, t2.y)};
    }

    template<template <class> class Child, typename T>
    inline Child<T> Max(const Tuple2<Child, T>& t1, const Tuple2<Child, T>& t2)
    {
        using std::max;
        return {max(t1.x, t2.x), max(t1.y, t2.y)};
    }

    template<template <class> class Child, typename T>
    inline T MaxComponentValue(const Tuple2<Child, T>& t)
    {
        using std::max;
        return max(t.x, t.y);
    }

    template<template <class> class Child, typename T>
    inline T MinComponentValue(const Tuple2<Child, T>& t)
    {
        using std::min;
        return min(t.x, t.y);
    }

    template<template <class> class Child, typename T>
    inline unsigned int MaxComponentIndex(const Tuple2<Child, T>& t)
    {
        using std::max;
        return (t.x > t.y) ? 0 : 1;
    }

    template<template <class> class Child, typename T>
    inline unsigned int MinComponentIndex(const Tuple2<Child, T>& t)
    {
        using std::min;
        return (t.x < t.y) ? 0 : 1;
    }

    template<template <class> class Child, typename T>
    inline Child<T> Permute(const Tuple2<Child, T>& a, const std::array<unsigned int, 2>& perm)
    {
        return {a[perm[0]], a[perm[1]]};
    }

    template<template <class> class Child, typename T>
    inline T HProd(const Tuple2<Child, T>& a)
    {
        return a.x * a.y;
    }

}

#endif //GRENDERER_TUPLE2_H
