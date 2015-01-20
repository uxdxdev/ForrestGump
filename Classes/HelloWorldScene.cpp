#include "HelloWorldScene.h"
#include "NewScene.h"
#include "GameScene.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mySprite = Sprite::create("CloseNormal.png");

	mySprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));

	this->addChild(mySprite);


	// create the main menu items
	auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(HelloWorld::Play, this)); // start the game scene
	auto menu_item_2 = MenuItemFont::create("Highscores", CC_CALLBACK_1(HelloWorld::Highscores, this)); // push the high scores scene
	auto menu_item_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(HelloWorld::Settings, this)); // push the settings scene
	//auto menu_item_4 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::ImageButton, this));

	// position the menu buttons on screen
	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));
	menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2));
	//menu_item_4->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 1));

	// create menu and add menu items
	auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);

	// position the main menu
	menu->setPosition(Point(0, 0));

	// add the menu to the scene
	this->addChild(menu);

    return true;
}

void HelloWorld::Play(cocos2d::Ref *pSender)
{
	CCLOG("Play");

	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(TransitionFlipX::create(2, scene));
}

void HelloWorld::Highscores(cocos2d::Ref *pSender)
{
	CCLOG("Highscores");

	auto scene = NewScene::createScene();

	Director::getInstance()->replaceScene(TransitionFlipX::create(2, scene));
}

void HelloWorld::Settings(cocos2d::Ref *pSender)
{
	CCLOG("Settings");
}


// image button
void HelloWorld::ImageButton(cocos2d::Ref *pSender)
{
	CCLOG("IMAGE Button");
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
