#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "StoryScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	CocosDenshion::SimpleAudioEngine::getInstance()->end();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		glview = GLViewImpl::createWithRect("DON STOP", Rect(0, 0, 720 * 0.7, 1280 * 0.7));
#else
		glview = GLViewImpl::createWithRect("DON STOP", Rect(0, 0, 720, 1280));
#endif
		director->setOpenGLView(glview);

    }
    glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//srand((unsigned)time(nullptr));

	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm.mp3");
	experimental::AudioEngine::lazyInit();

    // create a scene. it's an autorelease object

    auto scene = SplashScene::createScene();
	//auto scene = StoryScene::createScene();

	// run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	experimental::AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    //CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	experimental::AudioEngine::resumeAll();
}
