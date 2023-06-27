//
// Created by leo on 23-6-19.
//

#ifndef GRENDERER_MATHUTIL_H
#define GRENDERER_MATHUTIL_H

#include <cmath>
#include <limits>
#include <string>


#define CHECK(x) assert(x)
#define CHECK_IMPL(a, b, op) assert((a)op(b))

#define CHECK_EQ(a, b) CHECK_IMPL(a, b, ==)
#define CHECK_NE(a, b) CHECK_IMPL(a, b, !=)
#define CHECK_GT(a, b) CHECK_IMPL(a, b, >)
#define CHECK_GE(a, b) CHECK_IMPL(a, b, >=)
#define CHECK_LT(a, b) CHECK_IMPL(a, b, <)
#define CHECK_LE(a, b) CHECK_IMPL(a, b, <=)

#ifdef GRENDER_DEBUG_BUILD
#define DCHECK(x) (CHECK(x))
#define DCHECK_EQ(a, b) CHECK_EQ(a, b)
#define DCHECK_NE(a, b) CHECK_NE(a, b)
#define DCHECK_GT(a, b) CHECK_GT(a, b)
#define DCHECK_GE(a, b) CHECK_GE(a, b)
#define DCHECK_LT(a, b) CHECK_LT(a, b)
#define DCHECK_LE(a, b) CHECK_LE(a, b)

#else

#define EMPTY_CHECK \
    do {            \
    } while (false) /* swallow semicolon */

// Use an empty check (rather than expanding the macros to nothing) to swallow the
// semicolon at the end, and avoid empty if-statements.
#define DCHECK(x) EMPTY_CHECK

#define DCHECK_EQ(a, b) EMPTY_CHECK
#define DCHECK_NE(a, b) EMPTY_CHECK
#define DCHECK_GT(a, b) EMPTY_CHECK
#define DCHECK_GE(a, b) EMPTY_CHECK
#define DCHECK_LT(a, b) EMPTY_CHECK
#define DCHECK_LE(a, b) EMPTY_CHECK

#endif

#define Pi 3.1415926
template <typename T>
struct TupleLength { using type = float; };

template <>
struct TupleLength<double> { using type = double; };

template <typename T, typename U, typename V>
inline constexpr T Clamp(T val, U low, V high)
{
    if (val < low)
        return T(low);
    else if (val > high)
        return T(high);
    else
        return val;
}

inline float SafeASin(float x)
{
    DCHECK(x >= -1.0001 && x <= 1.0001);
    return std::asin(Clamp(x, -1, 1));
}

inline float SafeACos(float x)
{
    DCHECK(x >= -1.0001 && x <= 1.0001);
    return std::acos(Clamp(x, -1, 1));
}


/**
 * @tparam T
 * @param num
 * @return whether num is nun
 */
template<typename T>
inline bool IsNaN(T num)
{
    return std::isnan(num);
}

template<typename T>
inline T Lerp(float x, T a, T b)
{
    return (1 - x) * a + x * b;
}

template <typename T>
inline constexpr T Sqr(const T& v)
{
    return v * v;
}

/**
 * @tparam T
 * @return if T is an integral type then return a * b + c, otherwise
 */
template <typename T>
inline typename std::enable_if_t<std::is_integral_v<T>, T> FMA(T a, T b, T c)
{
    return a * b + c;
}

#endif //GRENDERER_MATHUTIL_H
