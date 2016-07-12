#include "ScoresScene.h"
#include "MenuScene.h"
#include "HighscoresScene.h"

USING_NS_CC;

Scene* ScoresScene::createScene(){
  auto scene = Scene::create();
  auto layer = ScoresScene::create();
  scene->addChild(layer);
  return scene;
}
bool ScoresScene::init(){
  if(!Layer::init()){ return false; }
  auto label = Label::createWithTTF("Nice Game!\nYour Score: ", "fonts/Marker Felt.ttf", 32);
    
  label -> setPosition(Vec2(Visible::getOrigin().x + Visible::getVisibleSize().width/2,
                            Visible::getOrigin().y + Visible::getVisibleSize().height - label->getContentSize().height));
    
  this->addChild(label, 1);

  auto labelScoreNum = Label::createWithTTF("Nice Game!\nYour Score: ", "fonts/Marker Felt.ttf", 32);
  labelScoreNum -> setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
  this->addChild(labelScoreNum, 1);
  
  auto menu_item_1 = MenuItemFont::create("GoBackToMenu", CC_CALLBACK_1(ScoresScene::GoBackToMenu, this));
  auto menu_item_2 = MenuItemFont::create("Highscores", CC_CALLBACK_1(ScoresScene::Highscores, this));
    
  auto *myMenu = Menu::create(menu_item_1, menu_item_2, NULL);
  myMenu -> setPosition(Point(Visible::getVisibleSize().width / 2, 50));
  myMenu -> alignItemsVertically();
  this -> addChild(myMenu);

  auto textField = ui::TextField::create("Enter You Name", "Arial", 24);
    
  textField -> addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
              std::cout << "editing a TextField" << std::endl;
  });

  //textField -> addEventListener(CC_CALLBACK_2(ScoresScene::textFieldHandler, this));

  textField -> setMaxLengthEnabled(true);
  textField -> setMaxLength(20);
  textField -> setPosition(Point(Visible::getVisibleSize().width / 2, Visible::getVisibleSize().height / 2));

  this->addChild(textField);
  return true;
}
//void ScoresScene::textFieldHandler(ui::TextField *sender, ui::TextField::EventType type) {
  //sender -> 
//}
void ScoresScene::GoBackToMenu(cocos2d::Ref *pSender){
  auto scene = MenuScene::createScene();
  Director::getInstance() -> pushScene(TransitionFade::create(0.5f, scene));
}
void ScoresScene::Highscores(cocos2d::Ref *pSender){
  auto scene = HighscoresScene::createScene();
  Director::getInstance() -> pushScene(TransitionFade::create(0.5f, scene));
}