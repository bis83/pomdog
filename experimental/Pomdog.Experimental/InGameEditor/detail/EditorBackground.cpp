﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#include "EditorBackground.hpp"

namespace Pomdog {
namespace SceneEditor {
//-----------------------------------------------------------------------
EditorBackground::EditorBackground(std::shared_ptr<GameHost> const& gameHost)
	: lineBatch(gameHost->GraphicsContext(), gameHost->GraphicsDevice())
	, primitiveAxes(editorColorScheme.CenterAxisX, editorColorScheme.CenterAxisY, editorColorScheme.CenterAxisZ)
	, primitiveGrid(editorColorScheme.GuideLine, editorColorScheme.Grid)
{
	auto graphicsContext = gameHost->GraphicsContext();
	auto graphicsDevice = gameHost->GraphicsDevice();
	auto assets = gameHost->AssetManager();
	auto window = gameHost->Window();

	{
		depthStencilState = DepthStencilState::CreateNone(graphicsDevice);
		blendState = BlendState::CreateNonPremultiplied(graphicsDevice);
	}
}
//-----------------------------------------------------------------------
void EditorBackground::SetViewProjection(Matrix4x4 const& viewProjectionIn)
{
	viewProjectionMatrix = viewProjectionIn;
}
//-----------------------------------------------------------------------
void EditorBackground::Draw(GraphicsContext & graphicsContext)
{
	lineBatch.Begin(viewProjectionMatrix);
	{
		primitiveGrid.Draw(lineBatch);
		primitiveAxes.Draw(lineBatch);
	}
	lineBatch.End();
}
//-----------------------------------------------------------------------
}// namespace SceneEditor
}// namespace Pomdog
