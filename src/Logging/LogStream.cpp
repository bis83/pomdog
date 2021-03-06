// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#include "Pomdog/Logging/LogStream.hpp"
#include "Pomdog/Logging/LogChannel.hpp"
#include "Pomdog/Logging/LogEntry.hpp"
#include <utility>

namespace Pomdog {
//-----------------------------------------------------------------------
LogStream::LogStream(LogChannel & channelIn, LogLevel levelIn)
    : sourceChannel(channelIn.Name())
    , channel(channelIn)
    , level(levelIn)
{}
//-----------------------------------------------------------------------
LogStream::LogStream(LogChannel & channelIn,
    std::string const& sourceChannelIn, LogLevel levelIn)
    : sourceChannel(sourceChannelIn)
    , channel(channelIn)
    , level(levelIn)
{}
//-----------------------------------------------------------------------
LogStream::LogStream(LogStream const& other)
    : sourceChannel(other.sourceChannel)
    , channel(other.channel)
    , level(other.level)
{
    cache << other.cache.str();
}
//-----------------------------------------------------------------------
LogStream::~LogStream()
{
    auto message = cache.str();
    if (!message.empty())
    {
        channel.Log(LogEntry{std::move(message), sourceChannel, level});
    }
}
//-----------------------------------------------------------------------
void LogStream::Flush()
{
    channel.Log(LogEntry{cache.str(), sourceChannel, level});
    cache.str(std::string{});
    cache.clear();
}
//-----------------------------------------------------------------------
void LogStream::Clear()
{
    cache.str(std::string{});
    cache.clear();
}
//-----------------------------------------------------------------------
std::string LogStream::String() const
{
    return cache.str();
}
//-----------------------------------------------------------------------
} // namespace Pomdog
