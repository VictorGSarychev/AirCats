#ifndef __SCORES_SCENE_H__
#define __SCORES_SCENE_H__

#include "MenuScene.h"

class ScoresScene : public cocos2d::Layer{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  
  CREATE_FUNC(ScoresScene);

  LabelCreator titleLabel;
  std::vector<MenuItemCreator> menuItem;

  void goBackToMenu(cocos2d::Ref *pSender);
  void highscores(cocos2d::Ref *pSender);
};

#endif // __SCORES_SCENE_H__
