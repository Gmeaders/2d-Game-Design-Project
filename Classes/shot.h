#include "cocos2d.h"
#include "Sprites.h"

class Shot : public Sprites{
public:
  Shot();
  ~Shot() {};
  void update(float);
  cocos2d::Sprite* getSprite() const { return sprite; }
  void setVel(float a, float b){ velocity.set(a, b);}
  bool getWall() const {return hitWall;};
    
private:
  cocos2d::Vec2 velocity;
  cocos2d::Size viewSize;
  cocos2d::Point origin;
  cocos2d::Sprite* sprite;
  cocos2d::Vector<cocos2d::SpriteFrame*> 
    		getAnimation(const char *format, int count);
  bool collidedRect(const Sprites*) const;
  void moveRight(){};
  void moveLeft(){};
  void moveUp(){};
  void moveDown(){};
  void notMoving(){};
  void notMovingUD(){};
  void notMovingLR(){};
 
  bool hitWall;
};
