#ifndef __HIGHSCORES_SCENE_H__
#define __HIGHSCORES_SCENE_H__

#include "MenuScene.h"
#include "cocos2d.h"
#include <string.h>
#include "ui\UIListView.h"

struct Score{
  Score();
  ~Score();
  Score(const char name[], const unsigned int score);
  char name[20];
  unsigned int score;
};
class ScrollCreator{
public:
  cocos2d::ui::ScrollView *scrollView;

  void addScroll();
  void addLabelToScrollView(cocos2d::Vector<cocos2d::Label*> label);
};
class ScoreCreator : public ScrollCreator{
public:
  std::vector<Score> vScore;
  cocos2d::Vector<cocos2d::Label*> buildScoreToLabel(unsigned int index);
};
class HighscoresScene : public cocos2d::Layer, Visible, LabelCreator, ScrollCreator{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HighscoresScene);
    
    ScoreCreator CScore;
    MenuItemCreator CMenuItem;
    ScrollCreator CScroll;
    
    void GoBackToMenu(Ref *pSender);
};

#endif // __HIGHSCORES_SCENE_H__
