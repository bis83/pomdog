//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_SRC_GL4_INDEXBUFFERGL4_752BED0C_BBD7_4563_B489_47AEAC302545_HPP
#define POMDOG_SRC_GL4_INDEXBUFFERGL4_752BED0C_BBD7_4563_B489_47AEAC302545_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "OpenGLPrerequisites.hpp"
#include <Pomdog/Graphics/detail/ForwardDeclarations.hpp>
#include <Pomdog/Utility/detail/Tagged.hpp>
#include <Pomdog/Utility/Optional.hpp>
#include "../RenderSystem/NativeIndexBuffer.hpp"

namespace Pomdog {
namespace Details {
namespace RenderSystem {
namespace GL4 {

using IndexBufferObjectGL4 = Tagged<GLuint, IndexBuffer>;

class IndexBufferGL4 final: public NativeIndexBuffer {
public:
	IndexBufferGL4() = delete;
	
	IndexBufferGL4(std::uint32_t sizeInBytes, BufferUsage bufferUsage);
	
	IndexBufferGL4(void const* indices, std::uint32_t sizeInBytes, BufferUsage bufferUsage);
	
	~IndexBufferGL4() override;
	
	void SetData(std::uint32_t offsetInBytes,
		void const* source, std::uint32_t sizeInBytes) override;
	
	void BindBuffer();
	
private:
	Optional<IndexBufferObjectGL4> bufferObject;
};

}// namespace GL4
}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_SRC_GL4_INDEXBUFFERGL4_752BED0C_BBD7_4563_B489_47AEAC302545_HPP)
