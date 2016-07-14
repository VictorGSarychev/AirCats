#include "HighscoresScene.h"

USING_NS_CC;

Score::Score(const char name[], const unsigned int score){
  strcpy(this -> name, name);
  this -> score = score;
}
Scene* HighscoresScene::createScene(){
  auto scene = Scene::create();
  auto layer = HighscoresScene::create();
  scene->addChild(layer);
  return scene;
}
bool HighscoresScene::init(){
  if(!Layer::init()){ return false; }
    
  cocos2d::Size visibleSize(Director::getInstance()->getVisibleSize());
  cocos2d::Point origin(Director::getInstance()->getVisibleOrigin());

  titleLabel.color = cocos2d::Color3B(236, 54, 49);
  titleLabel.position = cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - TITLE_LABEL_FONT_SIZE);
  
  titleLabel.addLabelTTF(titleLabel.label, "Highscores", TITLE_LABEL_FONT_PATH, TITLE_LABEL_FONT_SIZE, titleLabel.color, titleLabel.position);
  this->addChild(titleLabel.label, 1);
  
  score.vScore.push_back(Score("eXis_K", 12));
  score.vScore.push_back(Score("Nice", 14));
  score.vScore.push_back(Score("Nice2", 11));
  score.vScore.push_back(Score("Nice1", 18));
  scroll.addScroll();   
  
  for(unsigned int i = 0; i < score.vScore.size(); i++){
    cocos2d::Vector<cocos2d::Label*> label = score.buildScoreToLabel(i);
    scroll.addLabelToScrollView(label);
  }    
  this->addChild(scroll.scrollView);
  
  menuItem.item = MenuItemFont::create("GoBackToMenu", CC_CALLBACK_1(HighscoresScene::goBackToMenu, this));
  menuItem.setColorItem(cocos2d::Color3B(105, 138, 26));
    
  auto myMenu = Menu::create(menuItem.item, NULL);
  myMenu -> setPosition(Point(visibleSize.width / 2, 60));
  //myMenu->alignItemsVertically();
  this->addChild(myMenu, 1);
  
  return true;
}
void HighscoresScene::goBackToMenu(cocos2d::Ref *pSender){
  Director::getInstance()->startAnimation();
  auto scene = MenuScene::createScene();
  Director::getInstance() -> pushScene(TransitionFade::create(0.5f, scene));
}