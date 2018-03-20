#ifndef __MANAGER__
#define __MANAGER__

#include "cocos2d.h"
#include "knight.h"
#include "ghost.h"
#include "Sprites.h"
#include "shot.h"
#include "smallGhost.h"
#include <SimpleAudioEngine.h>

class Manager : public cocos2d::Layer
{
public:
  Manager();
  ~Manager();
  static cocos2d::Scene* createScene();
  virtual bool init();
  void update(float);
  void spawnGhosts();
  void incrementScore();
    
  // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);
    
  // implement the "static create()" method manually
  CREATE_FUNC(Manager);

private:
  float moveTime;
  float dx, dy;
  cocos2d::Size visibleSize;
 // cocos2d::Point origin;
  int knightWidth;
  std::list<Sprites*> spriteList;
  std::list<Sprites*> backGhosts;
  std::list<Sprites*> shots;
  cocos2d::Label* scoreLabel;
  cocos2d::Label* winLabel;
  cocos2d::Label* label;
  CocosDenshion::SimpleAudioEngine* Music;
  CocosDenshion::SimpleAudioEngine* sound;

  cocos2d::Vec2 origin;
  int score;
  cocos2d::EventListenerKeyboard* eventListener;
  void Shoot();
  bool iShot;
  bool right;
  bool moveLeft;
  bool moveRight;

  //Updates for Parallax Scrolling
  void updateParallax();
  
  cocos2d::Sprite* bg1;
  cocos2d::Sprite* bg2;
  cocos2d::Sprite* mnt1;
  cocos2d::Sprite* mnt2;
  cocos2d::Sprite* cld1;
  cocos2d::Sprite* cld2;

  cocos2d::Size viewSize;
};

#endif // __MANAGER_H__
