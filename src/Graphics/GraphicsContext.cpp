//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include <Pomdog/Graphics/GraphicsContext.hpp>
#include <vector>
#include <utility>
#include <Pomdog/Utility/Assert.hpp>
#include <Pomdog/Utility/Exception.hpp>
#include <Pomdog/Graphics/BlendState.hpp>
#include <Pomdog/Graphics/DepthStencilState.hpp>
#include <Pomdog/Graphics/RasterizerState.hpp>
#include <Pomdog/Graphics/SamplerState.hpp>
#include <Pomdog/Graphics/VertexBufferBinding.hpp>
#include <Pomdog/Graphics/Viewport.hpp>
#include "../RenderSystem/GraphicsCapabilities.hpp"
#include "../RenderSystem/NativeGraphicsContext.hpp"
#include "../RenderSystem/NativeBlendState.hpp"
#include "../RenderSystem/NativeDepthStencilState.hpp"
#include "../RenderSystem/NativeRasterizerState.hpp"
#include "../RenderSystem/NativeSamplerState.hpp"
#include "../RenderSystem/PresentationParameters.hpp"

namespace Pomdog {

using Details::RenderSystem::NativeGraphicsContext;
using Details::RenderSystem::PresentationParameters;

//-----------------------------------------------------------------------
#if defined(POMDOG_COMPILER_CLANG)
#pragma mark -
#pragma mark GraphicsContext::Impl class
#endif
//-----------------------------------------------------------------------
class GraphicsContext::Impl final
{
public:
	Impl() = delete;
	Impl(Impl const&) = delete;
	Impl(Impl &&) = default;
	
	Impl(std::unique_ptr<NativeGraphicsContext> nativeContext, PresentationParameters const& presentationParameters);
	
	void BuildResources(std::shared_ptr<GraphicsDevice> const& graphicsDevice);
	
	///@copydoc GraphicsContext
	void SetViewport(Viewport const& viewport);
	
	///@copydoc GraphicsContext
	void SetSamplerState(std::size_t samplerSlot, std::shared_ptr<SamplerState> const& samplerState);
	
public:
	Viewport viewport;
	std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
	std::vector<std::shared_ptr<SamplerState>> samplerStates;
	std::shared_ptr<BlendState> blendState;
	std::shared_ptr<DepthStencilState> depthStencilState;
	std::shared_ptr<RasterizerState> rasterizerState;
	std::shared_ptr<InputLayout> inputLayout;
	
