//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_GRAPHICS_DETAIL_FORWARDDECLARATIONS_A206A078_5F16_11E3_931A_A8206655A22B_HPP
#define POMDOG_GRAPHICS_DETAIL_FORWARDDECLARATIONS_A206A078_5F16_11E3_931A_A8206655A22B_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <Pomdog/Config/FundamentalTypes.hpp>

namespace Pomdog {

// Class
class BlendDescription;
class DepthStencilDescription;
class DepthStencilOperation;
class DepthStencilState;
class GraphicsContext;
class GraphicsDevice;
class SamplerDescription;
class RasterizerDescription;
class Viewport;

// Enumerations
enum class ClearOptions: std::uint8_t;
enum class ComparisonFunction: std::uint16_t;
enum class CullMode: std::uint16_t;
enum class FillMode: std::uint16_t;
enum class StencilOperation: std::uint16_t;

}// namespace Pomdog

#endif // !defined(POMDOG_GRAPHICS_DETAIL_FORWARDDECLARATIONS_A206A078_5F16_11E3_931A_A8206655A22B_HPP)