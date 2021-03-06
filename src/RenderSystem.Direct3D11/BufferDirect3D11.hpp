// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_BUFFERDIRECT3D11_58714643_HPP
#define POMDOG_BUFFERDIRECT3D11_58714643_HPP

#include "PrerequisitesDirect3D11.hpp"
#include "../RenderSystem/NativeBuffer.hpp"
#include "Pomdog/Graphics/detail/ForwardDeclarations.hpp"
#include <wrl/client.h>

namespace Pomdog {
namespace Detail {
namespace Direct3D11 {

class BufferDirect3D11 final : public NativeBuffer {
public:
    BufferDirect3D11(
        ID3D11Device* device,
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> const& deviceContext,
        std::size_t sizeInBytes,
        BufferUsage bufferUsage,
        D3D11_BIND_FLAG bindFlag);

    BufferDirect3D11(
        ID3D11Device* devuce,
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> const& deviceContext,
        void const* sourceData,
        std::size_t sizeInBytes,
        BufferUsage bufferUsage,
        D3D11_BIND_FLAG bindFlag);

    void GetData(
        std::size_t offsetInBytes,
        void* destination,
        std::size_t sizeInBytes) const override;

    void SetData(
        std::size_t offsetInBytes,
        void const* sourceData,
        std::size_t sizeInBytes) override;

    ID3D11Buffer* GetBuffer() const;

private:
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
};

} // namespace Direct3D11
} // namespace Detail
} // namespace Pomdog

#endif // POMDOG_BUFFERDIRECT3D11_58714643_HPP
