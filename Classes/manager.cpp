#include "manager.h"
#include <iostream>


Manager::~Manager() {

  std::list<Sprites*>::iterator i = spriteList.begin();
  while(i != spriteList.end())
  {
      removeChild((*i)->getSprite());
      delete *i;
      i = spriteList.erase(i);
      ++i;
  }

  std::list<Sprites*>::iterator b = backGhosts.begin();
  while(b != backGhosts.end())
  {
      removeChild((*b)->getSprite());
      delete *b;
      b = backGhosts.erase(b);
      ++b;
  }
  
  Music->stopAllEffects();
  sound->stopAllEffects();
  Music->unloadEffect("Abyss.wav");
  sound->unloadEffect("swing.aif");

}
Manager::Manager() : 
  moveTime(0.1), 
  dx(5), 
  dy(5),
  iShot(false),
  right(true),
  moveLeft(false),
  moveRight(false),
  viewSize(cocos2d::Director::getInstance()->getVisibleSize())
  {
     Music = CocosDenshion::SimpleAudioEngine::getInstance();
     sound = CocosDenshion::SimpleAudioEngine::getInstance();
     eventListener = cocos2d::EventListenerKeyboard::create();
     spriteList.push_back(new Knight);
     spriteList.push_back(new Ghost);
     spriteList.push_back(new Ghost);
     spriteList.push_back(new Ghost);
     backGhosts.push_back(new SmallGhost);
     backGhosts.push_back(new SmallGhost);
     backGhosts.push_back(new SmallGhost);
     backGhosts.push_back(new SmallGhost);
     backGhosts.push_back(new SmallGhost);
     backGhosts.push_back(new SmallGhost);	
     scoreLabel = 
	cocos2d::Label::createWithTTF("Ghosts Killed: 0", "fonts/Marker Felt.ttf", 24);
     scoreLabel->setPosition(cocos2d::Vec2(100, 740));
     score = 0;
     label = cocos2d::Label::createWithTTF("Kill 50 Ghosts!", "fonts/Marker Felt.ttf", 30);

     visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
     origin = cocos2d::Director::getInstance()->getVisibleOrigin();
      
  }
void Manager::updateParallax(){
     
	if(moveLeft && !moveRight)
	{
          std::list<Sprites*>::iterator i = spriteList.begin();
          ++i;
	  while(i != spriteList.end()){
		(*i)->getSprite()->setPositionX((*i)->getSprite()->getPositionX()-20);
		++i;
	  }
	  bg1->setPositionX(bg1->getPositionX()-10);
	  bg2->setPositionX(bg2->getPositionX()-10);
	  mnt1->setPositionX(mnt1->getPositionX()-1);
	  mnt2->setPositionX(mnt2->getPositionX()-1);
	  cld1->setPositionX(cld1->getPositionX()-5);
	  cld2->setPositionX(cld2->getPositionX()-5);
	}
	else if(!moveLeft && moveRight)
	{
          std::list<Sprites*>::iterator i = spriteList.begin();
          ++i;
          while(i != spriteList.end()){
		(*i)->getSprite()->setPositionX((*i)->getSprite()->getPositionX()+20);
		++i;
	  }
	  bg1->setPositionX(bg1->getPositionX()+10);
	  bg2->setPositionX(bg2->getPositionX()+10);
	  mnt1->setPositionX(mnt1->getPositionX()+1);
	  mnt2->setPositionX(mnt2->getPositionX()+1);
	  cld1->setPositionX(cld1->getPositionX()+5);
	  cld2->setPositionX(cld2->getPositionX()+5);
	}
  };

