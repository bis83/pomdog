// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_PREREQUISITESXAUDIO2_89DAE035_HPP
#define POMDOG_PREREQUISITESXAUDIO2_89DAE035_HPP

#include "Pomdog/Platform/Win32/PrerequisitesWin32.hpp"

#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#    // for Windows 8
#    include <xaudio2.h>
#else
#    // for Windows 7, Vista
#    ifndef _WIN32_DCOM
#        define _WIN32_DCOM
#    endif
#    include <XAudio2.h>
#endif

#endif // POMDOG_PREREQUISITESXAUDIO2_89DAE035_HPP
