#include "MainMenu.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();    
    auto layer = MainMenu::create();	
    scene->addChild(layer);	
    return scene;
}

bool MainMenu::init()
{    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// particle testing  for high scores button
	CCParticleSystem *ccEmitter = CCParticleSystemQuad::create("particles/Flower.plist");
	ccEmitter->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 2));
	ccEmitter->setEmissionRate(200.00);
	ccEmitter->setTotalParticles(50);
	this->addChild(ccEmitter);

	// particle testing for play button
	CCParticleSystem *ccEmitter2 = CCParticleSystemQuad::create("particles/Flower.plist");
	ccEmitter2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 8) * 2));
	ccEmitter2->setEmissionRate(300.00);
	ccEmitter2->setTotalParticles(50);
	this->addChild(ccEmitter2);

	// particle testing for settings button
	CCParticleSystem *ccEmitter3 = CCParticleSystemQuad::create("particles/Flower.plist");
	ccEmitter3->setPosition(Point(visibleSize.width / 4, (visibleSize.height / 5) * 2));
	ccEmitter3->setEmissionRate(300.00);
	ccEmitter3->setTotalParticles(50);
	this->addChild(ccEmitter3);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm_menu.wav", true);
	
	auto mainMenuBackground = Sprite::create("background/MainMenuBackground.png");
	mainMenuBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(mainMenuBackground, -50);

	// create the main menu items
	auto playButton = MenuItemImage::create("buttons/PlayNormal.png", "buttons/PlaySelected.png", CC_CALLBACK_1(MainMenu::playGame, this));
	auto highscoresButton = MenuItemImage::create("buttons/TrophyNormal.png", "buttons/TrophySelected.png", CC_CALLBACK_1(MainMenu::leaderboard, this));
	auto settingsButton = MenuItemImage::create("buttons/settings2.png", "buttons/settings2.png", CC_CALLBACK_1(MainMenu::settings, this));
	
	
	// position the menu buttons on screen
	playButton->setPosition(Point(0,0));
	highscoresButton->setPosition(Point(0,0));
	settingsButton->setPosition(Point(0,0));
	

	// create menu and add menu items
	auto* menu = Menu::create(playButton, highscoresButton, settingsButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);




	// creation of actions for tweening of main menu
	auto ccPlayBtnAction = MoveBy::create(1, Point(visibleSize.width / 2, (visibleSize.height / 8) * 2));
	playButton->runAction(ccPlayBtnAction);
	

	auto ccSettingsBtnAction = MoveBy::create(1, Point(visibleSize.width / 4, (visibleSize.height / 5) * 2));
	settingsButton->runAction(ccSettingsBtnAction);

	auto ccHighScoreBtnAction = MoveBy::create(1, Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 2));
	highscoresButton->runAction(ccHighScoreBtnAction);

	// loading .plist file
	//CCString* file = CCString::create("sprites/walk.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(file->getCString());
	
	auto rotateAction = RotateBy::create(2.0f, 360.0f);
	playButton->runAction(rotateAction);
	
	auto rotateAction2 = RotateBy::create(2.0f, 360.0f);
	settingsButton->runAction(rotateAction2);

	auto rotateAction3 = RotateBy::create(2.0f, 360.0f);
	highscoresButton->runAction(rotateAction3);

    return true;
}

void MainMenu::mainMenu()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);		
}

void MainMenu::playGame(cocos2d::Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
	
}

void MainMenu::leaderboard(cocos2d::Ref *pSender)
{	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
}

void MainMenu::settings(cocos2d::Ref *pSender)
{		
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
}