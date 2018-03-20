#include <iostream>
#include <cmath>
#include "smallGhost.h"


SmallGhost::SmallGhost() : 
  velocity((rand()%299+50), (rand()%299+20)),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  origin( cocos2d::Director::getInstance()->getVisibleOrigin() ),
  sprite( cocos2d::Sprite::create("spooky1.png") )
{
  float x = rand()%1000+ 1;
 
 
  cocos2d::
  	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ghosts.plist");

  cocos2d::Vector<cocos2d::SpriteFrame*>
  frames = getAnimation("ghosts", 5); 
 
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  sprite->setPosition( cocos2d::Point(x, 600) ); 

  cocos2d::Animation*
    animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/7);
  sprite->runAction(
    cocos2d::RepeatForever::create(cocos2d::Animate::create(animation))
  );
}

bool SmallGhost::collidedRect(const Sprites* otherSprite) const {
  int myWidth = sprite->getContentSize().width; 
  int myHeight = sprite->getContentSize().height; 
  int oWidth = otherSprite->getSprite()->getContentSize().width; 
  int oHeight = otherSprite->getSprite()->getContentSize().height; 

  cocos2d::Point myPos = sprite->getPosition();
  cocos2d::Point oPos  = otherSprite->getSprite()->getPosition();

  if ( myPos.x+myWidth/2 < oPos.x-oWidth/2 ) return false;
  if ( myPos.x-myWidth/2 > oPos.x+oWidth/2 ) return false;
  if ( myPos.y-myHeight/2 > oPos.y+oHeight/2 ) return false;
  if ( myPos.y+myHeight/2 < oPos.y-oHeight/2 ) return false;
  return true;
}


cocos2d::Vector<cocos2d::SpriteFrame*> 
SmallGhost::getAnimation(const char *prefix, int count) {
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


void SmallGhost::update(float dt) {
  cocos2d::Vec2 position = sprite->getPosition();
  cocos2d::Vec2 incr = velocity * dt;
  sprite->setPosition(position.x + incr.x, position.y + incr.y );

  cocos2d::Point location = sprite->getPosition();
  if ( location.x > viewSize.width - sprite->getContentSize().width/2 ) {
    velocity.x = -abs(velocity.x);
    sprite->setScale(-0.4);
    sprite->setScaleY(0.4);
   
  }
  else if ( location.x < sprite->getContentSize().width/2 - 20) {
    velocity.x = abs(velocity.x);
    sprite->setScale(0.4);
   
  }
  else if ( location.y > viewSize.height - sprite->getContentSize().height/2 - 10) {
    velocity.y = -abs(velocity.y);
    
  }
  else if ( location.y < sprite->getContentSize().height/2 - 30) {
    velocity.y = abs(velocity.y);

  }
}

