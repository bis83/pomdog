// Copyright (c) 2013-2015 mogemimi.
// Distributed under the MIT license. See LICENSE.md file for details.

#ifndef POMDOG_SPRITERENDERABLE_552FA480_HPP
#define POMDOG_SPRITERENDERABLE_552FA480_HPP

#include "Renderable.hpp"
#include "Pomdog.Experimental/Rendering/Commands/SpriteCommand.hpp"
#include "Pomdog/Math/Rectangle.hpp"
#include "Pomdog/Math/Vector2.hpp"
#include <Pomdog/Pomdog.hpp>
#include <memory>

namespace Pomdog {

class SpriteRenderable: public Renderable {
public:
    explicit SpriteRenderable(std::shared_ptr<Texture2D> const& texture);

    SpriteRenderable(std::shared_ptr<Texture2D> const& texture, TextureRegion const& textureRegion);

    void Visit(GameObject & gameObject, Renderer & renderer) override;

    void OriginPivot(Vector2 const& originPivot);
    Vector2 OriginPivot() const;

    void Region(TextureRegion const& region);
    TextureRegion const& Region() const;

    Rectangle BoundingBox() const;

private:
    Detail::Rendering::SpriteCommand command;
    Matrix3x2 offsetMatrix;
    Vector2 originPivot;
    std::uint32_t dirtyFlags;
};

}// namespace Pomdog

#endif // POMDOG_SPRITERENDERABLE_552FA480_HPP
