/*
<<<<<<< HEAD
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Player.h

	Description: The player class handles all player functionality. It
	keeps track on the player current state and actions at all times. We handle
	touches here also by registering the touch to make the player jump etc.
=======
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Player.h

Description: 

>>>>>>> 3b80dad6cdcb577e50f924efcb97006687b50c27
*/

#ifndef PLAYER_H_
#define	PLAYER_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite, public Character
{

public:	
	// Deconstrcutor
	virtual ~Player(){ this->playerCleanup(); };

	// Init
	virtual bool init();
	
	// Clean
	void playerCleanup();

	// Defining player actions
	typedef enum { BOOSTING, JUMPING, RUNNING } EPlayerAction;

	// Defining player jetpack actions
	typedef enum { BP_UP, BP_DOWN } EBackpackAction;

	// Creating player using filepath
	static Player* create(const std::string& filename);

	// Player jump function
	void jump();

	/* 
		Handles player touches

		@param point touched
	*/
	void touch(const Point& location);

	// Player update function, handles state and position
	void update();

	// Pauses all player actions
	void pausePlayer();

	// Resumes all player actions
	void resumePlayer();

	/* 
		Gets game object type

		@return game object type
	*/
	EGameOjectType getType(){ return m_eType; };

	/* 
		Gets the players current state 

		@return player state
	*/
	int getState(){ return m_eState; };

	/* 
		Gets the players current action

		@return player action
	*/
	int getAction(){ return m_ePlayerAction; }

	/* 
		Gets the players high score

		@return high score
	*/

	int getHighScore(){ return m_nHighscore; };

	/* 
		Gets the players current distance

		@return distance
	*/
	int getDistance(){ return m_nDistance; };

	/* 
		Gets the players current coins

		@return coins
	*/
	int getCoins(){ return m_nCoins; };

	/* 
		Gets the players current items

		@return items
	*/
	int getItems(){ return m_nItems; };

	/* 
		Gets the players current boosters

		@return boosters
	*/
	int getBoosters(){ return m_nBoosters; };

	/* 
		Gets the players current food

		@return food
	*/
	int getFood(){ return m_nFood; };

	/* 
		Gets the number of enemies killed

		@return number of enemies killed
	*/
	int getEnemiesKilled(){ return m_nEnemiesKilled; };	


	/* 
		Gets the player shield

		@return the shield sprite
	*/
	Sprite* getShield(){ return m_pShield; };

	// Sets the players game object type
	void setType(EGameOjectType type){ m_eType = type; };

	// Sets the players state
	void setState(ECharacterState state){ m_eState = state; };

	// Sets the players action
	void setAction(EPlayerAction action){ m_ePlayerAction = action; };

	// Sets the players jetpacks action
	void setBPAction(EBackpackAction bpAction){ m_eBackpackAction = bpAction; };

	// Sets the players highscore
	void setHighscore(int value){ m_nHighscore = value; };

	// Not implemented
	void addDistance();

	// Adds audio and particle effects to the coin
	void addCoin();

	// Adds audio and particle effects to the items
	void addItem();

	// Adds audio and particle effects to the boosters
	void addBooster();

	// Adds audio and particle effects to the food
	void addFood();

	// Adds audio and particle effects to killing enemies
	void addEnemiesKilled(){ m_nEnemiesKilled++; }

	// Adds particle effects
	void addParticle();

	/* 
		Gets path to particles and allows us to edit them 

		@param path
		@param particle width
		@param particle height
		@param number of particles
		@param effect duration
	*/
	void addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration);

	// Adds player death particles
	void addEnemyDeathParticle();

	// Resets coins
	void resetCoins();

	// Enables God Mode
	void setGodMode();

	// Disables God Mode
	void unsetGodMode();

	/* 
		Checks to see if God Mode is enabled	

		@return bool isGod
	*/
	bool isGod(){ return m_bGodMode; };

	/* 
		Gets the players animation

		@param players animation
		@param number of frames
	*/
	void getAnimationWithFrames(char* enemyAnimation, int frames);

	CREATE_FUNC(Player);

private:	
	EPlayerAction m_ePlayerAction;
	EBackpackAction m_eBackpackAction;

	int m_nHighscore;
	int m_nDistance;
	int m_nCoins;
	int m_nItems;
	int m_nBoosters;
	int m_nFood;
	int m_nEnemiesKilled;
	
	
	// God Mode count
	int m_nCount;

	std::string m_strUsername;
	CCParticleSystem *m_pEmitter;
	CCParticleSystem *m_pGameObjectEmitter;
	Sprite* m_pJetpack;
	bool m_bGodMode;
	Sprite* m_pShield;
};

#endif