	std::unique_ptr<NativeGraphicsContext> nativeContext;
};
//-----------------------------------------------------------------------
GraphicsContext::Impl::Impl(std::unique_ptr<NativeGraphicsContext> nativeGraphicsContext,
	PresentationParameters const& presentationParameters)
	: nativeContext(std::move(nativeGraphicsContext))
{
	POMDOG_ASSERT(nativeContext);
	auto graphicsCapbilities = nativeContext->GetCapabilities();

	POMDOG_ASSERT(graphicsCapbilities.SamplerSlotCount > 0);
	samplerStates.resize(graphicsCapbilities.SamplerSlotCount);
	
	viewport.SetWidth(presentationParameters.BackBufferWidth);
	viewport.SetHeight(presentationParameters.BackBufferHeight);
	SetViewport(viewport);
	
	//BuildResources();
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::BuildResources(std::shared_ptr<GraphicsDevice> const& graphicsDevice)
{
	POMDOG_ASSERT(nativeContext);
	POMDOG_ASSERT(graphicsDevice);
	
//	viewport.SetWidth(presentationParameters.BackBufferWidth);
//	viewport.SetHeight(presentationParameters.BackBufferHeight);
//	SetViewport(viewport);
	
	blendState = BlendState::CreateAdditive(graphicsDevice);
	rasterizerState = RasterizerState::CreateCullCounterClockwise(graphicsDevice);
	depthStencilState = DepthStencilState::CreateReadOnlyDepth(graphicsDevice);
	
	POMDOG_ASSERT(!samplerStates.empty());
	for (std::size_t index = 0; index < samplerStates.size(); ++index) {
		samplerStates[index] = SamplerState::CreateLinearClamp(graphicsDevice);
	}

	if (blendState) {
		blendState->GetNativeBlendState()->Apply();
	}
	if (depthStencilState) {
		depthStencilState->GetNativeDepthStencilState()->Apply();
	}
	if (rasterizerState) {
		rasterizerState->GetNativeRasterizerState()->Apply();
	}
	for (std::size_t index = 0; index < samplerStates.size(); ++index) {
		if (samplerStates[index]) {
			samplerStates[index]->GetNativeSamplerState()->Apply(index);
		}
	}
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::SetViewport(Viewport const& newViewport)
{
	POMDOG_ASSERT(nativeContext);
	POMDOG_ASSERT(newViewport.GetWidth() > 0);
	POMDOG_ASSERT(newViewport.GetHeight() > 0);

	this->viewport = newViewport;
	nativeContext->SetViewport(this->viewport);
}
//-----------------------------------------------------------------------
void GraphicsContext::Impl::SetSamplerState(std::size_t samplerSlot, std::shared_ptr<SamplerState> const& newSamplerState)
{
	POMDOG_ASSERT(newSamplerState);
	POMDOG_ASSERT(!samplerStates.empty());
	POMDOG_ASSERT(samplerStates.size() > samplerSlot);
	
	if (samplerStates.size() > samplerSlot)
	{
		samplerStates[samplerSlot] = newSamplerState;
		samplerStates[samplerSlot]->GetNativeSamplerState()->Apply(samplerSlot);
	}
}
//-----------------------------------------------------------------------
#if defined(POMDOG_COMPILER_CLANG)
#pragma mark -
#pragma mark GraphicsContext class
#endif
//-----------------------------------------------------------------------
GraphicsContext::GraphicsContext(std::unique_ptr<NativeGraphicsContext> nativeContext,
	Details::RenderSystem::PresentationParameters const& presentationParameters)
	: impl(new Impl(std::move(nativeContext), presentationParameters))
{}
//-----------------------------------------------------------------------
GraphicsContext::~GraphicsContext()
{}
//-----------------------------------------------------------------------
void GraphicsContext::Clear(Color const& color)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	impl->nativeContext->Clear(color);
}
//-----------------------------------------------------------------------
void GraphicsContext::Clear(ClearOptions options, Color const& color, float depth, std::int32_t stencil)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	impl->nativeContext->Clear(options, color, depth, stencil);
}
//-----------------------------------------------------------------------
void GraphicsContext::Present()
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	impl->nativeContext->Present();
}
//-----------------------------------------------------------------------
void GraphicsContext::Draw(PrimitiveTopology primitiveTopology)
{
	POMDOG_ASSERT(impl);
	
	POMDOG_THROW_EXCEPTION(std::runtime_error,
		"Not implemented", "GraphicsContext::Draw");
}
//-----------------------------------------------------------------------
void GraphicsContext::DrawIndexed(PrimitiveTopology primitiveTopology,
	std::shared_ptr<IndexBuffer> const& indexBuffer, std::size_t indexCount)
{
	POMDOG_ASSERT(impl);
	
	POMDOG_THROW_EXCEPTION(std::runtime_error,
		"Not implemented", "GraphicsContext::DrawIndexed");
}
//-----------------------------------------------------------------------
void GraphicsContext::DrawInstanced(PrimitiveTopology primitiveTopology, std::size_t instanceCount)
{
	POMDOG_ASSERT(impl);
	
	POMDOG_THROW_EXCEPTION(std::runtime_error,
		"Not implemented", "GraphicsContext::DrawInstanced");
}
//-----------------------------------------------------------------------
void GraphicsContext::DrawIndexedInstanced(PrimitiveTopology primitiveTopology,
	std::shared_ptr<IndexBuffer> const& indexBuffer, std::size_t indexCount, std::size_t instanceCount)
{
	POMDOG_ASSERT(impl);
	
	POMDOG_THROW_EXCEPTION(std::runtime_error,
		"Not implemented", "GraphicsContext::DrawIndexedInstanced");
}
//-----------------------------------------------------------------------
Viewport const& GraphicsContext::GetViewport() const
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);

	return impl->viewport;
}
//-----------------------------------------------------------------------
void GraphicsContext::SetViewport(Viewport const& viewport)
{
	POMDOG_ASSERT(impl);
	impl->SetViewport(viewport);
}
//-----------------------------------------------------------------------
Rectangle GraphicsContext::GetScissorRectangle() const
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	return impl->nativeContext->GetScissorRectangle();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetScissorRectangle(Pomdog::Rectangle const& rectangle)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(impl->nativeContext);
	impl->nativeContext->SetScissorRectangle(rectangle);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetBlendState(std::shared_ptr<BlendState> const& blendState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(blendState);
	impl->blendState = blendState;
	impl->blendState->GetNativeBlendState()->Apply();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetDepthStencilState(std::shared_ptr<DepthStencilState> const& depthStencilState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(depthStencilState);
	impl->depthStencilState = depthStencilState;
	impl->depthStencilState->GetNativeDepthStencilState()->Apply();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetRasterizerState(std::shared_ptr<RasterizerState> const& rasterizerState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(rasterizerState);
	impl->rasterizerState = rasterizerState;
	impl->rasterizerState->GetNativeRasterizerState()->Apply();
}
//-----------------------------------------------------------------------
void GraphicsContext::SetSamplerState(std::size_t index, std::shared_ptr<SamplerState> const& samplerState)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(samplerState);
	impl->SetSamplerState(index, samplerState);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetInputLayout(std::shared_ptr<InputLayout> const& inputLayout)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(inputLayout);
	impl->inputLayout = inputLayout;
	
	///@todo Not implemented.
	//impl->nativeContext->SetInputLayout(inputLayout);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetVertexBuffer(std::shared_ptr<VertexBuffer> const& vertexBuffer)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(vertexBuffer);
	impl->vertexBuffers.clear();
	impl->vertexBuffers.push_back(vertexBuffer);
	
	///@todo Not implemented.
	//impl->nativeContext->SetVertexBuffers(impl->vertexBuffers);
}
//-----------------------------------------------------------------------
void GraphicsContext::SetVertexBuffers(std::vector<std::shared_ptr<VertexBuffer>> const& vertexBuffers)
{
	POMDOG_ASSERT(impl);
	POMDOG_ASSERT(vertexBuffers.empty());
	impl->vertexBuffers = vertexBuffers;
	
	///@todo Not implemented.
	//impl->nativeContext->SetVertexBuffers(impl->vertexBuffers);
}
//-----------------------------------------------------------------------
}// namespace Pomdog
