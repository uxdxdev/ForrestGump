#ifndef COLLECTABLE_FACTORY
#define	COLLECTABLE_FACTORY

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class CollectableFactory : public cocos2d::Layer
{
public:		
	virtual bool init();
	virtual ~CollectableFactory(){ this->cleanup(); };
	bool addTMXTileMap(const std::string& filename);
	bool initTilePositions(TMXLayer* layer, std::string name);
	bool spawnSprites();
	bool activateItems(std::string name);
	void cleanup();


	
	
	void setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	bool isSpawned(){ return m_bIsSpawned; };
	void update();	
	
	void moveSprites();
	void resetItem(Sprite* item);
	CREATE_FUNC(CollectableFactory);
private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pCoinLayer;
	TMXLayer* m_pItemLayer;
	TMXLayer* m_pBoosterLayer;
	TMXLayer* m_pFoodLayer;
	bool m_bIsSpawned;
	std::vector<Sprite*> m_vpItems;
	std::deque<Sprite*> m_vpActiveItems;
	int m_cActiveItems;
};

#endif