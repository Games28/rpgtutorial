
#include "olcConsoleGameEngineOOP.h"
#include "RPG_Assets.h"


class cMap
{
public:
	cMap();
	~cMap();

public:
	int nWidth;
	int nHeight;
	std::string sName;
	olcSprite* pSprite;

	int GetIndex(int x, int y);
	bool GetSolid(int x, int y);
	bool create(std::string fileData, olcSprite* sprite, std::string name);

private:
	int* m_indices = nullptr;
	bool* m_solids = nullptr;
};



class cMap_Village1 : public cMap
{
public:
	cMap_Village1();


};

class cMap_village2 : public cMap
{
public:
	cMap_village2();
};