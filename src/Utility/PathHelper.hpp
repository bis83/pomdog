﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_PATHHELPER_BDBB516A_B1C9_42C1_8E30_64062CC7F84E_HPP
#define POMDOG_PATHHELPER_BDBB516A_B1C9_42C1_8E30_64062CC7F84E_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <string>

namespace Pomdog {
namespace Details {

class PathHelper {
public:
	static std::string Join(std::string const& path1, std::string const& path2);
};

}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_PATHHELPER_BDBB516A_B1C9_42C1_8E30_64062CC7F84E_HPP)
