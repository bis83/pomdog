//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_PARTICLECURVEKEY_6EBF4743_2FC9_43B9_9760_0FE25327F8F4_HPP
#define POMDOG_PARTICLECURVEKEY_6EBF4743_2FC9_43B9_9760_0FE25327F8F4_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

namespace Pomdog {
namespace Details {
namespace Particles {

template <typename T>
struct ParticleCurveKey {
	//std::uint8_t NormalizedTime;
	float TimeSeconds;
	T Value;
};

}// namespace Particles
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_PARTICLECURVEKEY_6EBF4743_2FC9_43B9_9760_0FE25327F8F4_HPP)