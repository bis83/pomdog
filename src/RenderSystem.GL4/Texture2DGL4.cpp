//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "Texture2DGL4.hpp"
#include <algorithm>
#include <Pomdog/Utility/Assert.hpp>
#include <Pomdog/Graphics/SurfaceFormat.hpp>
#include "../Utility/ScopeGuard.hpp"
#include "ErrorChecker.hpp"
#include "TypesafeHelperGL4.hpp"

namespace Pomdog {
namespace Details {
namespace RenderSystem {
namespace GL4 {
//-----------------------------------------------------------------------
namespace {

static GLenum ToInternalFormatGL4(SurfaceFormat format)
{
	switch (format)
	{
	case SurfaceFormat::BlockComp1_UNorm:
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case SurfaceFormat::BlockComp2_UNorm:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case SurfaceFormat::BlockComp3_UNorm:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case SurfaceFormat::R8G8B8A8_UNorm:
	case SurfaceFormat::B8G8R8A8_UNorm:
		return GL_RGBA8;
	case SurfaceFormat::R32G32B32A32_Float:
		return GL_RGBA32F;
	case SurfaceFormat::R10G10B10A2_UNorm:
		return GL_RGB10_A2;
	case SurfaceFormat::R16G16_Float:
		return GL_RG16;
	case SurfaceFormat::R32_Float:
		return GL_R32F;
	case SurfaceFormat::A8_UNorm:
		return GL_R8;
	};
	
#ifdef _MSC_VER
	return GL_R8;// FUS RO DAH!!!
#endif
}
//-----------------------------------------------------------------------
static GLenum ToFormatComponents(SurfaceFormat format)
{
	switch (format)
	{
	case SurfaceFormat::R8G8B8A8_UNorm:
	case SurfaceFormat::R32G32B32A32_Float:
	case SurfaceFormat::R10G10B10A2_UNorm:
		return GL_RGBA;
	case SurfaceFormat::R16G16_Float:
		return GL_RG;
	case SurfaceFormat::R32_Float:
	case SurfaceFormat::A8_UNorm:
		return GL_RED;
	case SurfaceFormat::B8G8R8A8_UNorm:
		return GL_BGRA;
	case SurfaceFormat::BlockComp1_UNorm:
	case SurfaceFormat::BlockComp2_UNorm:
	case SurfaceFormat::BlockComp3_UNorm:
		return GL_RED;///@note Cannot find format
	};

#ifdef _MSC_VER
	return GL_RED;// FUS RO DAH!!!
#endif
}
//-----------------------------------------------------------------------
static GLenum ToPixelFundamentalType(SurfaceFormat format)
{
	switch (format)
	{
	case SurfaceFormat::R8G8B8A8_UNorm:
	case SurfaceFormat::B8G8R8A8_UNorm:
	case SurfaceFormat::A8_UNorm:
		return GL_UNSIGNED_BYTE;
	case SurfaceFormat::R32G32B32A32_Float:
	case SurfaceFormat::R16G16_Float:
	case SurfaceFormat::R32_Float:
		return GL_FLOAT;
		break;
	case SurfaceFormat::R10G10B10A2_UNorm:
		return GL_UNSIGNED_INT_10_10_10_2;
		break;
	case SurfaceFormat::BlockComp1_UNorm:
	case SurfaceFormat::BlockComp2_UNorm:
	case SurfaceFormat::BlockComp3_UNorm:
		return GL_UNSIGNED_BYTE;///@note Cannot find format
	};

#ifdef _MSC_VER
	return GL_UNSIGNED_BYTE;// FUS RO DAH!!!
#endif
}
//-----------------------------------------------------------------------
static std::uint16_t ToBytesPerBlock(SurfaceFormat format)
{
	switch (format)
	{
	case SurfaceFormat::A8_UNorm:
	case SurfaceFormat::BlockComp1_UNorm:
		return 8;
	case SurfaceFormat::BlockComp2_UNorm:
	case SurfaceFormat::BlockComp3_UNorm:
		return 16;
	case SurfaceFormat::R8G8B8A8_UNorm:
	case SurfaceFormat::B8G8R8A8_UNorm:
	case SurfaceFormat::R10G10B10A2_UNorm:
	case SurfaceFormat::R16G16_Float:
	case SurfaceFormat::R32_Float:
		return 32;
	case SurfaceFormat::R32G32B32A32_Float:
		return 128;
	};

#ifdef _MSC_VER
	return 8;// FUS RO DAH!!!
#endif
}
//-----------------------------------------------------------------------
template <typename T>
static GLenum ToTextureUnitIndexGL4(T index)
{
	static_assert(std::is_unsigned<T>::value, "T is unsigned type.");

	static_assert(GL_TEXTURE0  == (GL_TEXTURE0 + 0), "");
	static_assert(GL_TEXTURE1  == (GL_TEXTURE0 + 1), "");
	static_assert(GL_TEXTURE2  == (GL_TEXTURE0 + 2), "");
	static_assert(GL_TEXTURE3  == (GL_TEXTURE0 + 3), "");
	static_assert(GL_TEXTURE4  == (GL_TEXTURE0 + 4), "");
	static_assert(GL_TEXTURE5  == (GL_TEXTURE0 + 5), "");
	static_assert(GL_TEXTURE6  == (GL_TEXTURE0 + 6), "");
	static_assert(GL_TEXTURE7  == (GL_TEXTURE0 + 7), "");
	static_assert(GL_TEXTURE8  == (GL_TEXTURE0 + 8), "");
	static_assert(GL_TEXTURE9  == (GL_TEXTURE0 + 9), "");
	static_assert(GL_TEXTURE10 == (GL_TEXTURE0 + 10), "");
	static_assert(GL_TEXTURE11 == (GL_TEXTURE0 + 11), "");
	static_assert(GL_TEXTURE12 == (GL_TEXTURE0 + 12), "");
	static_assert(GL_TEXTURE13 == (GL_TEXTURE0 + 13), "");
	static_assert(GL_TEXTURE14 == (GL_TEXTURE0 + 14), "");
	static_assert(GL_TEXTURE15 == (GL_TEXTURE0 + 15), "");
	static_assert(GL_TEXTURE16 == (GL_TEXTURE0 + 16), "");
	static_assert(GL_TEXTURE17 == (GL_TEXTURE0 + 17), "");
	static_assert(GL_TEXTURE18 == (GL_TEXTURE0 + 18), "");
	static_assert(GL_TEXTURE19 == (GL_TEXTURE0 + 19), "");

	POMDOG_ASSERT(index <= 19);
	return static_cast<GLenum>(index + GL_TEXTURE0);
}
//-----------------------------------------------------------------------
static GLsizei MipmapImageDataBytes(GLsizei pixelWidth, GLsizei pixelHeight, GLsizei bytesPerBlock)
{
	return ((pixelWidth + 3)/4) * ((pixelHeight + 3)/4) * bytesPerBlock;
}
//-----------------------------------------------------------------------
static void SetPixelDataTexture2DCompressedGL4(std::uint32_t pixelWidth, std::uint32_t pixelHeight,
	std::uint32_t levelCount, SurfaceFormat format, std::uint8_t const* pixelData)
{
	POMDOG_ASSERT(format == SurfaceFormat::BlockComp1_UNorm ||
		format == SurfaceFormat::BlockComp2_UNorm ||
		format == SurfaceFormat::BlockComp3_UNorm);

	auto const internalFormat = ToInternalFormatGL4(format);
	auto const bytesPerBlock = ToBytesPerBlock(format);
	std::size_t startOffset = 0;

	POMDOG_ASSERT(pixelWidth > 0);
	POMDOG_ASSERT(pixelHeight > 0);
	
	GLsizei mipMapPixelWidth = pixelWidth;
	GLsizei mipMapPixelHeight = pixelHeight;

	POMDOG_ASSERT(levelCount >= 1);
	for (GLint mipmapLevel = 0; mipmapLevel < static_cast<GLint>(levelCount); ++mipmapLevel)
	{
		POMDOG_ASSERT(mipMapPixelWidth > 0);
		POMDOG_ASSERT(mipMapPixelHeight > 0);
	
		GLsizei const strideBytesPerMipmap = MipmapImageDataBytes(mipMapPixelWidth, mipMapPixelHeight, bytesPerBlock);

		glCompressedTexSubImage2D(GL_TEXTURE_2D, mipmapLevel, 0, 0,
			mipMapPixelWidth, mipMapPixelHeight, internalFormat, strideBytesPerMipmap,
			pixelData + startOffset);

		#ifdef DEBUG
		ErrorChecker::CheckError("glCompressedTexSubImage2D", __FILE__, __LINE__);
		#endif

		startOffset += strideBytesPerMipmap;

		mipMapPixelWidth = std::max((mipMapPixelWidth >> 1), 1);
		mipMapPixelHeight = std::max((mipMapPixelHeight >> 1), 1);
	}
}
//-----------------------------------------------------------------------
static void SetPixelDataTexture2DGL4(std::uint32_t pixelWidth, std::uint32_t pixelHeight,
	std::uint32_t levelCount, SurfaceFormat format, std::uint8_t const* pixelData)
{
	POMDOG_ASSERT(pixelWidth > 0);
	POMDOG_ASSERT(pixelHeight > 0);
	POMDOG_ASSERT(levelCount >= 1);

	auto const formatComponents = ToFormatComponents(format);
	auto const pixelFundamentalType = ToPixelFundamentalType(format);
	auto const bytesPerBlock = ToBytesPerBlock(format);
		
	GLsizei mipMapPixelWidth = pixelWidth;
	GLsizei mipMapPixelHeight = pixelHeight;
	
	std::size_t startOffset = 0;

	for (GLint mipmapLevel = 0; mipmapLevel < static_cast<GLint>(levelCount); ++mipmapLevel)
	{
		GLsizei const strideBytesPerMipmap = MipmapImageDataBytes(mipMapPixelWidth, mipMapPixelHeight, bytesPerBlock);

		glTexSubImage2D(GL_TEXTURE_2D, mipmapLevel, 0, 0,
			mipMapPixelWidth, mipMapPixelHeight, formatComponents, pixelFundamentalType,
			pixelData + startOffset);

		#ifdef DEBUG
		ErrorChecker::CheckError("glTexSubImage2D", __FILE__, __LINE__);
		#endif

		startOffset += strideBytesPerMipmap;

		mipMapPixelWidth = std::max((mipMapPixelWidth >> 1), 1);
		mipMapPixelHeight = std::max((mipMapPixelHeight >> 1), 1);
	}
}

}// unnamed namespace
//-----------------------------------------------------------------------
template<> struct TypesafeHelperGL4::OpenGLGetTraits<Texture2DObjectGL4>
{
	constexpr static GLenum bufferObjectBinding = GL_TEXTURE_BINDING_2D;
	constexpr static GLenum textureObjectTarget = GL_TEXTURE_2D;
};
//-----------------------------------------------------------------------
Texture2DGL4::Texture2DGL4(std::uint32_t pixelWidth, std::uint32_t pixelHeight,
	std::uint32_t levelCount, SurfaceFormat format)
{
	// Create Texture2D
	textureObject = ([]{
		Texture2DObjectGL4 textureObject;
		glGenTextures(1, textureObject.data());
		return std::move(textureObject);
	})();
	
	auto const oldTextureObject = TypesafeHelperGL4::Get<Texture2DObjectGL4>();
	ScopeGuard scope([&oldTextureObject]{
		TypesafeHelperGL4::BindTexture(oldTextureObject);
	});

	POMDOG_ASSERT(textureObject);
	TypesafeHelperGL4::BindTexture(*textureObject);
	
	#ifdef DEBUG
	ErrorChecker::CheckError("glBindTexture", __FILE__, __LINE__);
	#endif

	POMDOG_ASSERT(pixelWidth > 0);
	POMDOG_ASSERT(pixelHeight > 0);
	POMDOG_ASSERT(levelCount >= 1);
	
	GLsizei const mipmapLevel = (levelCount - 1);
	glTexStorage2D(GL_TEXTURE_2D, mipmapLevel, ToInternalFormatGL4(format), pixelWidth, pixelHeight);
	
	#ifdef DEBUG
	ErrorChecker::CheckError("glTexStorage2D", __FILE__, __LINE__);
	#endif
}
//-----------------------------------------------------------------------
Texture2DGL4::~Texture2DGL4()
{
	if (textureObject) {
		glDeleteTextures(1, textureObject->data());
	}
}
//-----------------------------------------------------------------------
void Texture2DGL4::SetData(std::uint32_t pixelWidth, std::uint32_t pixelHeight,
	std::uint32_t levelCount, SurfaceFormat format, void const* pixelData)
{
	POMDOG_ASSERT(pixelWidth > 0);
	POMDOG_ASSERT(pixelHeight > 0);
	POMDOG_ASSERT(levelCount >= 1);
	POMDOG_ASSERT(pixelData != nullptr);

	auto const oldTextureObject = TypesafeHelperGL4::Get<Texture2DObjectGL4>();
	ScopeGuard scope([&oldTextureObject]{
		TypesafeHelperGL4::BindTexture(oldTextureObject);
	});
	
	POMDOG_ASSERT(textureObject);
	TypesafeHelperGL4::BindTexture(*textureObject);
	
	#ifdef DEBUG
	ErrorChecker::CheckError("glBindTexture", __FILE__, __LINE__);
	#endif
	
	switch (format) {
	case SurfaceFormat::BlockComp1_UNorm:
	case SurfaceFormat::BlockComp2_UNorm:
	case SurfaceFormat::BlockComp3_UNorm:
		SetPixelDataTexture2DCompressedGL4(pixelWidth, pixelHeight, levelCount, format,
			reinterpret_cast<std::uint8_t const*>(pixelData));
		break;
	default:
		SetPixelDataTexture2DGL4(pixelWidth, pixelHeight, levelCount, format,
			reinterpret_cast<std::uint8_t const*>(pixelData));
		break;
	}
}
//-----------------------------------------------------------------------
void Texture2DGL4::Apply(std::uint32_t index)
{
	#ifdef DEBUG
	{
		static std::uint32_t const maxCombinedTextureImageUnits = ([]{
			GLint maxCombinedTextureImageUnits = 0;
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits);
			return maxCombinedTextureImageUnits;
		})();

		POMDOG_ASSERT(index < maxCombinedTextureImageUnits);
	}
	#endif

	glActiveTexture(ToTextureUnitIndexGL4(index));

	#ifdef DEBUG
	ErrorChecker::CheckError("glActiveTexture", __FILE__, __LINE__);
	#endif

	// Bind texture
	POMDOG_ASSERT(textureObject);
	glBindTexture(GL_TEXTURE_2D, textureObject->value);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBindTexture", __FILE__, __LINE__);
	#endif
}
//-----------------------------------------------------------------------
}// namespace GL4
}// namespace RenderSystem
}// namespace Details
}// namespace Pomdog
