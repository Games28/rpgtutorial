#include "RPG_Assets.h"

void RPG_Assets::LoadSprites()
{
	auto load = [&](string sName, wstring sFIleName)
	{
		olcSprite* s = new olcSprite(sFIleName);
		m_mapSprite[sName] = s;
	};
	load("village", L"rpgdata/gfx/toml_spritesheetdark.spr");
	load("skelly", L"rpgdata/gfx/toml_Char001.png.spr");
	load("player", L"rpgdata/gfx/toml_CharacterSprites.spr");
	load("font", L"rpgdata/gfx/javidx9_nesfont8x8.spr");
	load("worldmap", L"rpgdata/gfx/worldmap1.png.spr");
	load("skymap", L"rpgdata/gfx/sky1.png.spr");
	load("title", L"rpgdata/gfx/title3.png.spr");
	load("balloon", L"rpgdata/gfx/balloon1.png.spr");
	load("sword", L"rpgdata/gfx/Sword.spr");
	load("hitech", L"rpgdata/gfx/toml_modernish.spr");

	load("purple", L"rpgdata/gfx/toml_purple.spr");

	load("health", L"rpgdata/gfx/item_health.spr");
	load("healthboost", L"rpgdata/gfx/item_healthboost.spr");

	load("Basic Sword", L"rpgdata/gfx/weapon_basic_sword.spr");
}

RPG_Assets::RPG_Assets()
{
}

RPG_Assets::~RPG_Assets()
{
}
