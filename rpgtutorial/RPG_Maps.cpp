#include "RPG_Maps.h"
#include <fstream>

cMap::cMap()
{
	pSprite = nullptr;
	nWidth = 0;
	nHeight = 0;
	m_solids = nullptr;
	m_indices = nullptr;
}

cMap::~cMap()
{
	delete[] m_solids;
	delete[] m_indices;
}

int cMap::GetIndex(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return m_indices[y * nWidth + x];
	else
		return 0;
	
}

bool cMap::GetSolid(int x, int y)
{
	if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		return m_indices[y * nWidth + x];
	else
		return true;
}

bool cMap::create(std::string fileData, olcSprite* sprite, std::string name)
{
	sName = name;
	pSprite = sprite;
	std::ifstream data(fileData, std::ios::in | std::ios::binary);
	if (data.is_open())
	{
		data >> nWidth >> nHeight;
		m_solids = new bool[nWidth * nHeight];
		m_indices = new int[nWidth * nHeight];
		for (int i = 0; i < nWidth * nHeight; i++)
		{
			data >> m_indices[i];
			data >> m_solids[i];
		}
		return true;
	}
	return false;
}

cMap_Village1::cMap_Village1()
{
	create("rpgdata/map/village1.lvl", RPG_Assets::get().GetSprite("village"), "coder town");
	
}

cMap_village2::cMap_village2()
{
	create("rpgdata/map/village2.lvl", RPG_Assets::get().GetSprite("village"), "debug town");
	
}
