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


}
#endif //GRENDERER_TUPLE3_H
