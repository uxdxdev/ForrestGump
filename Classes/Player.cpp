/*
3rd Year Project and Group dynamics assignment.

Forrest Gump

Copyright (c)	2014, 2015	David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

*/

// includes
#include <iostream>
#include "Player.h"
#include "cocos2d\cocos\math\Vec2.h"

/*
	Initialize the player

	@return bool true if initialized, false if not
*/
bool Player::init()
{
#ifdef _DEBUG
	CCLOG("Player::init() called");
#endif	
	Player::playerPosition = cocos2d::Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 3 + origin.y);
	setType(EGameOjectType::PLAYER);
	setName("Player One - Forrest");
	return true;
}

/*
	get player sprite information

	@return cocos2d::Sprite* the player sprite information
*/
cocos2d::Sprite* Player::getSprite()
{	
	return m_pCharacterSprite;
}

/*
	set player sprite information
*/
void Player::setSprite(char* pathToFile)
{
	m_pCharacterSprite = cocos2d::Sprite::create(pathToFile);
}

/*
	Update the player
*/
void Player::update()
{
	CCLOG("Updating Player");
	
	// update the sprite position
	Player::m_pCharacterSprite->setPosition(Player::playerPosition);
	
	// set the players bounding box to its Sprite Bounding box
	Player::setBoundingBox(m_pCharacterSprite->getBoundingBox());
}

void Player::cleanUp()
{
#ifdef _DEBUG
	CCLOG("Player::cleanUp()");
#endif	
}