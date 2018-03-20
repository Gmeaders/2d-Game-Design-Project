#include <iostream>
#include <cmath>
#include "shot.h"


Shot::Shot() : 
  velocity(0,0),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  origin( cocos2d::Director::getInstance()->getVisibleOrigin() ),
  sprite( cocos2d::Sprite::create("shot.png") ),
  hitWall(false)
{
   cocos2d::
  	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shot.plist");

  cocos2d::Vector<cocos2d::SpriteFrame*>
  frames = getAnimation("shot", 3); 
 
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  sprite->setPosition( cocos2d::Point(300.0, 165.0) ); 

  cocos2d::Animation*
    animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/8);
  sprite->runAction(
    cocos2d::RepeatForever::create(cocos2d::Animate::create(animation))
  );
}

bool Shot::collidedRect(const Sprites* otherSprite) const {
 int myWidth = sprite->getContentSize().width; 
  int myHeight = sprite->getContentSize().height; 
  int oWidth = otherSprite->getSprite()->getContentSize().width; 
  int oHeight = otherSprite->getSprite()->getContentSize().height; 

  cocos2d::Point myPos = sprite->getPosition();
  cocos2d::Point oPos  = otherSprite->getSprite()->getPosition();

  if ( myPos.x+myWidth/2 - 50 < oPos.x-oWidth/2 ) return false;
  if ( myPos.x-myWidth/2 + 70 > oPos.x+oWidth/2 ) return false;
  if ( myPos.y-myHeight/2+70 > oPos.y+oHeight/2 ) return false;
  if ( myPos.y+myHeight/2-80 < oPos.y-oHeight/2 ) return false;
  return true;
}


cocos2d::Vector<cocos2d::SpriteFrame*> 
Shot::getAnimation(const char *prefix, int count) {
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


void Shot::update(float dt) {
  cocos2d::Vec2 position = sprite->getPosition();
  cocos2d::Vec2 incr = velocity * dt;
  sprite->setPosition(position.x + incr.x, position.y + incr.y );

  cocos2d::Point location = sprite->getPosition();
  if ( location.x > viewSize.width - sprite->getContentSize().width/2 +100) {
    hitWall = true;
  }
  else if ( location.x < sprite->getContentSize().width/2 - 100) {
    hitWall = true; 
  }
 
}
