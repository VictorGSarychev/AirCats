#include "ScoresScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene(){
  auto scene = Scene::create();
  auto layer = GameScene::create();
  scene->addChild(layer);
  return scene;
}
bool GameScene::init(){
  if(!Layer::init()){ return false; }
    
  score = 0;
  scaleModel = 0.5f;
  pauseGame = false;

  cocos2d::Sprite *spriteBG = cocos2d::Sprite::create("bg.png");
  spriteBG->setPosition(Vec2(0, 0));
  this->addChild(spriteBG, 0);

#pragma region TITLE_LABEL  
  //Title label
  LabelCreator::color_titleLabel = cocos2d::Color3B(255, 255, 255);
  LabelCreator::position_titleLabel = cocos2d::Vec2(Visible::getOrigin().x + Visible::getVisibleSize().width / 2, Visible::getOrigin().y + Visible::getVisibleSize().height - TIMER_LABEL_FONT_SIZE);
  LabelCreator::addLabelTTF(timerTabel, "Start Game", TITLE_LABEL_FONT_PATH, TIMER_LABEL_FONT_SIZE, color_titleLabel, position_titleLabel);
  this->addChild(timerTabel, 1);
  //Score label
  LabelCreator::position_titleLabel = cocos2d::Vec2(Visible::getOrigin().x + (Visible::getVisibleSize().width / 2) - 50, 20);
  LabelCreator::addLabelTTF(labelScoreScore, "Score: ", TITLE_LABEL_FONT_PATH, TIMER_LABEL_FONT_SIZE, color_titleLabel, position_titleLabel);
  this->addChild(labelScoreScore, 1);
  //Score_num label
  LabelCreator::position_titleLabel = cocos2d::Vec2(Visible::getOrigin().x + (Visible::getVisibleSize().width / 2) + 20, 20);
  LabelCreator::addLabelTTF(labelScoreNum, "0", TITLE_LABEL_FONT_PATH, TIMER_LABEL_FONT_SIZE, color_titleLabel, position_titleLabel);
  this->addChild(labelScoreNum, 1);
#pragma endregion

  auto menu_item_1 = MenuItemFont::create("GoBackToMenu", CC_CALLBACK_1(GameScene::GoBackToMenu, this));
  auto menu_item_2 = MenuItemFont::create("Pause", CC_CALLBACK_1(GameScene::Pause, this));
    
  auto *myMenu = Menu::create(menu_item_1, menu_item_2, NULL);
  myMenu -> setPosition(Point(Visible::getVisibleSize().width / 2, 50));
  myMenu -> alignItemsVertically();
  this -> addChild(myMenu);

  for(int i = 0; i < 40; i++){
      
    char nameFileModel00[256];
    char nameFileModel01[256];
    strcpy(nameFileModel00, "model/balloon0");
    strcpy(nameFileModel01, "model/cat0");
    char num[256];      

    sprintf(num, "%d", rand() % 6 + 1);
    strcat(nameFileModel00, num);
    strcat(nameFileModel00, ".png");
      
    sprintf(num, "%d", rand() % 4 + 1);
    strcat(nameFileModel01, num);
    strcat(nameFileModel01, ".png");

    auto pinfoModel00 = AutoPolygon::generatePolygon(nameFileModel00);
    auto pinfoModel01 = AutoPolygon::generatePolygon(nameFileModel01);
    sprite[0].pushBack(Sprite::create(pinfoModel00));
    sprite[1].pushBack(Sprite::create(pinfoModel01));

    Point startPosition(rand() % 405, -300);
    sprite[0].at(sprite[0].size() - 1)->setPosition(startPosition.x, startPosition.y + ((150 / 2) * scaleModel));
    sprite[1].at(sprite[1].size() - 1)->setPosition(startPosition);
    sprite[0].at(sprite[0].size() - 1)->setScale(scaleModel);
    sprite[1].at(sprite[1].size() - 1)->setScale(scaleModel);

    this -> addChild(sprite[0].at(sprite[0].size() - 1));
    this -> addChild(sprite[1].at(sprite[1].size() - 1));

    DelayTime *delayAction = DelayTime::create(rand() % rand() % 40);

    Point actionEndPosition(rand() % 405, 900);
      
    action[0].pushBack(Sequence::create(delayAction, MoveTo::create(5, Point(actionEndPosition.x, actionEndPosition.y + ((150 / 2) * scaleModel))), NULL));
    action[1].pushBack(Sequence::create(delayAction, MoveTo::create(5, actionEndPosition), NULL));
    sprite[0].at(sprite[0].size() - 1)->runAction(action[0].at(action[0].size() - 1));
    sprite[1].at(sprite[1].size() - 1)->runAction(action[1].at(action[1].size() - 1));
  }
  
  auto listener = EventListenerTouchOneByOne::create();
  listener -> setSwallowTouches(true);
  listener -> onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
  _eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
  
  time = 40.0f;
  this->schedule(schedule_selector(GameScene::TimerMehod), 0.01);


//// now lets animate the sprite we moved
//Vector<SpriteFrame*> animFrames;
//animFrames.reserve(12);
//animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0,0,65,81)));
//animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0,0,65,81)));

//// create the animation out of the frames
//Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
//Animate* animate = Animate::create(animation);

//// run it and repeat it forever
//mySprite->runAction(RepeatForever::create(animate));
  return true;
}
void GameScene::TimerMehod(float dt){
  time -= dt;
  __String *timeToDisplay = __String::createWithFormat("%.1f", time);
  timerTabel -> setString(timeToDisplay -> getCString());

  if(time < 0.1){
    auto scene = ScoresScene::createScene();

    Director::getInstance() -> pushScene(TransitionFade::create(0.5f, scene));
  }
}
void GameScene::GoBackToMenu(cocos2d::Ref *pSender){
  Director::getInstance()->startAnimation();
  auto scene = MenuScene::createScene();
  Director::getInstance() -> pushScene(TransitionFade::create(0.5f, scene));
}
void GameScene::Pause(cocos2d::Ref *pSender){
  if(!pauseGame){
    for(unsigned int i = 0; i < sprite[0].size(); i++){
      Director::getInstance()->getActionManager()->pauseTarget(sprite[0].at(i));
      Director::getInstance()->getActionManager()->pauseTarget(sprite[1].at(i));
    }
  } else {
    for(unsigned int i = 0; i < sprite[0].size(); i++){
      Director::getInstance()->getActionManager()->resumeTarget(sprite[0].at(i));
      Director::getInstance()->getActionManager()->resumeTarget(sprite[1].at(i));
    } 
  }
  pauseGame = !pauseGame;
}
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
  //getContentSize();
  if(!pauseGame){
    for(unsigned int i = 0; i < sprite[0].size(); i++){
      Point spritePosition = sprite[0].at(i) -> getPosition();
      if(touch -> getLocation().x >= spritePosition.x - ((150 / 2) * scaleModel) &&
         touch -> getLocation().x <= spritePosition.x + ((150 / 2) * scaleModel) &&
         touch -> getLocation().y >= spritePosition.y &&
         touch -> getLocation().y <= spritePosition.y + ((160 / 2) * scaleModel)){
        sprite[0].at(i)->stopAllActions();
        sprite[1].at(i)->stopAllActions();
      
        auto action = MoveTo::create(1.2f, Point(sprite[0].at(i) -> getPosition().x, -100));
        sprite[0].at(i)->setPosition(Point(-100, -100));
        sprite[1].at(i)->runAction(action);

        score++;
      }
    }  
  }

  __String *scoreToDisplay = __String::createWithFormat("%i", score);
  labelScoreNum -> setString(scoreToDisplay -> getCString());

  return true;
}