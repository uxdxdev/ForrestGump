#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "MainMenu.h"
#include "Pause.h"
#include "Player.h"

USING_NS_CC;

Scene* GameScene::createScene()
{	
	auto scene = Scene::createWithPhysics();	
	scene->setTag(TAG_GAME_SCENE);

	GameScene* gameLayer = GameScene::create();
	gameLayer->SetPhysicsWorld(scene->getPhysicsWorld()); // set the layers physics
	scene->addChild(gameLayer, 0, TAG_GAME_LAYER);
	
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}	
	this->initializeGame();

	return true;
}

bool GameScene::initializeGame()
{	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_action_1.wav", true);
	
	//ANIMATION
	Vector<SpriteFrame*> animFrames(4);
	char str[100] = { 0 };
	int i = 1;
	while (i <= 2)
	{
		sprintf(str, "sprites/walk%02d.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 100, 128)); //we assume that the sprites' dimentions are 40*40 rectangles.
		i++;
		animFrames.pushBack(frame);
		sprintf(str, "sprites/walk%02d.png", i);
		auto frame1 = SpriteFrame::create(str, Rect(0, 0, 100, 128)); //we assume that the sprites' dimentions are 40*40 rectangles.
		i++;
		animFrames.pushBack(frame1);
		i++;
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	animate = Animate::create(animation);
	

	//END ANIMATION

	

	// Game play layer
	gamePlayLayer = Layer::create();
	this->addChild(gamePlayLayer, 0, "gamePlayLayer");

	// HUD layer
	m_HudLayer = HUD::create();
	this->addChild(m_HudLayer, 1, "hudLayer");

	//Background layer
	m_pParallax = Parallax::create();
	gamePlayLayer->addChild(m_pParallax, 0, "parallax");	
	if(m_pParallax->addBackground("background/backgroundFirst.png", "background/backgroundSecond.png", "background/backgroundThird.png"))
		CCLOG("Images loaded successful");		

	// add floorSprite to game scene
	auto floorSprite = Sprite::create("foreground/floorSprite.png");
	floorSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, floorSprite->getContentSize().height / 2 + origin.y));
	auto floorEdgeBody = PhysicsBody::createEdgeBox(floorSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	floorSprite->setPhysicsBody(floorEdgeBody);
	floorSprite->getPhysicsBody()->setDynamic(false);
	gamePlayLayer->addChild(floorSprite, -1); // add at z:1 for floorSprite	
	WorldManager::getInstance()->setFloorSprite(floorSprite);
		
	// Player			
	playerSprite = Player::create("sprites/Player.png");		
	playerSprite->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, FLOOR_SPRITE_TOP);
	auto playerPhysicsBody = PhysicsBody::createBox(playerSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	playerSprite->setPhysicsBody(playerPhysicsBody);
	playerPhysicsBody->setDynamic(false);
	gamePlayLayer->addChild(playerSprite, 0);
	WorldManager::getInstance()->setPlayer(playerSprite);
		

	playerSprite->runAction(RepeatForever::create(animate));
	

	// Segment spawns	
	spawnSegmentTimer = 0;
	//m_pSegmentManager = SegmentManager::create();
	//this->addChild(m_pSegmentManager);
	//m_pSegmentManager->spawnSegment();


	// pause button
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(GameScene::pause, this));
	menu_item_pause->setPosition(Vec2(origin.x + visibleSize.width - menu_item_pause->getContentSize().width / 2,
		origin.y + visibleSize.height - menu_item_pause->getContentSize().height / 2));

	// create menu, add menu items and add to the game scene
	auto* menu = Menu::create(menu_item_pause, NULL);
	menu->setPosition(Point(0, 0));
	m_HudLayer->addChild(menu);

	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
			
	m_fSpeed = 5.0f;

	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	CCLOG("onContactBegin -------> ");			
	return true;
}

void GameScene::update(float delta)
{
	CCLOG("-------------GAME LOOP START--------------");	

	spawnSegmentTimer++;
	if (spawnSegmentTimer > 500)
	{
		CCLOG("Spawn segment");
		//this->addChild(m_pSegment->spawnSegment());
		spawnSegmentTimer = 0;
	}

	WorldManager::getInstance()->getPlayer()->update();
	m_HudLayer->updateScore();

	CCLOG("Parallax");
	m_pParallax->updateBackground();

	//ANIMATION TESTS
	
	//AnimationCache *animationCache = AnimationCache::getInstance();
	//animationCache->addAnimationsWithFile("walk.plist");
	//Animation* animation = animationCache->animationByName("Animation");
	
	
	//SOURCE: http://www.cocos2d-x.org/wiki/Sprite_Sheet_Animation
	CCLOG("Animation");
	
	/*****************************************************
	Vector<SpriteFrame*> animFrames(15);

	char str[100] = { 0 };



	for (int i = 1; i < 4; i++)
	{
		sprintf(str, "sprites/walk%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
	playerSprite->runAction(RepeatForever::create(Animate::create(animation)));
	**************************************************************/
	//running animation	
	//moving my hero
	/*
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprites/player2.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("sprites/player2.plist");
	
	CCAnimation* anim = CCAnimation::create();

	for (int i = 1; i <= 2; i++) {
		String *str = String::createWithFormat("sprites/Playerwalk%02d.png", i);
		anim->addSpriteFrameWithFileName(str->getCString());
	}
	anim->setLoops(-1);
	Animate *animate = Animate::create(anim);
	playerSprite->runAction(animate);
	*/
	
	/* MOVING FOLLOWING HERO DIRECTION
	if ((actualPos.x <= location.x) && (actualPos.y <= location.y)) {

		playerSprite->runAction(Utils::getAnimationWithFrames(9, 16));
	}
	else if ((actualPos.x >= location.x) && (actualPos.y >= location.y)) {
		hero->runAction(Utils::getAnimationWithFrames(1, 8));
	}
	else if ((actualPos.x <= location.x) && (actualPos.y >= location.y)) {
		hero->runAction(Utils::getAnimationWithFrames(1, 4));
		hero->runAction(Utils::getAnimationWithFrames(9, 12));
	}
	else{
		hero->runAction(Utils::getAnimationWithFrames(13, 16));
		hero->runAction(Utils::getAnimationWithFrames(5, 8));
	}
	*/
	
//	playerSprite->runAction(m_pAnimation->getAnimationWithFrames(1, 2));
	//playerSprite->runAction(RepeatForever::create(AnimationMoves::getAnimationWithFrames(1, 2)));// (AnimationMoves::getAnimationWithFrames(1, 2));
	//playerSprite->runAction(RepeatForever::create(animate));

	//FIM ANIMATION TESTS

	
	
	CCLOG("-------------GAME LOOP END--------------");
}

/*
	This function converts each touch the user does into a Point(x, y)
*/
inline Point locationInGLFromTouch(Touch& touch)
{
	auto director = Director::getInstance();
	return director->convertToGL(touch.getLocationInView());
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) 
{
	WorldManager::getInstance()->getPlayer()->touch(locationInGLFromTouch(*touch));
	//playerSprite->stopAllActions();
	//playerSprite->runAction(AnimationMoves::getAnimationWithFrames(1, 4));
	//hero->runAction(Utils::getAnimationWithFrames(9, 16));
	return true;
}


void GameScene::pause(cocos2d::Ref *pSender)
{
	CCLOG("Pause");
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));

	// to play sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);
}