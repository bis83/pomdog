// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_RASTERIZERDESCRIPTION_AD753EE4_HPP
#define POMDOG_RASTERIZERDESCRIPTION_AD753EE4_HPP

#include "CullMode.hpp"
#include "FillMode.hpp"
#include "Pomdog/Basic/Export.hpp"
#include <cstdint>

namespace Pomdog {

struct POMDOG_EXPORT RasterizerDescription {
    std::int32_t DepthBias;
    float SlopeScaledDepthBias;
    CullMode CullMode;
    FillMode FillMode;
    bool MultisampleEnable;
    bool ScissorTestEnable;

    static RasterizerDescription CreateDefault()
    {
        return CreateCullCounterClockwise();
    }

    static RasterizerDescription CreateCullClockwise()
    {
        RasterizerDescription desc;
        desc.CullMode = CullMode::ClockwiseFace;
        desc.FillMode = FillMode::Solid;
        desc.DepthBias = 0;
        desc.SlopeScaledDepthBias = 0;
        desc.MultisampleEnable = false;
        desc.ScissorTestEnable = false;
        return desc;
    }

    static RasterizerDescription CreateCullCounterClockwise()
    {
        RasterizerDescription desc;
        desc.CullMode = CullMode::CounterClockwiseFace;
        desc.FillMode = FillMode::Solid;
        desc.DepthBias = 0;
        desc.SlopeScaledDepthBias = 0;
        desc.MultisampleEnable = false;
        desc.ScissorTestEnable = false;
        return desc;
    }

    static RasterizerDescription CreateCullNone()
    {
        RasterizerDescription desc;
        desc.CullMode = CullMode::None;
        desc.FillMode = FillMode::Solid;
        desc.DepthBias = 0;
        desc.SlopeScaledDepthBias = 0;
        desc.MultisampleEnable = false;
        desc.ScissorTestEnable = false;
        return desc;
    }
};

} // namespace Pomdog

#endif // POMDOG_RASTERIZERDESCRIPTION_AD753EE4_HPP
