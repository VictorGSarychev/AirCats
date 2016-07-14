#include "MenuScene.h"

USING_NS_CC;

Scene* MenuScene::createScene(){
  auto scene = Scene::create();
  auto layer = MenuScene::create();
  scene->addChild(layer);

  return scene;
}

bool MenuScene::init(){
  if(!Layer::init()){ return false; }
    
  cocos2d::Size visibleSize(Director::getInstance()->getVisibleSize());
  cocos2d::Point origin(Director::getInstance()->getVisibleOrigin());

  addCoverSprite(coverSprite, COVER_IMG_PATH, 0);

  titleLabel.color = cocos2d::Color3B(236, 54, 49);
  titleLabel.position = cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - TITLE_LABEL_FONT_SIZE);
  
  titleLabel.addLabelTTF(titleLabel.label, "Air Cats", TITLE_LABEL_FONT_PATH, TITLE_LABEL_FONT_SIZE, titleLabel.color, titleLabel.position);
  this->addChild(titleLabel.label, 1);

  /*CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/mainMusic.mp3");
  CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/mainMusic.mp3", true);
  CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);*/
  
  menuItem.push_back(MenuItemCreator(MenuItemFont::create("Play", CC_CALLBACK_1(MenuScene::play, this))));
  menuItem.back().setColorItem(cocos2d::Color3B(105, 138, 26));
  menuItem.push_back(MenuItemCreator(MenuItemFont::create("Highscores", CC_CALLBACK_1(MenuScene::highscores, this))));
  menuItem.back().setColorItem(cocos2d::Color3B(105, 138, 26));
  menuItem.push_back(MenuItemCreator(MenuItemFont::create("Close", CC_CALLBACK_1(MenuScene::menuCloseCallback, this))));
  menuItem.back().setColorItem(cocos2d::Color3B(105, 138, 26));  
  
  auto myMenu = Menu::create(menuItem[0].item, menuItem[1].item, menuItem[2].item, NULL);
  myMenu->alignItemsVertically();
  this->addChild(myMenu, 1);
      
  return true;
}
void MenuScene::pauseMusic(float dt){
  CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void MenuScene::resumeMusic(float dt){
  CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
void MenuScene::addCoverSprite(cocos2d::Sprite *sprite, const std::string &pathToCoverIMG, int localZOrder){
  cocos2d::Size visibleSize(Director::getInstance()->getVisibleSize());
  cocos2d::Point origin(Director::getInstance()->getVisibleOrigin());

  sprite = cocos2d::Sprite::create(pathToCoverIMG);
  sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
  this->addChild(sprite, localZOrder);
}
void MenuScene::play(cocos2d::Ref *pSender){
  auto scene = GameScene::createScene();
  cocos2d::Director::getInstance()->pushScene(cocos2d::TransitionFade::create(0.5f, scene));
}
void MenuScene::highscores(cocos2d::Ref *pSender){
  auto scene = HighscoresScene::createScene();
  cocos2d::Director::getInstance()->pushScene(cocos2d::TransitionFade::create(0.5f, scene));
}
void MenuScene::menuCloseCallback(cocos2d::Ref* pSender){
  cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}