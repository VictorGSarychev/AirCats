#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "Defines.h"
#include "InterfaceCreator.h"
#include "SimpleAudioEngine.h"
#include "HighscoresScene.h"
#include "GameScene.h"

class MenuScene : public cocos2d::Layer{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();   
  
  CREATE_FUNC(MenuScene);
  
  void pauseMusic(float dt);
  void resumeMusic(float dt);  
private:
  LabelCreator titleLabel;
  std::vector<MenuItemCreator> menuItem;
  cocos2d::Sprite *coverSprite;

  cocos2d::EventListenerTouchOneByOne *touchListener;
  void addCoverSprite(cocos2d::Sprite *sprite, const std::string &pathToCoverIMG, int localZOrder);

  void play(cocos2d::Ref *pSender);
  void highscores(cocos2d::Ref *pSender);
  void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif // __MENU_SCENE_H__
