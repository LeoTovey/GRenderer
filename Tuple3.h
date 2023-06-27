//
// Created by leo on 23-6-19.
//

#ifndef GRENDERER_TUPLE3_H
#define GRENDERER_TUPLE3_H

#include "MathUtil.h"

namespace GRender
{
    /**
    * @tparam Child: the child template class，which can be specialized as `Vector3<U>` or `Point3<U>`
    * @tparam T: type of element，float or double
    * @brief <template <typename> class Child, typename T>， Child前面的声明符说明Child可以是一个带一个参数的模板类，这是为了
    * 重载运算符的时候，可以知道另一个子类的类型是float还是double
    */
    template <template <typename> class Child, typename T>
    class Tuple3
    {
    public:
        Tuple3() = default;
        Tuple3(T x, T y, T z) : x(x), y(y), z(z){ DCHECK(!HasNaN());}
        bool HasNaN() const {return IsNaN(x) || IsNaN(y) || IsNaN(z);}
        Child<T> operator-() const {return {-x, -y, -z};}

#ifdef GRENDER_DEBUG_BUILD

        /*
         * The default versions of these are fine for release builds; for debug
         * we define them so that we can add the Assert checks.
         * 默认的拷贝构造函数是符合要求的，这里只是为了debug
         */
        explicit Tuple3(const Child<T> & c)
        {
            DCHECK(!c.HasNaN());
            x = c.x;
            y = c.y;
            z = c.z;
        }


        Child<T> &operator=(const Child<T>& c)
        {
            DCHECK(!c.HasNaN());
            x = c.x;
            y = c.y;
            z = c.z;
            return static_cast<Child<T> &>(*this);
        }
#endif

        template<typename U>
        auto operator+(const Child<U> &c) const -> Child<decltype(T{} + U{})>
        {
            DCHECK(!c.HasNaN());
            return {x + c.x, y + c.y, z + c.z};
        }

        template<typename U>
        auto operator-(const Child<U> &c) const -> Child<decltype(T{} - U{})>
        {
            DCHECK(!c.HasNaN());
            return {x - c.x, y - c.y, z - c.z};
        }

        template<typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})>
        {
            DCHECK(!IsNaN(s));
            return {s * x, s * y, s * z};
        }

        template<typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})>
        {
            DCHECK(d != 0 && !IsNaN(d));
            return {x / d, y / d, z / d};
        }

        template<typename U>
        bool operator==(const Child<U>& c) const
        {
            return x == c.x && y == c.y && z == c.z;
        }

        template<typename U>
        bool operator!=(const Child<U>& c) const
        {
            return x != c.x || y != c.y || z != c.z;
        }

        template<typename U>
        Child<T> &operator+=(const Child<U>& c)
        {
            DCHECK(!c.HasNaN());
            x += c.x;
            y += c.y;
            z += c.z;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        Child<T> &operator-=(const Child<U>& c)
        {
            DCHECK(!c.HasNaN());
            x -= c.x;
            y -= c.y;
            z -= c.z;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        Child<T> &operator*=(U s)
        {
            DCHECK(!IsNaN(s));
            x *= s;
            y *= s;
            z *= s;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        Child<T> &operator/=(U d)
        {
            DCHECK_NE(d, 0);
            DCHECK(!IsNaN(d));
            x /= d;
            y /= d;
            z /= d;
            return static_cast<Child<T> &>(*this);
        }

        T operator[](int i) const
        {
            DCHECK(i >= 0 && i <= 2);
            if (i == 0)
                return x;
            if (i == 1)
                return y;
            return z;
        }

        T &operator[](int i)
        {
            DCHECK(i >= 0 && i <= 2);
            if (i == 0)
                return x;
            if (i == 1)
                return y;
            return z;
        }

        /*
         *  \deprecated
         */
        std::string ToString() const
        {
            return "(" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + ")";
        }
    public:
        static const int m_dimension = 3;
        T x{}, y{}, z{};
    };


    template<template<class> class Child, typename T, typename U>
    inline auto operator*(U s, const Tuple3<Child, T>& t) -> Child<decltype(T{} * U{})>
    {
        DCHECK(!t.HasNaN());
        return t * s;
    }

    template<template<class> class Child, typename T>
    inline Child<T> Abs(const Tuple3<Child, T>& t)
    {
        using std::abs;
        return {abs(t.x), abs(t.y), abs(t.z)};
    }

    template<template<class> class Child, typename T>
    inline Child<T> Ceil(const Tuple3<Child, T>& t)
    {
        using std::ceil;
        return {ceil(t.x), ceil(t.y), ceil(t.z)};
    }

    template<template<class> class Child, typename T>
    inline Child<T> Floor(const Tuple3<Child, T>& t)
    {
        using std::floor;
        return {floor(t.x), floor(t.y), floor(t.z)};
    }

    template<template<class> class Child, typename T>
    inline auto Lerp(float t, const Tuple3<Child, T>& a, const Tuple3<Child, T>& b)
    {
        return (1 - t) * a + t * b;
    }

    /**
     * \deprecated
     */
    template<template<class> class Child, typename T, typename U>
    inline Child<T> FMA(U a, const Tuple3<Child, T>& b, const Tuple3<Child, T>& c)
    {
        return a * b + c;
    }

    template<template <class> class Child, typename T>
    inline Child<T> Min(const Tuple3<Child, T>& t1, const Tuple3<Child, T>& t2)
    {
        using std::min;
        return {min(t1.x, t2.x), min(t1.y, t2.y), min(t1.z, t2.z)};
    }

    template<template <class> class Child, typename T>
    inline Child<T> Max(const Tuple3<Child, T>& t1, const Tuple3<Child, T>& t2)
    {
        using std::max;
        return {max(t1.x, t2.x), max(t1.y, t2.y), max(t1.z, t2.z)};
    }

    template<template <class> class Child, typename T>
    inline T MaxComponentValue(const Tuple3<Child, T>& t)
    {
        using std::max;
        return max(max(t.x, t.y), t.z);
    }

    template<template <class> class Child, typename T>
    inline T MinComponentValue(const Tuple3<Child, T>& t)
    {
        using std::min;
        return min(min(t.x, t.y), t.z);
    }

    template<template <class> class Child, typename T>
    inline unsigned int MaxComponentIndex(const Tuple3<Child, T>& t)
    {
        using std::max;
        return (t.x > t.y) ? ((t.x > t.z) ? 0 : 2) : ((t.y > t.z) ? 1 : 2);
    }

    template<template <class> class Child, typename T>
    inline unsigned int MinComponentIndex(const Tuple3<Child, T>& t)
    {
        using std::min;
        return (t.x < t.y) ? ((t.x < t.z) ? 0 : 2) : ((t.y < t.z) ? 1 : 2);
    }

    template<template <class> class Child, typename T>
    inline Child<T> Permute(const Tuple3<Child, T>& a, const std::array<unsigned int, 3>& perm)
    {
        return {a[perm[0]], a[perm[1]], a[perm[2]]};
    }

    template<template <class> class Child, typename T>
    inline T HProd(const Tuple3<Child, T>& a)
    {
        return a.x * a.y * a.z;
    }
}
#endif //GRENDERER_TUPLE3_H
