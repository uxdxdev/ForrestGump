
#ifndef COLLISION_H_
#define	COLLISION_H_

// includes 
#include "cocos2d.h"
#include "SegmentManager.h"
#include "Player.h"
#include <vector>
#include <memory>

// forward declarations
class Enemy;

class CollisionManager
{
public:
	virtual bool init();
	static CollisionManager* getInstance();			
	bool checkCollisions();
	void cleanUp(); 

	Player* getPlayer(){ return m_pPlayer; };
	SegmentManager* getSegmentManager(){ return m_pSegmentManager; };
	std::deque<TMXLayer*> getTMXLayerVector(){ return m_vpSegmentLayers; };
	
	void registerPlayer(Player* player){ m_pPlayer = player; };
	void registerSegment(TMXLayer* segment){ m_vpSegmentLayers.push_back(segment); };
	void registerSegmentManager(SegmentManager* segmentManager){ m_pSegmentManager = segmentManager; };
protected:
	Player* m_pPlayer; 	
	std::deque<TMXLayer*> m_vpSegmentLayers;
	SegmentManager* m_pSegmentManager;
private:
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
};

#endif