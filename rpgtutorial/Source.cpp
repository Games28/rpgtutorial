#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngineOOP.h"

#include "RPG_Assets.h"
#include "RPG_Maps.h"

class The_RPG : public olcConsoleGameEngineOOP
{
public:
	The_RPG()
	{
		m_sAppName = L"Tile Based Platform Game";
	}


private:
	cMap* m_pCurrentMap = nullptr;

	// Player Properties
	float fPlayerPosX = 1.0f;
	float fPlayerPosY = 1.0f;
	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;
	bool bPlayerOnGround = false;

	// Camera properties
	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	// Sprite Resources
	olcSprite* spriteTiles = nullptr;
	olcSprite* spriteMan = nullptr;
	olcSprite* m_sprFont = nullptr;

	// Sprite selection flags
	int nDirModX = 0;
	int nDirModY = 0;

	void DrawBigText(string sText, int x, int y)
	{
		int i = 0;
		for (auto c : sText)
		{
			int sx = ((c - 32) % 16) * 8;
			int sy = ((c - 32) / 16) * 8;
			DrawPartialSprite(x + i * 8, y, m_sprFont, sx, sy, 8, 8);
			i++;
		}
	}



protected:
	virtual bool OnUserCreate()
	{
		
		RPG_Assets::get().LoadSprites();
		m_pCurrentMap = new cMap_Village1();

		m_sprFont = RPG_Assets::get().GetSprite("font");

		spriteMan = new olcSprite(L"minijario.spr");

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		
		
		fPlayerVelX = 0.0f;
		fPlayerVelY = 0.0f;

		// Handle Input
		if (IsFocused())
		{
			if (GetKey(VK_UP).bHeld)
			{
				fPlayerVelY = -6.0f;
			}

			if (GetKey(VK_DOWN).bHeld)
			{
				fPlayerVelY = 6.0f;
			}

			if (GetKey(VK_LEFT).bHeld)
			{
				fPlayerVelX += (bPlayerOnGround ? -25.0f : -15.0f) * fElapsedTime;
				nDirModY = 1;
			}

			if (GetKey(VK_RIGHT).bHeld)
			{
				fPlayerVelX += (bPlayerOnGround ? 25.0f : 15.0f) * fElapsedTime;
				nDirModY = 0;
			}

			if (GetKey(VK_SPACE).bPressed)
			{
				if (fPlayerVelY == 0)
				{
					fPlayerVelY = -12.0f;
					nDirModX = 1;
				}
			}
		}

		// Gravity
		fPlayerVelY += 20.0f * fElapsedTime;

		// Drag
		if (bPlayerOnGround)
		{
			fPlayerVelX += -3.0f * fPlayerVelX * fElapsedTime;
			if (fabs(fPlayerVelX) < 0.01f)
				fPlayerVelX = 0.0f;
		}

		// Clamp velocities
		if (fPlayerVelX > 10.0f)
			fPlayerVelX = 10.0f;

		if (fPlayerVelX < -10.0f)
			fPlayerVelX = -10.0f;

		if (fPlayerVelY > 100.0f)
			fPlayerVelY = 100.0f;

		if (fPlayerVelY < -100.0f)
			fPlayerVelY = -100.0f;

		// Calculate potential new position
		float fNewPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
		float fNewPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		
		// Check for Collision

		//here
		if (fPlayerVelX <= 0) // Moving Left
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.9f))
			{
				fNewPlayerPosX = (int)fNewPlayerPosX + 1;
				fPlayerVelX = 0;
			}
		}
		else // Moving Right
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.9f))
			{
				fNewPlayerPosX = (int)fNewPlayerPosX;
				fPlayerVelX = 0;
		
			}
		}

		bPlayerOnGround = false;
		if (fPlayerVelY <= 0) // Moving Up
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fNewPlayerPosY) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.9f, fNewPlayerPosY))
			{
				fNewPlayerPosY = (int)fNewPlayerPosY + 1;
				fPlayerVelY = 0;
			}
		}
		else // Moving Down
		{
			if (m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) || m_pCurrentMap->GetSolid(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f) )
			{
				fNewPlayerPosY = (int)fNewPlayerPosY;
				fPlayerVelY = 0;
				bPlayerOnGround = true; // Player has a solid surface underfoot
				nDirModX = 0;
			}
		}

		// Apply new position
		fPlayerPosX = fNewPlayerPosX;
		fPlayerPosY = fNewPlayerPosY;

		// Link camera to player position
		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

		// Draw Level
		int nTileWidth = 16;
		int nTileHeight = 16;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > m_pCurrentMap->nWidth - nVisibleTilesX) fOffsetX = m_pCurrentMap->nWidth - nVisibleTilesX;
		if (fOffsetY > m_pCurrentMap->nHeight - nVisibleTilesY) fOffsetY = m_pCurrentMap->nHeight - nVisibleTilesY;

		// Get offsets for smooth movement
		float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
		float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

		// Draw visible tile map
		for (int x = -1; x < nVisibleTilesX + 1; x++)
		{
			for (int y = -1; y < nVisibleTilesY + 1; y++)
			{
				int idx = m_pCurrentMap->GetIndex(x + fOffsetX, y + fOffsetY);
				int sx = idx % 10;
				int sy = idx / 10;

				DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, m_pCurrentMap->pSprite, sx * nTileWidth, sy * nTileHeight, nTileWidth, nTileHeight);

				
			}
		}

		// Draw Player
		//Fill((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, (fPlayerPosX - fOffsetX + 1.0f) * nTileWidth, (fPlayerPosY - fOffsetY + 1.0f) * nTileHeight, PIXEL_SOLID, FG_GREEN);
		DrawPartialSprite((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, spriteMan, nDirModX * nTileWidth, nDirModY * nTileHeight, nTileWidth, nTileHeight);
		DrawBigText("hello jedi", 30, 30);

		return true;
	}
};
int main()
{
	The_RPG game;
	if (game.ConstructConsole(256, 240, 4, 4))
	{
		game.Start();
	}

	return 0;
}