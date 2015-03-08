#include "SpawnManager.h"
#include "WorldManager.h"

USING_NS_CC;

bool SpawnManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->createEnemies();	
	srand(time(NULL));
	m_bIsSpawned = false;
	return true;
}

void SpawnManager::createEnemies()
{
	// Ground Enemy
	this->createEnemy("sprites/ground01.png", "ground", true, false);
	this->createEnemy("sprites/ground01.png", "ground", true, false);
	this->createEnemy("sprites/ground01.png", "ground", true, false);
	// Floating Enemies
	this->createEnemy("sprites/floating01.png", "floating", false, false);		
	this->createEnemy("sprites/floating01.png", "floating", false, false);
	this->createEnemy("sprites/floating01.png", "floating", false, false);
	this->createEnemy("sprites/floating01.png", "floating", false, false);
	this->createEnemy("sprites/floating01.png", "floating", false, false);
	this->createEnemy("sprites/floating01.png", "floating", false, false);
}

int SpawnManager::getRandomHeight()
{	
	int min = (int)WorldManager::getInstance()->getFloorSprite()->getContentSize().height * 2;
	int max = (int)VISIBLE_SIZE_HEIGHT;	
	return (rand() % max + min);
}

int SpawnManager::getRandomXPos()
{		
	int min = (int)VISIBLE_SIZE_WIDTH * 1.2;
	int max = (int)VISIBLE_SIZE_WIDTH * 2;
	return (rand() % max + min);
}

void SpawnManager::createEnemy(std::string filename, std::string name, bool gravity, bool rotate)
{
	auto enemy = Enemy::create(filename);
	enemy->setName(name);	
	if (name == "floating")
	{
		enemy->setPosition(Vec2(this->getRandomXPos(), this->getRandomHeight()));
	}
	else if (name == "ground")
	{
		enemy->setPosition(Vec2(this->getRandomXPos(), WorldManager::getInstance()->getFloorSprite()->getContentSize().height + enemy->getContentSize().height / 2));
	}	
	enemy->setVisible(true);
	enemy->animateEnemy();
	this->addChild(enemy);
	CollisionManager::getInstance()->addEnemy(enemy);

}

bool SpawnManager::spawnEnemy()
{	
	int randomnumber;
	int numberOfEnemies = CollisionManager::getInstance()->getEnemies().size();	
	randomnumber = (rand() % numberOfEnemies);	
	this->addEnemyToActiveVector(CollisionManager::getInstance()->getEnemies().at(randomnumber));	
	m_bIsSpawned = true;
	return true;
}

bool SpawnManager::addEnemyToActiveVector(Enemy* enemy)
{
	enemy->setVisible(true);
	m_vpActiveEnemies.push_back(enemy);
	return true;
}

void SpawnManager::update()
{	
	this->moveSprites();
}

void SpawnManager::moveSprites()
{
	if (!CollisionManager::getInstance()->getEnemies().empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getEnemies().size(); ++it)
		{
			auto enemy = CollisionManager::getInstance()->getEnemies().at(it);

			if (enemy)
			{
				// move by individual enemy speeds
				enemy->setPosition(Vec2(enemy->getPosition().x - ENEMY_MOVEMENT_SPEED, enemy->getPosition().y));

				if (enemy->getPosition().x < SCREEN_ORIGIN.x - enemy->getContentSize().width / 2){
					this->resetEnemy(enemy);
				}
			}
		}
	}
}

void SpawnManager::resetEnemy(Enemy* enemy)
{
	if (enemy != NULL)
	{
		Enemy* enemySprite = static_cast<Enemy*>(enemy);
		if (enemySprite->getName() == "floating")
		{
			enemySprite->setPosition(Vec2(this->getRandomXPos(), getRandomHeight()));
		}
		else if (enemySprite->getName() == "ground")
		{
			enemySprite->setPosition(Vec2(this->getRandomXPos(), enemySprite->getPositionY()));
		}
		enemySprite->setVisible(true);		
	}
}

void SpawnManager::pauseGame()
{
	if (!CollisionManager::getInstance()->getEnemies().empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getEnemies().size(); ++it)
		{
			auto enemy = CollisionManager::getInstance()->getEnemies().at(it);

			if (enemy)
			{
				enemy->pauseSchedulerAndActions();
			}
		}
	}
}
void SpawnManager::resumeGame()
{
	if (!CollisionManager::getInstance()->getEnemies().empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getEnemies().size(); ++it)
		{
			auto enemy = CollisionManager::getInstance()->getEnemies().at(it);

			if (enemy)
			{
				enemy->resumeSchedulerAndActions();
			}
		}
	}
}
