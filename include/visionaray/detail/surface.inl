// This file is distributed under the MIT license.
// See the LICENSE file for details.

#include <cstddef>
#include <utility>

#include "../math/array.h"
#include "../generic_material.h"

namespace visionaray
{

//-------------------------------------------------------------------------------------------------
// Factory function make_surface()
//

template <typename N, typename M>
VSNRAY_FUNC
inline surface<N, M> make_surface(N const& gn, N const& sn, M const& m)
{
    return { gn, sn, m };
}

template <typename N, typename C, typename M>
VSNRAY_FUNC
inline surface<N, C, M> make_surface(N const& gn, N const& sn, C const tex_color, M const& m)
{
    return { gn, sn, tex_color, m };
}


namespace simd
{

//-------------------------------------------------------------------------------------------------
// Functions to pack and unpack SIMD surfaces
//

template <typename N, typename M, typename ...Args, size_t Size>
VSNRAY_FUNC
inline auto pack(array<surface<N, M, Args...>, Size> const& surfs)
    -> decltype( make_surface(
            pack(std::declval<array<N, Size>>()),
            pack(std::declval<array<N, Size>>()),
            pack(std::declval<array<M, Size>>())
            ) )
{
    array<N, Size> geometric_normals;
    array<N, Size> shading_normals;
    array<M, Size> materials;

    for (size_t i = 0; i < Size; ++i)
    {
        geometric_normals[i] = surfs[i].geometric_normal;
        shading_normals[i]   = surfs[i].shading_normal;
        materials[i]         = surfs[i].material;
    }

    return {
        pack(geometric_normals),
        pack(shading_normals),
        pack(materials)
        };
}

template <typename N, typename C, typename M, typename ...Args, size_t Size>
VSNRAY_FUNC
inline auto pack(array<surface<N, C, M, Args...>, Size> const& surfs)
    -> decltype( make_surface(
            pack(std::declval<array<N, Size>>()),
            pack(std::declval<array<N, Size>>()),
            pack(std::declval<array<C, Size>>()),
            pack(std::declval<array<M, Size>>())
            ) )
{
    array<N, Size> geometric_normals;
    array<N, Size> shading_normals;
    array<C, Size> tex_colors;
    array<M, Size> materials;

    for (size_t i = 0; i < Size; ++i)
    {
        geometric_normals[i] = surfs[i].geometric_normal;
        shading_normals[i]   = surfs[i].shading_normal;
        tex_colors[i]        = surfs[i].tex_color;
        materials[i]         = surfs[i].material;
    }

    return {
        pack(geometric_normals),
        pack(shading_normals),
        pack(tex_colors),
        pack(materials)
        };
}

} // simd

} // visionaray
