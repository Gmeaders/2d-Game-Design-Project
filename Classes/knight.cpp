#include <iostream>
#include <cmath>
#include "knight.h"


float getVelocity() {
  float x = rand() % 5 + 1;
  x = (rand()%2?-1:1)*x;
  return x;
}

Knight::Knight() : 
  velocity(0, 0),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  origin( cocos2d::Director::getInstance()->getVisibleOrigin() ), 
  currentVelX(0),
  currentVelY(0),
  amIRight(true),
  stoppedUD(true),
  stoppedLR(false)
{
  cocos2d::
  	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("idle.plist");

  frames = getAnimation("idle", 2); 
 
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  sprite->setPosition( cocos2d::Point(525.0, 165.0) );

  animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/4);
  sprite->runAction(
   	cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
  animation->retain();

  cocos2d::
  	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("knight.plist");

  walkFrames  = getAnimation("knight", 8); 
  walkAnimation = cocos2d::Animation::createWithSpriteFrames(walkFrames, 1.0f/8);
  walkAnimation->retain();

}

bool Knight::collidedRect(const Sprites* otherSprite) const {
  int myWidth = sprite->getContentSize().width; 
  int myHeight = sprite->getContentSize().height; 
  int oWidth = otherSprite->getSprite()->getContentSize().width; 
  int oHeight = otherSprite->getSprite()->getContentSize().height; 

  cocos2d::Point myPos = sprite->getPosition();
  cocos2d::Point oPos  = otherSprite->getSprite()->getPosition();

  if ( myPos.x+myWidth/2 - 50 < oPos.x-oWidth/2 ) return false;
  if ( myPos.x-myWidth/2 + 70 > oPos.x+oWidth/2 ) return false;
  if ( myPos.y-myHeight/2+80 > oPos.y+oHeight/2 ) return false;
  if ( myPos.y+myHeight/2-80 < oPos.y-oHeight/2 ) return false;
  return true;
}

//get animation frames
cocos2d::Vector<cocos2d::SpriteFrame*> 
Knight::getAnimation(const char *prefix, int count) {
  cocos2d::SpriteFrameCache* 
  spritecache = cocos2d::SpriteFrameCache::getInstance();
  cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
  std::stringstream stream;
  for(int i = 1; i <= count; i++) {
    stream << std::string(prefix) << i << ".png";
    animFrames.pushBack(spritecache->getSpriteFrameByName(stream.str()));
    stream.clear();
    stream.str("");
  }
  return animFrames;
}


void Knight::update(float dt) {
  cocos2d::Vec2 position = sprite->getPosition();
  cocos2d::Vec2 incr = velocity * dt;
  

  cocos2d::Point location = sprite->getPosition();
  if ( location.y > 400 - sprite->getContentSize().height/2 ) {
    currentVelY = 0;
    velocity.set(currentVelX, currentVelY);
    incr.y = -1;
    
  }
  else if ( location.y < 175 - sprite->getContentSize().height/2 ) {
    currentVelY = 0;
    velocity.set(currentVelX, currentVelY);
    incr.y = 1;

  }
 sprite->setPosition(position.x + incr.x, position.y + incr.y );
}

void Knight::moveLeft(){
  sprite->setScaleX(-1);
  sprite->stopAllActions();
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(walkAnimation)));
  stoppedLR = false;

}

void Knight::moveRight(){
  sprite->setScaleX(1);
  sprite->stopAllActions();
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(walkAnimation)));
  stoppedLR = false;
}

void Knight::moveUp(){ 
  sprite->stopAllActions();
  
  currentVelY = 200;
  velocity.set(currentVelX, currentVelY);
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(walkAnimation)));
  stoppedUD = false;

}

void Knight::moveDown(){
  currentVelY = -200;
  velocity.set(currentVelX, currentVelY);
  sprite->stopAllActions();
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(walkAnimation)));
  stoppedUD = false;
}

void Knight::notMovingUD(){
    currentVelY = 0;
    velocity.set(currentVelX, currentVelY);
    stoppedUD = true;
    if(stoppedLR && stoppedUD){
     sprite->stopAllActions();
     sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
    }
}

void Knight::notMovingLR(){
    currentVelX = 0;
    velocity.set(currentVelX, currentVelY);
    stoppedLR = true;
    if(stoppedLR && stoppedUD){
     sprite->stopAllActions();
     sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
    }
}



