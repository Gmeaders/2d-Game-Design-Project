#include "cocos2d.h"
#include "Sprites.h"

class SmallGhost : public Sprites{
public:
  SmallGhost();
  ~SmallGhost() {};
  void update(float);
  cocos2d::Sprite* getSprite() const { return sprite; }

    
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
  void notMovingUD(){};
  void notMovingLR(){};
  void setVel(float, float){};
  bool getWall() const{return false;};
};
