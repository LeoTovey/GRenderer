//
// Created by leo on 23-6-28.
//

#ifndef GRENDERER_BOUNDS2_H
#define GRENDERER_BOUNDS2_H

#include "Point2.h"

namespace GRender
{
    template<typename T>
    class Bounds2
    {
    public:

        Bounds2()
        {
            T min_num = std::numeric_limits<T>::min();
            T max_num = std::numeric_limits<T>::max();
            p_min = Point2<T>(min_num, min_num);
            p_max = Point2<T>(max_num, max_num);
        }

        explicit Bounds2(const Point2<T>& p) : p_min(p), p_max(p) {}
        explicit Bounds2(const Point2<T>& p1, const Point2<T>& p2) : p_min(Min(p1, p2)), p_max(Max(p1, p2)) {}

        Point2<T> operator[](int i) const
        {
            return (i == 0) ? p_min : p_max;
        }

        Point2<T>& operator[](int i)
        {
            return (i == 0) ? p_min : p_max;
        }

        template<typename U>
        bool operator==(const Bounds2<U> &b) const
        {
            return p_min == b.p_min && p_max == b.p_max;
        }

        Vector2<T> Diagonal() const {return p_max - p_min;}

        T Area() const
        {
            Vector2<T> d = Diagonal();
            return d.x * d.y;
        }


        int MaxDimension() const
        {
            Vector2<T> d = Diagonal();
            if (d.x > d.y)
            {
                return 0;
            }
            else
            {
                return 1;
            }

        }

        Point2f Lerp(Point2f t) const
        {
            return {
                    ::Lerp(t.x, p_min.x, p_max.x),
                    ::Lerp(t.y, p_min.y, p_max.y)
            };
        }

        Vector2f Offset(Point2f p) const
        {
            Vector2f offset = p - p_min;
            if (p_max.x > p_min.x)
            {
                offset.x /= p_max.x - p_min.x;
            }
            if (p_max.y > p_min.y)
            {
                offset.y /= p_max.y - p_min.y;
            }

            return offset;
        }

        void BoundingSphere(Point2<T> *center, float * radius)
        {
            *center = (p_min + p_max) / 2;
            *radius = Distance(*center, p_max);
        }

        bool IsEmpty() const
        {
            return p_min.x >= p_max.x|| p_min.y >= p_max.y;
        }

        bool IsDegenerate() const
        {
            return p_min.x > p_max.x || p_min.y > p_max.y;
        }


        // ?
//        Point2<T> Corner(int corner) const
//        {
//            return Point2<T>((*this)[(corner & 1)].x,
//                             (*this)[(corner & 2) ? 1 : 0].y,
//                             (*this)[(corner & 4) ? 1 : 0].z);
//        }

        Point2<T> p_min;
        Point2<T> p_max;
    };

    using Bounds2i = Bounds2<int>;
    using Bounds2f = Bounds2<float>;


    template<typename T>
    inline Bounds2<T> Union(const Bounds2<T> &b, const Point2<T>& p)
    {
        Bounds2<T> ret;
        ret.p_min = Min(b.p_min, p);
        ret.p_max = Max(b.p_max, p);
        return ret;
    }

    template<typename T>
    inline Bounds2<T> Union(const Bounds2<T> &b1, const Bounds2<T>& b2)
    {
        Bounds2<T> ret;
        ret.p_min = Min(b1.p_min, b2.p_min);
        ret.p_max = Max(b1.p_max, b2.p_max);
        return ret;
    }

    template<typename T>
    inline Bounds2<T> Intersect(const Bounds2<T> &b1, const Bounds2<T>& b2)
    {
        Bounds2<T> ret;
        ret.p_min = Max(b1.p_min, b2.p_min);
        ret.p_max = Min(b1.p_max, b2.p_max);
        return ret;
    }

    template<typename T>
    inline bool Inside(const Bounds2<T> &b, const Point2<T>& p)
    {
        bool x = (p.x >= b.p_min.x) && (p.x <= b.p_max.x);
        bool y = (p.y >= b.p_min.y) && (p.y <= b.p_max.y);
        return (x && y);
    }

    template<typename T>
    inline bool InsideExclusive(const Bounds2<T> &b, const Point2<T>& p)
    {
        bool x = (p.x >= b.p_min.x) && (p.x < b.p_max.x);
        bool y = (p.y >= b.p_min.y) && (p.y < b.p_max.y);
        return (x && y);
    }

    template<typename T, typename U>
    inline auto DistanceSquared(const Bounds2<T> &b, const Point2<U>& p)
    {
        using TDist = decltype(T{} - U{});
        TDist dist_x = std::max<TDist>({b.p_min.x - p.x, 0, p.x - b.p_max.x});
        TDist dist_y = std::max<TDist>({b.p_min.y - p.y, 0, p.y - b.p_max.y});
        return Sqr(dist_x) + Sqr(dist_y);
    }

    template <typename T, typename U>
    inline auto Distance(const Bounds2<T> &b, const Point2<U>& p)
    {
        auto dist2 = DistanceSquared(b, p);
        using TDist = typename TupleLength<decltype(dist2)>::type;
        return std::sqrt(TDist(dist2));
    }


    template <typename T, typename U>
    inline Bounds2<T> Expand(const Bounds2<T> &b, U delta)
    {
        Bounds2<T> ret;
        ret.p_min = b.p_min - Vector2<T>(delta, delta);
        ret.p_max = b.p_max + Vector2<T>(delta, delta);
        return ret;
    }




//    template<typename T>
//    inline bool Overlaps(const Bounds2<T> &b1, const Bounds2<T>& b2)
//    {
//        Bounds2<T> ret;
//        ret.p_min = Max(b1.p_min, b2.p_min);
//        ret.p_max = Min(b1.p_max, b2.p_max);
//        return ret;
//    }


}

#endif //GRENDERER_BOUNDS2_H
