// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_ANIMATIONNODE_DEEDC3FD_AB3D_4C6B_AC05_E5E22457E878_HPP
#define POMDOG_ANIMATIONNODE_DEEDC3FD_AB3D_4C6B_AC05_E5E22457E878_HPP

#include "AnimationTimeInterval.hpp"

namespace Pomdog {
namespace Detail {
namespace Skeletal2D {

class AnimationGraphWeightCollection;

}// namespace Skeletal2D
}// namespace Detail

class Skeleton;
class SkeletonPose;

class AnimationNode {
public:
    virtual ~AnimationNode() = default;

    virtual void Calculate(AnimationTimeInterval const& time,
        Detail::Skeletal2D::AnimationGraphWeightCollection const& weights,
        Skeleton const& skeleton,
        SkeletonPose & skeletonPose) const = 0;

    virtual AnimationTimeInterval Length() const = 0;
};

}// namespace Pomdog

#endif // !defined(POMDOG_ANIMATIONNODE_DEEDC3FD_AB3D_4C6B_AC05_E5E22457E878_HPP)
