/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#pragma once

#ifdef _MSC_VER
// Upgrade warning to error: All control paths must return a value
	#pragma warning(error : 4715)
#endif

// Pineapple includes
#include <Pineapple/Engine/Container/Bitfield.h>
#include <Pineapple/Engine/Container/Rect.h>
#include <Pineapple/Engine/Container/Vect2.h>
#include <Pineapple/Engine/Platform/Event.h>
#include <Pineapple/Engine/Platform/File.h>
#include <Pineapple/Engine/Platform/Platform.h>
#include <Pineapple/Engine/System/InputHandler.h>
#include <Pineapple/Engine/System/Object.h>
#include <Pineapple/Engine/System/TimerHandler.h>
#include <Pineapple/Engine/System/World.h>
#include <Pineapple/Engine/Util/Macro.h>
#include <Pineapple/Engine/Util/Obscure.h>

// Graphics
#include <Pineapple/Engine/Graphics/Font.h>
#include <Pineapple/Engine/Graphics/Graphics.h>
#include <Pineapple/Engine/Graphics/Map.h>
#include <Pineapple/Engine/Graphics/Sprite.h>
#include <Pineapple/Engine/Graphics/Texture.h>
#include <Pineapple/Engine/Graphics/TextureAtlas.h>
#include <Pineapple/Engine/Graphics/Tile.h>
#include <Pineapple/Engine/Graphics/TileMap.h>
#include <Pineapple/Engine/Graphics/TileSet.h>

// Sound
#include <Pineapple/Engine/Sound/Effect.h>
#include <Pineapple/Engine/Sound/Sound.h>

// Physics
#include <Pineapple/Engine/Physics/AABB.h>
#include <Pineapple/Engine/Physics/Particle.h>

// Common
#include <Pineapple/Engine/Prefab/Asset/Asset.h>
#include <Pineapple/Engine/Prefab/Game/Entity.h>
#include <Pineapple/Engine/Prefab/UI/Background.h>
#include <Pineapple/Engine/Prefab/UI/Fade.h>
#include <Pineapple/Engine/Prefab/UI/Flash.h>
