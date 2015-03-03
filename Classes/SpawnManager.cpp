#include "SpawnManager.h"
#include "WorldManager.h"

USING_NS_CC;

bool SpawnManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	srand(time(NULL));
	m_bIsSpawned = false;
	//this->spawnEnemy();
	//this->schedule(schedule_selector(SpawnManager::spawnEnemy), 0.7f * VISIBLE_SIZE_WIDTH);
	return true;
}

void SpawnManager::update()
{
	    int dist = WorldManager::getInstance()->getPlayer()->getDistance();
		this->schedule(schedule_selector(SpawnManager::spawnEnemy),spawnFrequency * VISIBLE_SIZE_WIDTH);
		setSpawnFreq(dist);
}


/*
	This function checks the current enemy count if it
	is less than the counter it spawns an enemy
*/
void SpawnManager::spawnEnemy(float dt)
{
	int spawnPos;
	//int numberOfEnemies = CollisionManager::getInstance()->getEnemies().size();
	float spawnPosSeed = 4.0;
	spawnPos = (rand() % 2);

	m_pGroundEnemy = Enemy::create("sprites/walk05.png");
	m_pFloatingEnemy = Enemy::create("sprites/Enemy.png");

	m_pGroundEnemy->setPosition(Vec2(m_pGroundEnemy->getPositionX() + VISIBLE_SIZE_WIDTH * 1.5, SCREEN_ORIGIN.y + (WorldManager::getInstance()->getFloorSprite()->getContentSize().height + this->getContentSize().height / 2.5)));
	m_pFloatingEnemy->setPosition(Vec2(m_pFloatingEnemy->getPositionX() + VISIBLE_SIZE_WIDTH * 1.5, SCREEN_ORIGIN.y + 100));

	auto groundEnemyPhysicsBody = PhysicsBody::createBox(m_pGroundEnemy->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	m_pGroundEnemy->setPhysicsBody(groundEnemyPhysicsBody);
	groundEnemyPhysicsBody->setDynamic(false);

	m_pGroundEnemy->setPhysicsBody(PhysicsBody::createBox(Size(m_pGroundEnemy->getContentSize().width, m_pGroundEnemy->getContentSize().height)));
	m_pGroundEnemy->getPhysicsBody()->setDynamic(true);
	m_pGroundEnemy->getPhysicsBody()->setGravityEnable(true);

	auto floatingEnemyPhysicsBody = PhysicsBody::createBox(m_pFloatingEnemy->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	m_pFloatingEnemy->setPhysicsBody(floatingEnemyPhysicsBody);
	floatingEnemyPhysicsBody->setDynamic(false);

	m_pFloatingEnemy->setPhysicsBody(PhysicsBody::createBox(Size(m_pFloatingEnemy->getContentSize().width, m_pFloatingEnemy->getContentSize().height)));
	m_pFloatingEnemy->getPhysicsBody()->setDynamic(true);
	m_pFloatingEnemy->getPhysicsBody()->setGravityEnable(false);

	this->addChild(m_pGroundEnemy);
	this->addChild(m_pFloatingEnemy);

	// adding enemies to the collision manager
	CollisionManager::getInstance()->addEnemy(m_pGroundEnemy);
	CollisionManager::getInstance()->addEnemy(m_pFloatingEnemy);

	int randomnumber;
	//int numberOfEnemies = CollisionManager::getInstance()->getEnemies().size();
	int numberOfEnemies = 2;
	randomnumber = (rand() % numberOfEnemies);

		switch (randomnumber)
		{
		case 0:
			this->addEnemyBehaviour(m_pGroundEnemy, "ground");
			break;
		case 1:
			this->addEnemyBehaviour(m_pFloatingEnemy, "floating");
			break;
		default:
			CCLOG("enemy spawn random number unknown");
		}

	//return true;
}


bool SpawnManager::addEnemyBehaviour(Enemy* enemy, std::string name)
{
	enemy->setName(name);

	if (enemy != NULL)
	{
		// resetin sprite poisition + seeting sprite to invisible
		auto reset = CCCallFuncND::create(this, callfuncND_selector(SpawnManager::resetSprite), (void*)enemy);
		auto enemtySpriteBehaviour = Sequence::create(
			MoveBy::create(SPRITE_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-(VISIBLE_SIZE_WIDTH * 2), 0)),
			reset,
			NULL);
		enemy->runAction(enemtySpriteBehaviour);
	}

	m_bIsSpawned = true;
	return true;
}

void SpawnManager::resetSprite(Node* sender, void* enemyRef)
{
	if (enemyRef != NULL)
	{
		Enemy* enemy = static_cast<Enemy*>(enemyRef);
		enemy->stopAllActions();
		enemy->setPosition(Vec2(enemy->getPositionX() + (VISIBLE_SIZE_WIDTH * 2), enemy->getPositionY()));
		enemy->setVisible(true);
		m_bIsSpawned = false;
	}
}

void SpawnManager::setSpawnFreq(int dist)
{
	if (dist > 0 && dist < 1000){
		spawnFrequency = ENEMY_SPAWN_FREQ_LEVEL_1;
	}
	else if (dist > 1000 && dist < 2000)
	{
		spawnFrequency = ENEMY_SPAWN_FREQ_LEVEL_2;
	}
	else if (dist > 2000 && dist < 3000)
	{
		spawnFrequency = ENEMY_SPAWN_FREQ_LEVEL_3;
	}
	else if (dist > 3000 && dist < 4000)
	{
		spawnFrequency = ENEMY_SPAWN_FREQ_LEVEL_4;
	}
	else if (dist > 4000 && dist < 5000)
	{
		spawnFrequency = ENEMY_SPAWN_FREQ_LEVEL_5;
	}
	else if (dist > 5000)
	{
		spawnFrequency = ENEMY_SPAWN_FREQ_LEVEL_6;
	}
}