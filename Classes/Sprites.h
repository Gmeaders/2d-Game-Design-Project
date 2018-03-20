#ifndef SPRITES_H
#define SPRITES_H
#include "cocos2d.h"


class Sprites{ 
public:
	Sprites() {};
	virtual ~Sprites() {};
	virtual void update(float) = 0;
        virtual void moveRight() = 0;
  	virtual void moveLeft() = 0;
	virtual void moveUp() = 0; 
  	virtual void moveDown() = 0;
	virtual cocos2d::Sprite* getSprite() const = 0;
	virtual bool collidedRect(const Sprites*) const = 0;
        virtual void setVel(float, float) = 0;
        virtual bool getWall() const = 0;
        virtual void notMovingUD() = 0;
  	virtual void notMovingLR() = 0;

};

#endif
