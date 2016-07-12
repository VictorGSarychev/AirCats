#ifndef __SCORES_SCENE_H__
#define __SCORES_SCENE_H__

#include "MenuScene.h"
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <iostream>

class ScoresScene : public cocos2d::Layer, Visible{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  void menuCloseCallback(cocos2d::Ref* pSender);
  
  CREATE_FUNC(ScoresScene);

  cocos2d::Sprite *spriteArrow;
  
  void GoBackToMenu(Ref *pSender);
  void Highscores(Ref *pSender);

  //void textFieldHandler(ui::TextField *sender, ui::TextField::EventType type);
};

#endif // __SCORES_SCENE_H__
