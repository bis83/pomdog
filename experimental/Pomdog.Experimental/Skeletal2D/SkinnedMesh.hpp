//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_SKINNEDMESH_4A54231B_DCA1_44D0_A7E7_427681B8F4BE_HPP
#define POMDOG_SKINNEDMESH_4A54231B_DCA1_44D0_A7E7_427681B8F4BE_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "SkinnedMeshPart.hpp"
#include "Pomdog/Graphics/VertexBuffer.hpp"
#include "Pomdog/Graphics/IndexBuffer.hpp"
#include <memory>
#include <vector>

namespace Pomdog {

class SkinnedMesh {
public:
	std::shared_ptr<VertexBuffer> VertexBuffer;
	std::shared_ptr<IndexBuffer> IndexBuffer;
	std::vector<SkinnedMeshPart> MeshParts;
};

}// namespace Pomdog

#endif // !defined(POMDOG_SKINNEDMESH_4A54231B_DCA1_44D0_A7E7_427681B8F4BE_HPP)