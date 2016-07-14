#include "ScoresScene.h"

USING_NS_CC;

Scene* ScoresScene::createScene(){
  auto scene = Scene::create();
  auto layer = ScoresScene::create();
  scene->addChild(layer);
  return scene;
}
bool ScoresScene::init(){
  if(!Layer::init()){ return false; }

  cocos2d::Size visibleSize(Director::getInstance()->getVisibleSize());
  cocos2d::Point origin(Director::getInstance()->getVisibleOrigin());

  titleLabel.color = cocos2d::Color3B(236, 54, 49);
  titleLabel.position = cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - TITLE_LABEL_FONT_SIZE);
  
  titleLabel.addLabelTTF(titleLabel.label, "Nice Game!\nYour Score: ", TITLE_LABEL_FONT_PATH, TITLE_LABEL_FONT_SIZE, titleLabel.color, titleLabel.position);
  this->addChild(titleLabel.label, 1);

  /*auto labelScoreNum = Label::createWithTTF("Nice Game!\nYour Score: ", "fonts/Marker Felt.ttf", 32);
  labelScoreNum -> setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
  this->addChild(labelScoreNum, 1);*/
  
  menuItem.push_back(MenuItemCreator(MenuItemFont::create("GoBackToMenu", CC_CALLBACK_1(ScoresScene::goBackToMenu, this))));
  menuItem.back().setColorItem(cocos2d::Color3B(105, 138, 26));

  menuItem.push_back(MenuItemCreator(MenuItemFont::create("Highscores", CC_CALLBACK_1(ScoresScene::highscores, this))));
  menuItem.back().setColorItem(cocos2d::Color3B(105, 138, 26));
      
  auto *myMenu = Menu::create(menuItem[0].item, menuItem[1].item, NULL);
  myMenu -> setPosition(Point(visibleSize.width / 2, 50));
  myMenu -> alignItemsVertically();
  this -> addChild(myMenu);

  auto textField = ui::TextField::create("Enter You Name", "Arial", 24);
    
  textField -> addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){});

  //textField -> addEventListener(CC_CALLBACK_2(ScoresScene::textFieldHandler, this));

  textField -> setMaxLengthEnabled(true);
  textField -> setMaxLength(20);
  textField -> setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

  this->addChild(textField);
  return true;
}

void ScoresScene::goBackToMenu(cocos2d::Ref *pSender){
  Director::getInstance()->startAnimation();
  auto scene = MenuScene::createScene();
  Director::getInstance() -> pushScene(TransitionFade::create(0.5f, scene));
}
void ScoresScene::highscores(cocos2d::Ref *pSender){
  auto scene = HighscoresScene::createScene();
  cocos2d::Director::getInstance()->pushScene(cocos2d::TransitionFade::create(0.5f, scene));
}