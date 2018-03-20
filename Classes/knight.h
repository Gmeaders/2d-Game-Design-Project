#include "cocos2d.h"
#include "Sprites.h"


class Knight : public Sprites{
public:
  Knight();
  ~Knight(){animation->release();
	walkAnimation->release();};
  void update(float);
  cocos2d::Sprite* getSprite() const { return sprite; }
  void setVel(float a, float b){ velocity.set(a, b);}

    
private:
  cocos2d::Vec2 velocity;
  cocos2d::Size viewSize;
  cocos2d::Point origin;
  cocos2d::Sprite* sprite;
  cocos2d::Animation* animation;
  cocos2d::Animation* walkAnimation;
  cocos2d::Vector<cocos2d::SpriteFrame*> walkFrames;
  cocos2d::Vector<cocos2d::SpriteFrame*> frames;
  
  bool stoppedUD;
  bool stoppedLR;
  bool amIRight;
  float currentVelX;
  float currentVelY;
  cocos2d::Vector<cocos2d::SpriteFrame*> 
    		getAnimation(const char *format, int count);

  bool collidedRect(const Sprites*) const;

  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void notMovingUD();
  void notMovingLR();
  bool movingRight();
  bool getWall() const{return false;};

  
};
