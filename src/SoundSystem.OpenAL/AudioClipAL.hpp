// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_AUDIOCLIPAL_88AB8594_HPP
#define POMDOG_AUDIOCLIPAL_88AB8594_HPP

#include "PrerequisitesOpenAL.hpp"
#include "../Utility/Noncopyable.hpp"
#include "Pomdog/Utility/Optional.hpp"
#include <cstdint>
#include <cstddef>

namespace Pomdog {

enum class AudioChannels: std::uint8_t;

namespace Detail {
namespace SoundSystem {
namespace OpenAL {

class AudioClipAL final: Noncopyable {
public:
    AudioClipAL(void const* data, std::size_t size,
        int sampleRate, int bitsPerSample,
        AudioChannels channel);

    ~AudioClipAL();

    std::size_t SizeInBytes() const;

    ALuint NativeBuffer() const;

private:
    Optional<ALuint> buffer;
    std::size_t sizeInBytes;
};

} // namespace OpenAL
} // namespace SoundSystem
} // namespace Detail
} // namespace Pomdog

#endif // POMDOG_AUDIOCLIPAL_88AB8594_HPP
