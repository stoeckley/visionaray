// This file is distributed under the MIT license.
// See the LICENSE file for details.

namespace MATH_NAMESPACE
{
namespace simd
{

//-------------------------------------------------------------------------------------------------
// float8 members
//

VSNRAY_FORCE_INLINE float8::basic_float(
        float x1,
        float x2,
        float x3,
        float x4,
        float x5,
        float x6,
        float x7,
        float x8
        )
    : value(_mm256_set_ps(x8, x7, x6, x5, x4, x3, x2, x1))
{
}

VSNRAY_FORCE_INLINE float8::basic_float(float const v[8])
    : value(_mm256_load_ps(v))
{
}

VSNRAY_FORCE_INLINE float8::basic_float(float s)
    : value(_mm256_set1_ps(s))
{
}

VSNRAY_FORCE_INLINE float8::basic_float(__m256i const& i)
    : value(_mm256_cvtepi32_ps(i))
{
}

VSNRAY_FORCE_INLINE float8::basic_float(__m256 const& v)
    : value(v)
{
}

VSNRAY_FORCE_INLINE float8::operator __m256() const
{
    return value;
}


//-------------------------------------------------------------------------------------------------
// Bitwise cast
//

inline int8 reinterpret_as_int(float8 const& a)
{
    return _mm256_castps_si256(a);
}


//-------------------------------------------------------------------------------------------------
// Static cast
//

// TODO


//-------------------------------------------------------------------------------------------------
// select intrinsic
//

VSNRAY_FORCE_INLINE float8 select(mask8 const& m, float8 const& a, float8 const& b)
{
    return _mm256_blendv_ps(b, a, m.f);
}

VSNRAY_FORCE_INLINE float8 select(mask8 const& m, float8 const& a, float b)
{
    return select(m, a, float8(b));
}

VSNRAY_FORCE_INLINE float8 select(mask8 const& m, float a, float8 const& b)
{
    return select(m, float8(a), b);
}


//-------------------------------------------------------------------------------------------------
// Load / store
//

VSNRAY_FORCE_INLINE void store(float dst[8], float8 const& v)
{
    _mm256_store_ps(dst, v);
}


//-------------------------------------------------------------------------------------------------
// Basic arithmetic
//

VSNRAY_FORCE_INLINE float8 operator-(float8 const& v)
{
    return _mm256_sub_ps(_mm256_setzero_ps(), v);
}

VSNRAY_FORCE_INLINE float8 operator+(float8 const& u, float8 const& v)
{
    return _mm256_add_ps(u, v);
}

VSNRAY_FORCE_INLINE float8 operator-(float8 const& u, float8 const& v)
{
    return _mm256_sub_ps(u, v);
}

VSNRAY_FORCE_INLINE float8 operator*(float8 const& u, float8 const& v)
{
    return _mm256_mul_ps(u, v);
}

VSNRAY_FORCE_INLINE float8 operator/(float8 const& u, float8 const& v)
{
    return _mm256_div_ps(u, v);
}


//-------------------------------------------------------------------------------------------------
// Bitwise operators
//

VSNRAY_FORCE_INLINE float8 operator&(float8 const& u, float8 const& v)
{
    return _mm256_and_ps(u, v);
}

VSNRAY_FORCE_INLINE float8 operator|(float8 const& u, float8 const& v)
{
    return _mm256_or_ps(u, v);
}

VSNRAY_FORCE_INLINE float8 operator^(float8 const& u, float8 const& v)
{
    return _mm256_xor_ps(u, v);
}


//-------------------------------------------------------------------------------------------------
// Comparisons
//

VSNRAY_FORCE_INLINE mask8 operator<(float8 const& u, float8 const& v)
{
    return _mm256_cmp_ps(u, v, _CMP_LT_OQ);
}

VSNRAY_FORCE_INLINE mask8 operator>(float8 const& u, float8 const& v)
{
    return _mm256_cmp_ps(u, v, _CMP_GT_OQ);
}

VSNRAY_FORCE_INLINE mask8 operator<=(float8 const& u, float8 const& v)
{
    return _mm256_cmp_ps(u, v, _CMP_LE_OQ);
}

VSNRAY_FORCE_INLINE mask8 operator>=(float8 const& u, float8 const& v)
{
    return _mm256_cmp_ps(u, v, _CMP_GE_OQ);
}

VSNRAY_FORCE_INLINE mask8 operator==(float8 const& u, float8 const& v)
{
    return _mm256_cmp_ps(u, v, _CMP_EQ_OQ);
}

VSNRAY_FORCE_INLINE mask8 operator!=(float8 const& u, float8 const& v)
{
    return _mm256_cmp_ps(u, v, _CMP_NEQ_OQ);
}

VSNRAY_FORCE_INLINE mask8 operator&&(float8 const& u, float8 const& v)
{
    return _mm256_and_ps(u, v);
}

VSNRAY_FORCE_INLINE mask8 operator||(float8 const& u, float8 const& v)
{
    return _mm256_or_ps(u, v);
}


//-------------------------------------------------------------------------------------------------
// Math functions
//

VSNRAY_FORCE_INLINE float8 min(float8 const& u, float8 const& v)
{
    return _mm256_min_ps(u, v);
}

VSNRAY_FORCE_INLINE float8 max(float8 const& u, float8 const& v)
{
    return _mm256_max_ps(u, v);
}

VSNRAY_FORCE_INLINE float8 saturate(float8 const& u)
{
    return _mm256_max_ps(_mm256_setzero_ps(), _mm256_min_ps(u, _mm256_set1_ps(1.0f)));
}

VSNRAY_FORCE_INLINE float8 abs(float8 const& u)
{
    return _mm256_and_ps(u, _mm256_castsi256_ps(_mm256_set1_epi32(0x7FFFFFFF)));
}

VSNRAY_FORCE_INLINE float8 ceil(float8 const& v)
{
    return _mm256_ceil_ps(v);
}

VSNRAY_FORCE_INLINE float8 floor(float8 const& v)
{
    return _mm256_floor_ps(v);
}

VSNRAY_FORCE_INLINE float8 sqrt(float8 const& v)
{
    return _mm256_sqrt_ps(v);
}

} // simd
} // MATH_NAMESPACE