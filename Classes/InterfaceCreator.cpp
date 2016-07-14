#include "InterfaceCreator.h"

void LabelCreator::addLabelTTF(cocos2d::Label* &label, const std::string &initText, const std::string &fontFilePath, const float fontSize, cocos2d::Color3B color, cocos2d::Point position){
  label = cocos2d::Label::createWithTTF(initText, fontFilePath, fontSize);    
  label->setColor(color);
  label->setPosition(position);
}
MenuItemCreator::MenuItemCreator(cocos2d::MenuItemFont *item){
  this->item = item;
}
void MenuItemCreator::setColorItem(cocos2d::Color3B color){
  this->colorItem = color;
  this->item->setColor(this->colorItem);
}
void ScrollCreator::addLabelToScrollView(cocos2d::Vector<cocos2d::Label*> label){
  scrollView->addChild(label.at(0), 1);
  scrollView->addChild(label.at(1), 1);
  scrollView->addChild(label.at(2), 1);
}
cocos2d::Vector<cocos2d::Label*> ScoreCreator::buildScoreToLabel(unsigned int index){
  cocos2d::__String *sNumList = cocos2d::__String::createWithFormat("%i", index + 1);
  cocos2d::__String *sScore    = cocos2d::__String::createWithFormat("%i", vScore[index].score);

  cocos2d::Vector<cocos2d::Label*> labels;
  labels.pushBack(cocos2d::Label::createWithTTF(sNumList->getCString(), "fonts/Marker Felt.ttf", 20));
  labels.pushBack(cocos2d::Label::createWithTTF(vScore[index].name, "fonts/Marker Felt.ttf", 20));
  labels.pushBack(cocos2d::Label::createWithTTF(sScore->getCString(), "fonts/Marker Felt.ttf", 20));

  labels.at(0)->setPosition(cocos2d::Point(40,  1070 - index * 30));
  labels.at(1)->setPosition(cocos2d::Point(80,  1070 - index * 30));
  labels.at(2)->setPosition(cocos2d::Point(300, 1070 - index * 30));
  
  return labels;
}
void ScrollCreator::addScroll(){
  cocos2d::Size visibleSize(cocos2d::Director::getInstance()->getVisibleSize());
  cocos2d::Point origin(cocos2d::Director::getInstance()->getVisibleOrigin());

  scrollView = cocos2d::ui::ScrollView::create();
  scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
  scrollView->setContentSize(cocos2d::Size(visibleSize.width - 20.0f, visibleSize.height / 1.5f));
  scrollView->setInnerContainerSize(cocos2d::Size(visibleSize.width - 20.0f, 1100));
  scrollView->setBounceEnabled(true);
  scrollView->setAnchorPoint(cocos2d::Point(0.5f, 0.5f));
  scrollView->setPosition(cocos2d::Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
}