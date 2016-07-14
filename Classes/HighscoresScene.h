#ifndef __HIGHSCORES_SCENE_H__
#define __HIGHSCORES_SCENE_H__

#include "MenuScene.h"
#include "Defines.h"
#include "InterfaceCreator.h"

class HighscoresScene : public cocos2d::Layer{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  CREATE_FUNC(HighscoresScene);
    
  LabelCreator titleLabel;
  ScoreCreator score;
  MenuItemCreator menuItem;
  ScrollCreator scroll;

  void goBackToMenu(cocos2d::Ref *pSender);
};

#endif // __HIGHSCORES_SCENE_H__
