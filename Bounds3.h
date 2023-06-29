//
// Created by leo on 23-6-28.
//

#ifndef GRENDERER_BOUNDS3_H
#define GRENDERER_BOUNDS3_H

#include "Point3.h"

namespace GRender
{
    template<typename T>
    class Bounds3
    {
    public:

        Bounds3()
        {
            T min_num = std::numeric_limits<T>::min();
            T max_num = std::numeric_limits<T>::max();
            p_min = Point3<T>(min_num, min_num, min_num);
            p_max = Point3<T>(max_num, max_num, max_num);
        }

        explicit Bounds3(const Point3<T>& p) : p_min(p), p_max(p) {}
        explicit Bounds3(const Point3<T>& p1, const Point3<T>& p2) : p_min(Min(p1, p2)), p_max(Max(p1, p2)) {}

        Point3<T> operator[](int i) const
        {
            return (i == 0) ? p_min : p_max;
        }

        Point3<T>& operator[](int i)
        {
            return (i == 0) ? p_min : p_max;
        }

        template<typename U>
        bool operator==(const Bounds3<U> &b) const
        {
            return p_min == b.p_min && p_max == b.p_max;
        }

        Vector3<T> Diagonal() const {return p_max - p_min;}

        T SurfaceArea() const
        {
            Vector3<T> d = Diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }

        T Volume() const
        {
            Vector3<T> d = Diagonal();
            return d.x * d.y * d.z;
        }

        int MaxDimension() const
        {
            Vector3<T> d = Diagonal();
            if (d.x > d.y && d.x > d.z)
            {
                return 0;
            }
            else if(d.y > d.z)
            {
                return 1;
            }
            else
            {
                return 2;
            }

        }

        Point3f Lerp(Point3f t) const
        {
            return {
                    ::Lerp(t.x, p_min.x, p_max.x),
                    ::Lerp(t.y, p_min.y, p_max.y),
                    ::Lerp(t.z, p_min.z, p_max.z)
            };
        }

        Vector3f Offset(Point3f p) const
        {
            Vector3f offset = p - p_min;
            if (p_max.x > p_min.x)
            {
                offset.x /= p_max.x - p_min.x;
            }
            if (p_max.y > p_min.y)
            {
                offset.y /= p_max.y - p_min.y;
            }
            if (p_max.z > p_min.z)
            {
                offset.z /= p_max.z - p_min.z;
            }

            return offset;
        }

        void BoundingSphere(Point3<T> *center, float * radius)
        {
            *center = (p_min + p_max) / 2;
            *radius = Distance(*center, p_max);
        }

        bool IsEmpty() const
        {
            return p_min.x >= p_max.x|| p_min.y >= p_max.y || p_min.z >= p_max.z;
        }

        bool IsDegenerate() const
        {
            return p_min.x > p_max.x || p_min.y > p_max.y || p_min.z > p_max.z;
        }


        // ?
//        Point3<T> Corner(int corner) const
//        {
//            return Point3<T>((*this)[(corner & 1)].x,
//                             (*this)[(corner & 2) ? 1 : 0].y,
//                             (*this)[(corner & 4) ? 1 : 0].z);
//        }

        Point3<T> p_min;
        Point3<T> p_max;
    };

    using Bounds3i = Bounds3<int>;
    using Bounds3f = Bounds3<float>;


    template<typename T>
    inline Bounds3<T> Union(const Bounds3<T> &b, const Point3<T>& p)
    {
        Bounds3<T> ret;
        ret.p_min = Min(b.p_min, p);
        ret.p_max = Max(b.p_max, p);
        return ret;
    }

    template<typename T>
    inline Bounds3<T> Union(const Bounds3<T> &b1, const Bounds3<T>& b2)
    {
        Bounds3<T> ret;
        ret.p_min = Min(b1.p_min, b2.p_min);
        ret.p_max = Max(b1.p_max, b2.p_max);
        return ret;
    }

    template<typename T>
    inline Bounds3<T> Intersect(const Bounds3<T> &b1, const Bounds3<T>& b2)
    {
        Bounds3<T> ret;
        ret.p_min = Max(b1.p_min, b2.p_min);
        ret.p_max = Min(b1.p_max, b2.p_max);
        return ret;
    }

    template<typename T>
    inline bool Inside(const Bounds3<T> &b, const Point3<T>& p)
    {
        bool x = (p.x >= b.p_min.x) && (p.x <= b.p_max.x);
        bool y = (p.y >= b.p_min.y) && (p.y <= b.p_max.y);
        bool z = (p.z >= b.p_min.z) && (p.z <= b.p_max.z);
        return (x && y && z);
    }

    template<typename T>
    inline bool InsideExclusive(const Bounds3<T> &b, const Point3<T>& p)
    {
        bool x = (p.x >= b.p_min.x) && (p.x < b.p_max.x);
        bool y = (p.y >= b.p_min.y) && (p.y < b.p_max.y);
        bool z = (p.z >= b.p_min.z) && (p.z < b.p_max.z);
        return (x && y && z);
    }

    template<typename T, typename U>
    inline auto DistanceSquared(const Bounds3<T> &b, const Point3<U>& p)
    {
        using TDist = decltype(T{} - U{});
        TDist dist_x = std::max<TDist>({b.p_min.x - p.x, 0, p.x - b.p_max.x});
        TDist dist_y = std::max<TDist>({b.p_min.y - p.y, 0, p.y - b.p_max.y});
        TDist dist_z = std::max<TDist>({b.p_min.z - p.z, 0, p.z - b.p_max.z});

        return Sqr(dist_x) + Sqr(dist_y) + Sqr(dist_z);
    }

    template <typename T, typename U>
    inline auto Distance(const Bounds3<T> &b, const Point3<U>& p)
    {
        auto dist2 = DistanceSquared(b, p);
        using TDist = typename TupleLength<decltype(dist2)>::type;
        return std::sqrt(TDist(dist2));
    }


    template <typename T, typename U>
    inline Bounds3<T> Expand(const Bounds3<T> &b, U delta)
    {
        Bounds3<T> ret;
        ret.p_min = b.p_min - Vector3<T>(delta, delta, delta);
        ret.p_max = b.p_max + Vector3<T>(delta, delta, delta);
        return ret;
    }




//    template<typename T>
//    inline bool Overlaps(const Bounds3<T> &b1, const Bounds3<T>& b2)
//    {
//        Bounds3<T> ret;
//        ret.p_min = Max(b1.p_min, b2.p_min);
//        ret.p_max = Min(b1.p_max, b2.p_max);
//        return ret;
//    }


}

#endif //GRENDERER_BOUNDS3_H
