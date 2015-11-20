// This file is distributed under the MIT license.
// See the LICENSE file for details.

#include <array>
#include <type_traits>

#if VSNRAY_SIMD_ISA >= VSNRAY_SIMD_ISA_AVX
#include "../simd/avx.h"
#endif
#include "../simd/sse.h"
#include "../simd/type_traits.h"

namespace MATH_NAMESPACE
{


//--------------------------------------------------------------------------------------------------
// vector3 members
//

template <typename T>
MATH_FUNC
inline vector<3, T>::vector(T x, T y, T z)
    : x(x)
    , y(y)
    , z(z)
{
}

template <typename T>
MATH_FUNC
inline vector<3, T>::vector(T s)
    : x(s)
    , y(s)
    , z(s)
{
}

template <typename T>
MATH_FUNC
inline vector<3, T>::vector(T const data[3])
    : x(data[0])
    , y(data[1])
    , z(data[2])
{
}

template <typename T>
template <typename U>
MATH_FUNC
inline vector<3, T>::vector(vector<2, U> const& rhs, U z)
    : x(rhs.x)
    , y(rhs.y)
    , z(z)
{
}

template <typename T>
template <typename U>
MATH_FUNC
inline vector<3, T>::vector(vector<3, U> const& rhs)
    : x(rhs.x)
    , y(rhs.y)
    , z(rhs.z)
{
}

template <typename T>
template <typename U>
MATH_FUNC
inline vector<3, T>::vector(vector<4, U> const& rhs)
    : x(rhs.x)
    , y(rhs.y)
    , z(rhs.z)
{
}

template <typename T>
template <typename U>
MATH_FUNC
inline vector<3, T>& vector<3, T>::operator=(vector<3, U> const& rhs)
{

    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;

}

template <typename T>
MATH_FUNC
inline T* vector<3, T>::data()
{
    return reinterpret_cast<T*>(this);
}

template <typename T>
MATH_FUNC
inline T const* vector<3, T>::data() const
{
    return reinterpret_cast<T const*>(this);
}

template <typename T>
MATH_FUNC
inline T& vector<3, T>::operator[](size_t i)
{
    return data()[i];
}

template <typename T>
MATH_FUNC
inline T const& vector<3, T>::operator[](size_t i) const
{
    return data()[i];
}

template <typename T>
MATH_FUNC
inline vector<2, T>& vector<3, T>::xy()
{
    return *reinterpret_cast<vector<2, T>*>( data() );
}

template <typename T>
MATH_FUNC
inline vector<2, T> const& vector<3, T>::xy() const
{
    return *reinterpret_cast<vector<2, T> const*>( data() );
}


//--------------------------------------------------------------------------------------------------
// Basic arithmetic
//

template <typename T>
MATH_FUNC
inline vector<3, T> operator-(vector<3, T> const& v)
{
    return vector<3, T>(-v.x, -v.y, -v.z);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator+(vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>(u.x + v.x, u.y + v.y, u.z + v.z);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator-(vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator*(vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>(u.x * v.x, u.y * v.y, u.z * v.z);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator/(vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>(u.x / v.x, u.y / v.y, u.z / v.z);
}


//--------------------------------------------------------------------------------------------------
// Comparisons
//

template <typename T>
MATH_FUNC
inline bool operator==(vector<3, T> const& u, vector<3, T> const& v)
{
    return u.x == v.x && u.y == v.y && u.z == v.z;
}

template <typename T>
MATH_FUNC
inline bool operator<(vector<3, T> const& u, vector<3, T> const& v)
{
    return u.x < v.x || ( (u.x == v.x && u.y < v.y) || (u.y == v.y && u.z < v.z) );
}

template <typename T>
MATH_FUNC
inline bool operator!=(vector<3, T> const& u, vector<3, T> const& v)
{
    return !(u == v);
}

template <typename T>
MATH_FUNC
inline bool operator<=(vector<3, T> const& u, vector<3, T> const& v)
{
    return !(v < u);
}

template <typename T>
MATH_FUNC
inline bool operator>(vector<3, T> const& u, vector<3, T> const& v)
{
    return v < u;
}

template <typename T>
MATH_FUNC
inline bool operator>=(vector<3, T> const& u, vector<3, T> const& v)
{
    return !(u < v);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator+(vector<3, T> const& v, T const& s)
{
    return vector<3, T>(v.x + s, v.y + s, v.z + s);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator-(vector<3, T> const& v, T const& s)
{
    return vector<3, T>(v.x - s, v.y - s, v.z - s);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator*(vector<3, T> const& v, T const& s)
{
    return vector<3, T>(v.x * s, v.y * s, v.z * s);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator/(vector<3, T> const& v, T const& s)
{
    return vector<3, T>(v.x / s, v.y / s, v.z / s);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator+(T const& s, vector<3, T> const& v)
{
    return vector<3, T>(s + v.x, s + v.y, s + v.z);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator-(T const& s, vector<3, T> const& v)
{
    return vector<3, T>(s - v.x, s - v.y, s - v.z);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator*(T const& s, vector<3, T> const& v)
{
    return vector<3, T>(s * v.x, s * v.y, s * v.z);
}

template <typename T>
MATH_FUNC
inline vector<3, T> operator/(T const& s, vector<3, T> const& v)
{
    return vector<3, T>(s / v.x, s / v.y, s / v.z);
}


//--------------------------------------------------------------------------------------------------
// Geometric functions
//

template <typename T>
MATH_FUNC
inline vector<3, T> cross(vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>
    (
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

template <typename T>
MATH_FUNC
inline T dot(vector<3, T> const& u, vector<3, T> const& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template <typename T>
MATH_FUNC
inline T norm(vector<3, T>  const& v)
{
    return sqrt( dot(v, v) );
}

template <typename T>
MATH_FUNC
inline T norm2(vector<3, T> const& v)
{
    return dot(v, v);
}

template <typename T>
MATH_FUNC
inline T length(vector<3, T> const& v)
{
    return norm(v);
}

template <typename T>
MATH_FUNC
inline vector<3, T> normalize(vector<3, T> const& v)
{
    return v * rsqrt( dot(v, v) );
}


//--------------------------------------------------------------------------------------------------
// Misc.
//

template <typename M, typename T>
MATH_FUNC
inline vector<3, T> select(M const& m, vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>(
            select(m, u.x, v.x),
            select(m, u.y, v.y),
            select(m, u.z, v.z)
            );
}

template <typename M, typename T1, typename T2>
MATH_FUNC
auto select(M const& m, vector<3, T1> const& u, vector<3, T2> const& v)
    -> vector<3, decltype(select(m, u.x, v.x))>
{
    using T3 = decltype(select(m, u.x, v.x));

    return vector<3, T3>(
            select(m, u.x, v.x),
            select(m, u.y, v.y),
            select(m, u.z, v.z)
            );
}

template <typename T>
MATH_FUNC
inline vector<3, T> min(vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>( min(u.x, v.x), min(u.y, v.y), min(u.z, v.z) );
}

template <typename T>
MATH_FUNC
inline vector<3, T> max(vector<3, T> const& u, vector<3, T> const& v)
{
    return vector<3, T>( max(u.x, v.x), max(u.y, v.y), max(u.z, v.z) );
}

template <typename T>
MATH_FUNC
inline T hadd(vector<3, T> const& u)
{
    return u.x + u.y + u.z;
}


namespace simd
{

//-------------------------------------------------------------------------------------------------
// SIMD conversions
//

// pack ---------------------------------------------------

inline vector<3, float4> pack(
        vector<3, float> const& v1,
        vector<3, float> const& v2,
        vector<3, float> const& v3,
        vector<3, float> const& v4
        )
{
    return vector<3, float4>(
        float4(v1.x, v2.x, v3.x, v4.x),
        float4(v1.y, v2.y, v3.y, v4.y),
        float4(v1.z, v2.z, v3.z, v4.z)
        );
}

#if VSNRAY_SIMD_ISA >= VSNRAY_SIMD_ISA_AVX

inline vector<3, float8> pack(
        vector<3, float> const& v1,
        vector<3, float> const& v2,
        vector<3, float> const& v3,
        vector<3, float> const& v4,
        vector<3, float> const& v5,
        vector<3, float> const& v6,
        vector<3, float> const& v7,
        vector<3, float> const& v8
        )
{
    return vector<3, float8>(
        float8(v1.x, v2.x, v3.x, v4.x, v5.x, v6.x, v7.x, v8.x),
        float8(v1.y, v2.y, v3.y, v4.y, v5.y, v6.y, v7.y, v8.y),
        float8(v1.z, v2.z, v3.z, v4.z, v5.z, v6.z, v7.z, v8.z)
        );
}

#endif

// unpack -------------------------------------------------

template <
    typename FloatT,
    typename = typename std::enable_if<is_simd_vector<FloatT>::value>::type
    >
inline std::array<vector<3, float>, num_elements<FloatT>::value> unpack(
        vector<3, FloatT> const& v
        )
{
    using float_array = typename aligned_array<FloatT>::type;

    float_array x;
    float_array y;
    float_array z;

    store(x, v.x);
    store(y, v.y);
    store(z, v.z);

    std::array<vector<3, float>, num_elements<FloatT>::value> result;

    for (int i = 0; i < num_elements<FloatT>::value; ++i)
    {
        result[i].x = x[i];
        result[i].y = y[i];
        result[i].z = z[i];
    }

    return result;
}

} // simd

} // MATH_NAMESPACE
