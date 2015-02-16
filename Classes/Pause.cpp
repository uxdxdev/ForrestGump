#include "Pause.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* Pause::createScene()
{
	auto scene = Scene::create();
	auto layer = Pause::create();
	scene->addChild(layer);
	return scene;
}

bool Pause::init()
{    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
	auto pauseMenuBackground = Sprite::create("background/pauseMenuBackground.png");
	pauseMenuBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(pauseMenuBackground, -50);
	
	// create the Pause menu items
	auto resumeButton = MenuItemImage::create("buttons/resume.png", "buttons/resume_clicked.png", CC_CALLBACK_1(Pause::resume, this));
	auto mainMenuButton = MenuItemImage::create("buttons/menu.png", "buttons/menu_clicked.png", CC_CALLBACK_1(Pause::mainMenu, this));
	auto exitButton = MenuItemImage::create("buttons/exit.png", "buttons/exit_clicked.png", CC_CALLBACK_1(Pause::exit, this));
    
	// position the menu buttons on screen
	resumeButton->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3) + 150));
	mainMenuButton->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3)));
	exitButton->setPosition(Point(visibleSize.width - 50, (visibleSize.height / 3)-100));
	
	// create menu and add menu items
	auto* menu = Menu::create(resumeButton, mainMenuButton, exitButton, NULL);
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}

void Pause::resume(cocos2d::Ref *pSender)
{
    Director::getInstance()->popScene();		
}

void Pause::mainMenu(cocos2d::Ref *pSender)
{
	Director::getInstance()->popScene();
    auto scene = MainMenu::createScene();    
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void Pause::exit(cocos2d::Ref *pSender)
{
	Director::sharedDirector()->end();
}

