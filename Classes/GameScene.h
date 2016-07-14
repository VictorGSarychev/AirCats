#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ScoresScene.h"
#include "InterfaceCreator.h"

#include <vector>
#include <string.h>

struct GameObject{
  GameObject();

  std::string nameFileSprite;
  cocos2d::EventListenerTouchOneByOne *listener;
  cocos2d::Sprite *sprite;
  cocos2d::Action *action;
  cocos2d::Point startSpritePosition;
  cocos2d::Point actionPosition;
};
class GameLogic{
public:
  /**
   * @pathToFileModel path to file of model and name file model without numeric ending of the word
   * @randRange range random
   * @randRange format of the file model
   */
  std::string genRandNumToNameFile(const std::string &pathToFileModel, int randRange, const std::string &formatFile);
  cocos2d::Sprite* createSpriteUsingPolygon(const std::string fileName);

  cocos2d::Sprite* initSprite(GameObject &obj, std::string &fileName, float scaleSprite, cocos2d::Point position);
  cocos2d::Action* initAction(GameObject &obj, cocos2d::Point position, cocos2d::DelayTime *delay, const float duration);
  cocos2d::DelayTime* getDelayAction(int range);  
  cocos2d::DelayTime *delayAction;
};
class GameScene : public cocos2d::Layer, GameLogic{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
    
  CREATE_FUNC(GameScene);
    
  unsigned int score;
  bool pauseGameFlag;
  LabelCreator timer;
  LabelCreator scoreTitle;
  LabelCreator scoreNum;
  std::vector<MenuItemCreator> menuItem;
  float time;
    
  bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
  void TimerMehod(float dt);
  
  std::vector<GameObject> balloon;
  std::vector<GameObject> cat;

  void pauseGame(cocos2d::Ref *pSender);
  void goBackToMenu(cocos2d::Ref *pSender);
};

#endif // __GAME_SCENE_H__
