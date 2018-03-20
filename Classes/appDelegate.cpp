#include "appDelegate.h"
#include "manager.h"

static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);

AppDelegate::AppDelegate() { }

AppDelegate::~AppDelegate() { }

void AppDelegate::initGLContextAttrs() {
  //set OpenGL context attributions, now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

  cocos2d::GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages() {
  return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  cocos2d::Director* director = cocos2d::Director::getInstance();
  cocos2d::GLView *  glview = director->getOpenGLView();
  if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    glview = cocos2d::GLViewImpl::createWithRect("First Animation with spritesheet and plist", cocos2d::Rect(0, 0, mediumResolutionSize.width, mediumResolutionSize.height));
#else
    glview = GLViewImpl::create("Brian's Ghostly Animation");
#endif
    director->setOpenGLView(glview);
  }

  // turn on display FPS
  director->setDisplayStats(false);

  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0 / 60);

  register_all_packages();

  // create a scene. it's an autorelease object
  cocos2d::Scene* scene = Manager::createScene();
  // run
  director->runWithScene(scene);

  return true;
}

// This function will be called when the app is inactive. 
// When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  cocos2d::Director::getInstance()->stopAnimation();

  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  cocos2d::Director::getInstance()->startAnimation();

  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
