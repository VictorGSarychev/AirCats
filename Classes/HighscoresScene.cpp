#include "HighscoresScene.h"
#include "ScoresScene.h"
#include "MenuScene.h"

USING_NS_CC;

Score::Score(const char name[], const unsigned int score){
  strcpy(this -> name, name);
  this -> score = score;
}
Score::Score(){}
Score::~Score(){}

Scene* HighscoresScene::createScene(){
  auto scene = Scene::create();
  auto layer = HighscoresScene::create();
  scene->addChild(layer);
  return scene;
}
bool HighscoresScene::init(){
  if(!Layer::init()){ return false; }
    
#pragma region TITLE_LABEL  
  LabelCreator::color_titleLabel = cocos2d::Color3B(255, 255, 255);
  LabelCreator::position_titleLabel = cocos2d::Vec2(Visible::getOrigin().x + Visible::getVisibleSize().width / 2, Visible::getOrigin().y + Visible::getVisibleSize().height - TITLE_LABEL_FONT_SIZE);
  
  LabelCreator::addLabelTTF(LabelCreator::titleLabel, "Highscores", TITLE_LABEL_FONT_PATH, TITLE_LABEL_FONT_SIZE, color_titleLabel, position_titleLabel);
  this->addChild(LabelCreator::titleLabel, 1);
#pragma endregion  
  CScore.vScore.push_back(Score("eXis_K", 12));
  CScore.vScore.push_back(Score("Nice", 14));
  CScore.vScore.push_back(Score("Nice2", 11));
  CScore.vScore.push_back(Score("Nice1", 18));
#pragma region SCROLL_VIEW
  CScroll.addScroll();   
  for(unsigned int i = 0; i < CScore.vScore.size(); i++){
    cocos2d::Vector<cocos2d::Label*> label = CScore.buildScoreToLabel(i);
    CScroll.addLabelToScrollView(label);
  }    
  this->addChild(CScroll.scrollView);
#pragma endregion
#pragma region MENU_ITEM
  CMenuItem.menuItems.pushBack(MenuItemFont::create("GoBackToMenu", CC_CALLBACK_1(HighscoresScene::GoBackToMenu, this)));
  
  CMenuItem.colorMenuItems = cocos2d::Color3B(105, 138, 26);
  CMenuItem.setColorAllMenuItemFont(CMenuItem.menuItems, CMenuItem.colorMenuItems);
  
  auto myMenu = Menu::create(CMenuItem.menuItems.at(0), NULL);
  myMenu -> setPosition(Point(Visible::getVisibleSize().width / 2, 60));
  //myMenu->alignItemsVertically();
  this->addChild(myMenu, 1);
#pragma endregion
  
  return true;
}
void HighscoresScene::GoBackToMenu(cocos2d::Ref *pSender){
  auto scene = MenuScene::createScene();
  Director::getInstance()->pushScene(TransitionFade::create(0.5f, scene));
}
void ScrollCreator::addScroll(){
  scrollView = ui::ScrollView::create();
  scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
  scrollView->setContentSize(Size(Visible::getVisibleSize().width - 20.0f, Visible::getVisibleSize().height / 1.5f));
  scrollView->setInnerContainerSize(Size(Visible::getVisibleSize().width - 20.0f, 1100));
  scrollView->setBounceEnabled(true);
  scrollView->setAnchorPoint(Point(0.5f, 0.5f));
  scrollView->setPosition(Point(Visible::getVisibleSize().width / 2 + Visible::getOrigin().x, Visible::getVisibleSize().height / 2 + Visible::getOrigin().y));
}
void ScrollCreator::addLabelToScrollView(cocos2d::Vector<cocos2d::Label*> label){
  scrollView->addChild(label.at(0), 1);
  scrollView->addChild(label.at(1), 1);
  scrollView->addChild(label.at(2), 1);
}
cocos2d::Vector<cocos2d::Label*> ScoreCreator::buildScoreToLabel(unsigned int index){
  __String * sNumList = __String::createWithFormat("%i", index + 1);
  __String *sScore    = __String::createWithFormat("%i", vScore[index].score);

  cocos2d::Vector<cocos2d::Label*> labels;
  labels.pushBack(Label::createWithTTF(sNumList -> getCString(), "fonts/Marker Felt.ttf", 20));
  labels.pushBack(Label::createWithTTF(vScore[index].name, "fonts/Marker Felt.ttf", 20));
  labels.pushBack(Label::createWithTTF(sScore -> getCString(), "fonts/Marker Felt.ttf", 20));

  labels.at(0)->setPosition(Point(40,  1070 - index * 30));
  labels.at(1)->setPosition(Point(80,  1070 - index * 30));
  labels.at(2)->setPosition(Point(300, 1070 - index * 30));
  
  return labels;
}