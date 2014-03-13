//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_TRANSFORM3D_31340FC0_165D_4776_81BB_C8245E39E098_HPP
#define POMDOG_TRANSFORM3D_31340FC0_165D_4776_81BB_C8245E39E098_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <Pomdog/Math/Vector3.hpp>

namespace Pomdog {

class Transform3D
{
public:
	Vector3 Position;
	Vector3 Rotation;///@todo Replace by Quaternion
	Vector3 Scale;

public:
	Transform3D();
};

}// namespace Pomdog

#endif // !defined(POMDOG_TRANSFORM3D_31340FC0_165D_4776_81BB_C8245E39E098_HPP)