void Manager::update(float dt) {
 //update parallax scrolling
 updateParallax();

  //Set if statements to have him go either way
   std::list<Sprites*>::iterator b = backGhosts.begin();
  while(b != backGhosts.end())
  { 
    (*b)->update(dt);
    ++b;
  }

 //Series of statements to cause Parallax Scrolling for mountain & background
 if (bg1->getPositionX() < -bg1->getContentSize().width/2) {
    bg1->setPositionX( bg2->getPositionX() + bg2->getContentSize().width);
  }
  if (bg2->getPositionX() < -bg2->getContentSize().width/2) {
    bg2->setPositionX(bg1->getPositionX() + bg1->getContentSize().width);
  }

 if (mnt1->getPositionX() < -mnt1->getContentSize().width/2) {
    mnt1->setPositionX( mnt2->getPositionX() + mnt2->getContentSize().width);
  }
  if (mnt2->getPositionX() < -mnt2->getContentSize().width/2) {
    mnt2->setPositionX(mnt1->getPositionX() + mnt1->getContentSize().width);
  }
 if (cld1->getPositionX() < -cld1->getContentSize().width/2) {
    cld1->setPositionX( cld2->getPositionX() + cld2->getContentSize().width);
  }
  if (cld2->getPositionX() < -cld2->getContentSize().width/2) {
    cld2->setPositionX(cld1->getPositionX() + cld1->getContentSize().width);
  }

  // Going Left
  if (bg1->getPositionX() > bg1->getContentSize().width/2) {
    bg2->setPositionX( bg1->getPositionX() - bg2->getContentSize().width);
  }
  if (bg2->getPositionX() > bg2->getContentSize().width/2) {
    bg1->setPositionX(bg2->getPositionX() - bg1->getContentSize().width);
  }

 if (mnt1->getPositionX() > mnt1->getContentSize().width/2) {
    mnt2->setPositionX( mnt1->getPositionX() - mnt2->getContentSize().width);
  }
  if (mnt2->getPositionX() > mnt2->getContentSize().width/2) {
    mnt1->setPositionX(mnt2->getPositionX() - mnt1->getContentSize().width);
  }
 if (cld1->getPositionX() > cld1->getContentSize().width/2) {
    cld2->setPositionX( cld1->getPositionX() - cld2->getContentSize().width);
  }
  if (cld2->getPositionX() > cld2->getContentSize().width/2) {
    cld1->setPositionX(cld2->getPositionX() - cld1->getContentSize().width);
  }
  //END OF PARALLAX SCROLL
 
 
 //STARTING SHOOT COLLISION
 std::list<Sprites*>::iterator front = spriteList.begin();
  (*front)->update(dt);
  if(iShot)
  {
        if(spriteList.size() == 1) spawnGhosts();
        std::list<Sprites*>::iterator i = spriteList.begin();
        ++i;
	std::list<Sprites*>::iterator s = shots.begin();

        while(s != shots.end())
 	{
             (*s)->update(dt);
	     while(i != spriteList.end())
             {
               (*i)->update(dt);
     	       if((*s)->collidedRect(*i)) 
               {
	          removeChild((*i)->getSprite());
	          delete (*i);
	          i = spriteList.erase(i);
                  incrementScore();
               }
     		else ++i;
             }
             if ((*s)->getWall())
	       {
           	  removeChild((*s)->getSprite());
		  delete(*s);
		  s = shots.erase(s);
  	       }
             else ++s;
        }
         
  }
  else
  {
        if(spriteList.size() == 1) spawnGhosts();
        std::list<Sprites*>::iterator it = spriteList.begin();
        ++it;
  	while(it != spriteList.end())
 	{
	  (*it)->update(dt);
	  ++it;
        }
  }
  if(shots.empty()) iShot = false;

  //END SHOOTING COLLISION STUFF IDK
}



  

void Manager::spawnGhosts() {
  Ghost * newSprite;
  for (unsigned int i = 0; i < 5; ++i) {
   newSprite = new Ghost(); 
   spriteList.push_back( newSprite ); 
   addChild( newSprite->getSprite() );
  }
}

void Manager::Shoot() {
  std::list<Sprites*>::iterator i = spriteList.begin();
  Shot* newShot = new Shot();
  newShot->getSprite()->setPosition((*i)->getSprite()->getPosition());

  if(!right){
	newShot->getSprite()->setScaleX(-1);
	newShot->setVel(-1500, 0);
  }
  else{
	newShot->getSprite()->setScaleX(1);
	newShot->setVel(1500,0);
  }
  shots.push_back(newShot);
  addChild(newShot->getSprite());
}



cocos2d::Scene* Manager::createScene() {
  // 'scene' is an autorelease object
  cocos2d::Scene* scene = cocos2d::Scene::create(); 
  // 'layer' is an autorelease object
  cocos2d::Layer* layer = Manager::create();
  // add layer as a child to scene
  scene->addChild(layer);
  // return the scene
  return scene;
}

// Initializes instance
bool Manager::init() {

  if ( !Layer::init() ) {
    return false;
  }
 
  //close icon
  cocos2d::MenuItemImage* closeItem = cocos2d::MenuItemImage::create(
     "CloseNormal.png","CloseSelected.png",
     CC_CALLBACK_1(Manager::menuCloseCallback, this));
    
  closeItem->setPosition(
     cocos2d::Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
     origin.y + closeItem->getContentSize().height/2));

  // create menu, it's an autorelease object
  cocos2d::Menu* menu = cocos2d::Menu::create(closeItem, NULL);
  menu->setPosition(cocos2d::Vec2::ZERO);
  this->addChild(menu, 1);

  //title label 

  label = cocos2d::Label::createWithTTF("Kill 50 Ghosts!", "fonts/Marker Felt.ttf", 30);
    
  // position the background on the center of the screen
  label->setPosition(
     cocos2d::Vec2(origin.x + visibleSize.width/2,
     origin.y + visibleSize.height - label->getContentSize().height));

  // add the label as a child to this layer
  addChild(label, 1);
  addChild(scoreLabel, 1); 

   cocos2d::Label* controls1 = 
	cocos2d::Label::createWithTTF("Controls:", "fonts/Marker Felt.ttf", 24);

   controls1->setPosition(cocos2d::Vec2(72, 715));
   controls1->setColor(cocos2d::Color3B(255,0,50));
   addChild(controls1, 1);

   cocos2d::Label* controls2 = 
	cocos2d::Label::createWithTTF("W: Move Up", "fonts/Marker Felt.ttf", 18);

   controls2->setPosition(cocos2d::Vec2(75, 690));
   controls2->setColor(cocos2d::Color3B(255,0,50));
   addChild(controls2, 1);
   
   cocos2d::Label* controls3 = 
	cocos2d::Label::createWithTTF("S: Move Down", "fonts/Marker Felt.ttf", 18);

   controls3->setPosition(cocos2d::Vec2(83, 670));
   controls3->setColor(cocos2d::Color3B(255,0,50));
   addChild(controls3, 1);
   
   cocos2d::Label* controls4 = 
	cocos2d::Label::createWithTTF("A: Move Left", "fonts/Marker Felt.ttf", 18);

   controls4->setPosition(cocos2d::Vec2(80, 650));
   controls4->setColor(cocos2d::Color3B(255,0,50));
   addChild(controls4, 1);

  cocos2d::Label* controls5 = 
	cocos2d::Label::createWithTTF("D: Move Right", "fonts/Marker Felt.ttf", 18);

   controls5->setPosition(cocos2d::Vec2(83, 630));
   controls5->setColor(cocos2d::Color3B(255,0,50));
   addChild(controls5, 1);

  cocos2d::Label* controls6 = 
	cocos2d::Label::createWithTTF("Space: Shoot", "fonts/Marker Felt.ttf", 18);

   controls6->setPosition(cocos2d::Vec2(75, 610));
   controls6->setColor(cocos2d::Color3B(255,0,50));
   addChild(controls6, 1);
   
   
   


 //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("song.mp3");
  //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("song.mp3", true);
   Music->preloadBackgroundMusic("Abyss.wav");
   Music->playBackgroundMusic("Abyss.wav", true);


  //PARALLAX STUFF
  bg1 = cocos2d::Sprite::create("background.png");
  bg1->setPosition(0, visibleSize.height/2);
  bg2 = cocos2d::Sprite::create("background.png");
  bg2->setPosition(bg1->getContentSize().width - 1, visibleSize.height/2);

  mnt1 = cocos2d::Sprite::create("sky.png");
  mnt1->setPosition(0, visibleSize.height/2);
  mnt2 = cocos2d::Sprite::create("sky.png");
  mnt2->setPosition(mnt1->getContentSize().width - 1, visibleSize.height/2);

  cld1 = cocos2d::Sprite::create("clouds.png");
  cld1->setPosition(0, visibleSize.height/2);
  cld2 = cocos2d::Sprite::create("clouds.png");
  cld2->setPosition(cld1->getContentSize().width - 1, visibleSize.height/2);

  //Mountains
  addChild(mnt1);
  addChild(mnt2);

  //Clouds
  addChild(cld1);
  addChild(cld2);

    //Ghosts in Background
    std::list<Sprites*>::iterator g = backGhosts.begin();
  while(g != backGhosts.end()){
	(*g)->getSprite()->setScale(0.4);
	addChild((*g)->getSprite());
	++g;
  }

  //background
  addChild(bg1);
  addChild(bg2);



  std::list<Sprites*>::iterator i = spriteList.begin();
  while(i != spriteList.end())
  { 
    addChild((*i)->getSprite());
    ++i;
  }

  //Keyboard Stuff

  eventListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode,
	 cocos2d::Event* event)
  {

        std::list<Sprites*>::iterator i = spriteList.begin();
	switch(keyCode){
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
                        (*i)->moveLeft();
			right = false;
			moveRight = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			(*i)->moveRight();
			right = true;
			moveLeft = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			(*i)->moveUp();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			(*i)->moveDown();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
			sound->playEffect("swing.aif");
			Shoot();
			iShot = true;
			break;
		default: 
			break;
	}
  };

  std::list<Sprites*>::iterator front = spriteList.begin();
  this->_eventDispatcher->addEventListenerWithSceneGraphPriority(
	eventListener,(*front)->getSprite());



  cocos2d::EventListenerKeyboard* upListener = 
 	cocos2d::EventListenerKeyboard::create();

  upListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode,
	 cocos2d::Event* event)
  {

        std::list<Sprites*>::iterator i = spriteList.begin();

	switch(keyCode){
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
                        (*i)->notMovingLR();
			moveRight = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			(*i)->notMovingLR();
			moveLeft = false;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			(*i)->notMovingUD();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			(*i)->notMovingUD();
			break;
		default: 
			break;
	}
};


  this->_eventDispatcher->addEventListenerWithSceneGraphPriority
		(upListener,(*front)->getSprite());



  schedule( schedule_selector(Manager::update));
  return true;
}


void Manager::menuCloseCallback(Ref* pSender) {
  cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}


//this last function is longer than it needs to be, everything past 
//line 483 is copy-paste.
void Manager::incrementScore(){
  score++;
  std::string result;
  std::stringstream ss;
  ss << "Ghosts Killed: " << score;
  result = ss.str();
  removeChild(scoreLabel);
  scoreLabel = 
	cocos2d::Label::createWithTTF(result, "fonts/Marker Felt.ttf", 24);
  scoreLabel->setPosition(cocos2d::Vec2(100, 740));
  addChild(scoreLabel);
  if(score == 50)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("You Win!", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  } 
  if(score == 75)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("You're Doing It!", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 100)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("Great Job!", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 150)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("Still Here?", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 200)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("That's a Nice Score.", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 250)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("How Long has it Been?", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 275)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("I'm Just Impressed Now.", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 300)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("You're A Monster!", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 325)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("This is Crazy.", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 350)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("How Long Must I Run!", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 375)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("I Wasn't Designed for This!", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  if(score == 400)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("I Give Up", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
 if(score == 425)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("Jk, Still Here.", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
  //hey there 8)
  if(score == 450)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("Leaving Though", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
 if(score == 475)
  {
	removeChild(label);
	label = cocos2d::Label::createWithTTF("Bye", "fonts/Marker Felt.ttf", 50);
        label->setPosition( cocos2d::Vec2(origin.x + visibleSize.width/2,
    		 origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(cocos2d::Color3B(255,0,50));

	addChild(label);

  }
}
