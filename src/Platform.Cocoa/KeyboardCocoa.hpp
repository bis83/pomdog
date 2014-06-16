﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_SRC_COCOA_KEYBOARDCOCOA_E0980F30_9516_49D4_80A0_CCE22DAB9F05_HPP
#define POMDOG_SRC_COCOA_KEYBOARDCOCOA_E0980F30_9516_49D4_80A0_CCE22DAB9F05_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <Pomdog/Input/Keyboard.hpp>
#include <Pomdog/Input/KeyboardState.hpp>

namespace Pomdog {
namespace Details {
namespace Cocoa {

class KeyboardCocoa final: public Keyboard {
public:
	KeyboardCocoa();

	///@copydoc Pomdog::Mouse
	KeyboardState const& State() const override;
	
	void SetKey(Keys key, KeyState keyState);
	
private:
	KeyboardState state;
};

}// namespace Cocoa
}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_SRC_COCOA_KEYBOARDCOCOA_E0980F30_9516_49D4_80A0_CCE22DAB9F05_HPP)