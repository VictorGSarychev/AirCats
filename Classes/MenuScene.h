#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "Defines.h"

class Visible{
public:
  static cocos2d::Size visibleSize;
  static cocos2d::Vec2 origin;

  static void setVisibleSize(cocos2d::Size size){ visibleSize = size; };
  static void setOrigin(cocos2d::Vec2 vec2){ origin = vec2; }

  static cocos2d::Size getVisibleSize(){ return visibleSize; };
  static cocos2d::Vec2 getOrigin(){ return origin; }
};

class LabelCreator{
public:
  cocos2d::Label *titleLabel;
  cocos2d::Color3B color_titleLabel;
  cocos2d::Vec2 position_titleLabel;
  void addLabelTTF(cocos2d::Label* &label, const std::string &initText, const std::string &fontFilePath, const float fontSize, cocos2d::Color3B color, cocos2d::Point position);
};

class MenuItemCreator{
public:
  cocos2d::Color3B colorMenuItems;
  cocos2d::Vector<cocos2d::MenuItemFont*> menuItems;

  void setColorAllMenuItemFont(cocos2d::Vector<cocos2d::MenuItemFont*> menuItems, cocos2d::Color3B color);
};

class MenuScene : public cocos2d::Layer, Visible, LabelCreator{
public:
  MenuScene();
  ~MenuScene();
  static cocos2d::Scene* createScene();
  virtual bool init();   
  
  CREATE_FUNC(MenuScene);
  
  void PauseMusic(float dt);
  void ResumeMusic(float dt);    
  void Play(Ref *pSender);
  void Highscores(Ref *pSender);
  void menuCloseCallback(cocos2d::Ref* pSender);
private:
  MenuItemCreator CMenuItem;
  cocos2d::Sprite *coverSprite;  

  cocos2d::EventListenerTouchOneByOne *touchListener;
  void addCoverSprite(cocos2d::Sprite *sprite, const std::string &pathToCoverIMG, int localZOrder);
};

#endif // __MENU_SCENE_H__
