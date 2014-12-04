﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "SamplerStateDirect3D11.hpp"
#include "../RenderSystem.Direct3D11/GraphicsContextDirect3D11.hpp"
#include <Pomdog/Graphics/SamplerDescription.hpp>
#include <Pomdog/Utility/Assert.hpp>
#include <array>

namespace Pomdog {
namespace Details {
namespace RenderSystem {
namespace Direct3D11 {
namespace {

static D3D11_FILTER ToFilterDirect3D11(TextureFilter textureFilter)
{
	switch (textureFilter) {
	case TextureFilter::Anisotropic:    return D3D11_FILTER_ANISOTROPIC;
	case TextureFilter::Linear:         return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	case TextureFilter::Point:          return D3D11_FILTER_MIN_MAG_MIP_POINT;
	case TextureFilter::LinearMipPoint: return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
	case TextureFilter::PointMipLinear: return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	case TextureFilter::MinLinearMagPointMipLinear: return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
	case TextureFilter::MinLinearMagPointMipPoint:  return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	case TextureFilter::MinPointMagLinearMipLinear: return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
	case TextureFilter::MinPointMagLinearMipPoint:  return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
	}
	return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
}
//-----------------------------------------------------------------------
static D3D11_TEXTURE_ADDRESS_MODE ToTextureAddressModeDirect3D11(TextureAddressMode addressMode)
{
	switch (addressMode) {
	case TextureAddressMode::Wrap: return D3D11_TEXTURE_ADDRESS_WRAP;
	case TextureAddressMode::Clamp: return D3D11_TEXTURE_ADDRESS_CLAMP;
	case TextureAddressMode::Mirror: return D3D11_TEXTURE_ADDRESS_MIRROR;
	}
	return D3D11_TEXTURE_ADDRESS_WRAP;
}

}// unnamed namespace
//-----------------------------------------------------------------------
SamplerStateDirect3D11::SamplerStateDirect3D11(ID3D11Device* nativeDevice, SamplerDescription const& description)
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = ToFilterDirect3D11(description.Filter);
	samplerDesc.AddressU = ToTextureAddressModeDirect3D11(description.AddressU);
	samplerDesc.AddressV = ToTextureAddressModeDirect3D11(description.AddressV);
	samplerDesc.AddressW = ToTextureAddressModeDirect3D11(description.AddressW);
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = description.MinMipLevel;
	samplerDesc.MaxLOD = description.MaxMipLevel;
	samplerDesc.MipLODBias = description.MipMapLevelOfDetailBias;
	samplerDesc.MaxAnisotropy = description.MaxAnisotropy;

	POMDOG_ASSERT(samplerDesc.MinLOD <= samplerDesc.MaxLOD);
	POMDOG_ASSERT(samplerDesc.MaxLOD <= D3D11_FLOAT32_MAX);

	POMDOG_ASSERT(nativeDevice);
	HRESULT hr = nativeDevice->CreateSamplerState(&samplerDesc, &nativeSamplerState);
	
	if (FAILED(hr))
	{
		///@todo throw exception
		// error, FUS RO DAH!
		//POMDOG_THROW_EXCEPTION(ExceptionCode::RenderingAPIError,
		//	"failed to create ID3D11SamplerState.");
	}
}
//-----------------------------------------------------------------------
void SamplerStateDirect3D11::Apply(NativeGraphicsContext & graphicsContext, std::uint32_t index)
{
	POMDOG_ASSERT(index < D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT);

	std::array<ID3D11SamplerState*, 1> const states = { nativeSamplerState.Get() };

	POMDOG_ASSERT(static_cast<GraphicsContextDirect3D11*>(&graphicsContext)
		== dynamic_cast<GraphicsContextDirect3D11*>(&graphicsContext));

	auto & nativeGraphicsContext = static_cast<GraphicsContextDirect3D11 &>(graphicsContext);
	auto deviceContext = nativeGraphicsContext.GetDeviceContext();

	POMDOG_ASSERT(deviceContext);
	deviceContext->PSSetSamplers(index, states.size(), states.data());
}
//-----------------------------------------------------------------------
}// namespace Direct3D11
}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog