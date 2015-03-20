#include "AppDelegate.h"
#include "Definitions.h"
#include "Splash.h"
#include <string>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	
	//////////////

	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Grand Theft Muffins");
		director->setOpenGLView(glview);
	}

	director->setOpenGLView(glview);

	// Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	// a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
#else
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
#endif

	Size frameSize = glview->getFrameSize();

	std::vector<std::string> searchPath;

<<<<<<< HEAD
	// In this demo, we select resource according to the frame's height.
	// If the resource size is different from design resolution size, you need to set contentScaleFactor.
	// We use the ratio of resource's height to the height of design resolution,
	// this can make sure that the resource's height could fit for the height of design resolution.

	// if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > galaxyS4Resource.size.height)
	{
		CCLOG("Using large resources");
		searchPath.push_back(largeResource.directory);
		director->setContentScaleFactor(MIN(largeResource.size.height / designResolutionSize.height, largeResource.size.width / designResolutionSize.width));	}
	else if (frameSize.height > mediumResource.size.height)
	{
		CCLOG("Using galaxys4 resources");
		searchPath.push_back(galaxyS4Resource.directory);
		director->setContentScaleFactor(MIN(galaxyS4Resource.size.height / designResolutionSize.height, galaxyS4Resource.size.width / designResolutionSize.width));
=======
	if (screenSize.height >= 1536)
	{
		//CCLOG("using ipadhd 2048x1536");
		resourceDir.push_back("ipadhd");		
		glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
	}
	/*else if (screenSize.height >= 1080)
	{
		//CCLOG("using galaxyS4 1920x1080");
		resourceDir.push_back("galaxyS4");
		glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::NO_BORDER);
	}*/
	else if (screenSize.height >= 768)
	{
		//CCLOG("using nexus7 1024x768");
		resourceDir.push_back("nexus7");
		glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
>>>>>>> 8734582f7cc4f518121fbdbec60c59bbb3fe7306
	}
	// if the frame's height is larger than the height of small resource size, select medium resource.
	else if (frameSize.height > smallResource.size.height)
	{
<<<<<<< HEAD
		CCLOG("Using medium resources");
		searchPath.push_back(mediumResource.directory);
		director->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width));
	}
	// if the frame's height is smaller than the height of medium resource size, select small resource.
	else
	{
		CCLOG("Using small resources");
		searchPath.push_back(smallResource.directory);
		director->setContentScaleFactor(MIN(smallResource.size.height / designResolutionSize.height, smallResource.size.width / designResolutionSize.width));
=======
		//CCLOG("using iphonehd 960x640");
		resourceDir.push_back("iphonehd");
		glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
	}	
	else
	{
		//CCLOG("using iphone 480x320");
		resourceDir.push_back("iphone");
		glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);		
>>>>>>> 8734582f7cc4f518121fbdbec60c59bbb3fe7306
	}

	// set searching path
	FileUtils::getInstance()->setSearchPaths(searchPath);

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//////////////

	// create a scene. it's an autorelease object
	auto scene = Splash::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
