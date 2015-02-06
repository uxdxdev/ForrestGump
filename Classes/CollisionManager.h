
#ifndef COLLISION_H_
#define	COLLISION_H_

// includes 
#include <vector>
#include <memory>

// forward declarations
class Player;
class Enemy;

/*	Singleton CollisionManager */
class CollisionManager
{
public:
	virtual bool init(); // initialization
	static CollisionManager* getInstance(); // instance of CollsionManager

	// register with the collision manager
	void registerEnemyWithCollisionManager(std::shared_ptr<Enemy> obj);

	// register the player object
	void registerPlayer(std::shared_ptr<Player> player);

	// check for collisions between the player and all other game objects
	bool checkCollisons();
	void cleanUp(); // delete CollisionManager

	// getters 
	std::shared_ptr<Player> getPlayer(){ return m_pPlayer; }; // player
	std::vector<std::shared_ptr<Enemy>> getVectorOfEnemies(){ return m_vpEnemies; }; // vector of enemies
	
private:
	static CollisionManager* m_Instance; 
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
	
	std::shared_ptr<Player> m_pPlayer; // player 
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies; // vector of GameObject pointers	
};

#endif