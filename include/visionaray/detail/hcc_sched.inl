// This file is distributed under the MIT license.
// See the LICENSE file for details.

#include <hcc/hc.hpp>

#include <visionaray/random_generator.h>

namespace visionaray
{

namespace detail
{

template <typename Color, typename Depth>
struct hcc_rt_ref
{
    VSNRAY_GPU_FUNC
    Color* color_;
    Depth* depth_;
};


template <typename R, typename K, typename SP>
inline void hcc_sched_impl_frame(
        K             kernel,
        SP            sparams,
        vec2ui const& block_size
        )
{
    auto scissor_box   = sparams.scissor_box;
    auto rt_ref        = sparams.rt.ref();
    auto cam           = sparams.cam;
    auto width         = sparams.rt.width();
    auto height        = sparams.rt.height();
    auto sample_params = sparams.sample_params;

    hc::parallel_for_each(
            hc::extent<2>(width, height),
            [=](hc::index<2> idx) [[hc]]
            {

                auto x = idx[0];
                auto y = idx[1];

                if (x < scissor_box.x || y < scissor_box.y || x >= scissor_box.w || y >= scissor_box.h)
                {
                    return;
                }

                // TODO: support any sampler
                random_generator<typename R::scalar_type> gen;// TODO

                auto r = detail::make_primary_rays(
                        R{},
                        sample_params,
                        gen,
                        x,
                        y,
                        rt_ref.width(),
                        rt_ref.height(),
                        cam
                        );

                sample_pixel(
                        kernel,
                        sample_params,
                        r,
                        gen,
                        rt_ref,
                        x,
                        y,
                        rt_ref.width(),
                        rt_ref.height(),
                        cam
                        );
            }
            );
}

} // detail

template <typename R>
hcc_sched<R>::hcc_sched(vec2ui block_size)
    : block_size_(block_size)
{
}

template <typename R>
hcc_sched<R>::hcc_sched(unsigned block_size_x, unsigned block_size_y)
    : block_size_(block_size_x, block_size_y)
{
}

template <typename R>
template <typename K, typename SP>
void hcc_sched<R>::frame(K kernel, SP sched_params)
{
    sched_params.cam.begin_frame();

    sched_params.rt.begin_frame();

    detail::hcc_sched_impl_frame<R>(
            kernel,
            sched_params,
            block_size_,
            );

    sched_params.rt.end_frame();

    sched_params.cam.end_frame();
}

} // visionaray
