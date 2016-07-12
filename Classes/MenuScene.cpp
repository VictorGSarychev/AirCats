#include "MenuScene.h"
#include "HighscoresScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

cocos2d::Size Visible::visibleSize;
cocos2d::Vec2 Visible::origin;

MenuScene::MenuScene(){
  
}

MenuScene::~MenuScene(){

}

Scene* MenuScene::createScene(){
  auto scene = Scene::create();
  auto layer = MenuScene::create();
  scene->addChild(layer);

  return scene;
}

bool MenuScene::init(){
  if(!Layer::init()){
    return false;
  }
    
  setVisibleSize(Director::getInstance()->getVisibleSize());
  setOrigin(Director::getInstance()->getVisibleOrigin());

  addCoverSprite(coverSprite, COVER_IMG_PATH, 0);

#pragma region TITLE_LABEL  
  LabelCreator::color_titleLabel = cocos2d::Color3B(236, 54, 49);
  LabelCreator::position_titleLabel = cocos2d::Vec2(Visible::getOrigin().x + Visible::getVisibleSize().width / 2, Visible::getOrigin().y + Visible::getVisibleSize().height - TITLE_LABEL_FONT_SIZE);
  
  addLabelTTF(LabelCreator::titleLabel, "Air Cats", TITLE_LABEL_FONT_PATH, TITLE_LABEL_FONT_SIZE, color_titleLabel, position_titleLabel);
  this->addChild(LabelCreator::titleLabel, 1);
#pragma endregion
#pragma region MAIN_MUSIC
  /*CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/mainMusic.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/mainMusic.mp3", true);
  CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);*/
#pragma endregion
#pragma region MENU_ITEM
  CMenuItem.menuItems.pushBack(MenuItemFont::create("Play", CC_CALLBACK_1(MenuScene::Play, this)));
  CMenuItem.menuItems.pushBack(MenuItemFont::create("Highscores", CC_CALLBACK_1(MenuScene::Highscores, this)));
  CMenuItem.menuItems.pushBack(MenuItemFont::create("Close", CC_CALLBACK_1(MenuScene::menuCloseCallback, this)));
  
  CMenuItem.colorMenuItems = cocos2d::Color3B(105, 138, 26);
  CMenuItem.setColorAllMenuItemFont(CMenuItem.menuItems, CMenuItem.colorMenuItems);
  
  auto myMenu = Menu::create(CMenuItem.menuItems.at(0), CMenuItem.menuItems.at(1), CMenuItem.menuItems.at(2), NULL);
  myMenu->alignItemsVertically();
  this->addChild(myMenu, 1);
#pragma endregion
      
  return true;
}
void MenuScene::PauseMusic(float dt){
  CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void MenuScene::ResumeMusic(float dt){
  CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void MenuScene::Play(cocos2d::Ref *pSender){
  auto scene = GameScene::createScene();
  Director::getInstance()->pushScene(TransitionFade::create(0.5f, scene));
}
void MenuScene::Highscores(cocos2d::Ref *pSender){
  auto scene = HighscoresScene::createScene();
  Director::getInstance()->pushScene(TransitionFade::create(0.5f, scene));
}
void MenuScene::menuCloseCallback(Ref* pSender){
  Director::getInstance()->end();

  #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}
void LabelCreator::addLabelTTF(cocos2d::Label* &label, const std::string &initText, const std::string &fontFilePath, const float fontSize, cocos2d::Color3B color, cocos2d::Point position){
  label = cocos2d::Label::createWithTTF(initText, fontFilePath, fontSize);    
  label->setColor(color);
  label->setPosition(position);
}
void MenuItemCreator::setColorAllMenuItemFont(cocos2d::Vector<cocos2d::MenuItemFont*> menuItems, cocos2d::Color3B color){
  for(unsigned int i = 0; i < menuItems.size(); i++){
    menuItems.at(i)->setColor(color);
  }
}
void MenuScene::addCoverSprite(cocos2d::Sprite *sprite, const std::string &pathToCoverIMG, int localZOrder){
  sprite = cocos2d::Sprite::create(pathToCoverIMG);
  sprite->setPosition(Vec2(Visible::getVisibleSize().width / 2 + Visible::getOrigin().x, Visible::getVisibleSize().height / 2 + Visible::getOrigin().y));
  this->addChild(sprite, localZOrder);
}