#ifndef __INTERFACE_CREATOR_H__
#define __INTERFACE_CREATOR_H__

#include "cocos2d.h"
#include "ui\UIListView.h"
#include "ui\CocosGUI.h"

struct Score{
  Score(const char name[], const unsigned int score);
  char name[20];
  unsigned int score;
};
class LabelCreator{
public:
  cocos2d::Label *label;
  cocos2d::Color3B color;
  cocos2d::Vec2 position;
  void addLabelTTF(cocos2d::Label* &label, const std::string &initText, const std::string &fontFilePath, const float fontSize, cocos2d::Color3B color, cocos2d::Point position);
};
class MenuItemCreator{
public:
  cocos2d::Color3B colorItem;
  cocos2d::MenuItemFont* item;

  MenuItemCreator(){};
  MenuItemCreator(cocos2d::MenuItemFont *item);
  void setColorItem(cocos2d::Color3B color);
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

#endif // __INTERFACE_CREATOR_H__