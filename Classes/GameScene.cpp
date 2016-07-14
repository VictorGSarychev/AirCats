#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene(){
  auto scene = Scene::create();
  auto layer = GameScene::create();
  scene->addChild(layer);
  return scene;
}
bool GameScene::init(){
  if(!Layer::init()){ return false; }
    
  cocos2d::Size visibleSize(Director::getInstance()->getVisibleSize());
  cocos2d::Point origin(Director::getInstance()->getVisibleOrigin());

  score = 0;
  pauseGameFlag = false;

  cocos2d::Sprite *spriteBG = cocos2d::Sprite::create("bg.png");
  spriteBG->setPosition(Vec2(0, 0));
  this->addChild(spriteBG, 0);
 
  //Title label
  timer.color = cocos2d::Color3B(236, 54, 49);
  timer.position = cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - TITLE_LABEL_FONT_SIZE);
  timer.addLabelTTF(timer.label, "Start Game", TITLE_LABEL_FONT_PATH, TIMER_LABEL_FONT_SIZE, timer.color, timer.position);
  this->addChild(timer.label, 1);
  //Score label
  scoreTitle.color = cocos2d::Color3B(236, 54, 49);
  scoreTitle.position = cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - TITLE_LABEL_FONT_SIZE * 2);
  scoreTitle.addLabelTTF(scoreTitle.label, "Score: ", TITLE_LABEL_FONT_PATH, TIMER_LABEL_FONT_SIZE, scoreTitle.color, scoreTitle.position);
  this->addChild(scoreTitle.label, 1);
  //Score_num label
  scoreNum.color = cocos2d::Color3B(236, 54, 49);
  scoreNum.position = cocos2d::Vec2(origin.x + visibleSize.width / 2 + 100, origin.y + visibleSize.height - TITLE_LABEL_FONT_SIZE * 2);
  scoreNum.addLabelTTF(scoreNum.label, "0", TITLE_LABEL_FONT_PATH, TIMER_LABEL_FONT_SIZE, scoreNum.color, scoreNum.position);
  this->addChild(scoreNum.label, 1);

  menuItem.push_back(MenuItemCreator(MenuItemFont::create("GoBackToMenu", CC_CALLBACK_1(GameScene::goBackToMenu, this))));
  menuItem.back().setColorItem(cocos2d::Color3B(105, 138, 26));

  menuItem.push_back(MenuItemCreator(MenuItemFont::create("Pause", CC_CALLBACK_1(GameScene::pauseGame, this))));
  menuItem.back().setColorItem(cocos2d::Color3B(105, 138, 26));

  auto *myMenu = Menu::create(menuItem[0].item, menuItem[1].item, NULL);
  myMenu -> setPosition(Point(visibleSize.width / 2, 50));
  myMenu -> alignItemsVertically();
  this -> addChild(myMenu);

  for(unsigned int i = 0; i < COUNT_CATS_TO_LAYER; i++){
    balloon.push_back(GameObject());
    cat.push_back(GameObject());
    GameObject balloonObj = balloon.back();
    GameObject catObj = cat.back();

    balloonObj.nameFileSprite = genRandNumToNameFile(FILE_NAME_SPRITE_FILE_BALLOON, COUNT_SPRITE_FILE_BALLOON, FORMAT_SPRITE_FILE);
    catObj.nameFileSprite = genRandNumToNameFile(FILE_NAME_SPRITE_FILE_CAT, COUNT_SPRITE_FILE_CAT, FORMAT_SPRITE_FILE);

    balloonObj.startSpritePosition = cocos2d::Point(rand() % 405, -300 + ((150 / 2) * SCALE_BALLOON_SPRITE));
    catObj.startSpritePosition = cocos2d::Point(rand() % 405, -300);

    GameLogic::initSprite(balloonObj, balloonObj.nameFileSprite, SCALE_BALLOON_SPRITE, balloonObj.startSpritePosition);
    GameLogic::initSprite(catObj, catObj.nameFileSprite, SCALE_CAT_SPRITE, catObj.startSpritePosition);

    this->addChild(balloonObj.sprite);
    this->addChild(catObj.sprite);

    delayAction = getDelayAction(RANDOM_DELAY_TIME_SEQUENCE);

    catObj.actionPosition = cocos2d::Point(rand() % 405, 900 + ((150 / 2) * SCALE_BALLOON_SPRITE));
    balloonObj.actionPosition = cocos2d::Point(rand() % 405, 900);
      
    GameLogic::initAction(balloonObj, balloonObj.actionPosition, delayAction, DURATION_GAME_OBJ_ACTION);
    GameLogic::initAction(catObj, catObj.actionPosition, delayAction, DURATION_GAME_OBJ_ACTION);
    
    balloonObj.sprite->runAction(balloonObj.action);
    catObj.sprite->runAction(catObj.action);


    balloonObj.listener = cocos2d::EventListenerTouchOneByOne::create();
    balloonObj.listener->setSwallowTouches(true);
    //catObj.listener->setSwallowTouches(true);
    balloonObj.listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    //catObj.listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(balloonObj.listener, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(catObj.listener, this);

    //cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(balloonObj.listener, 30);
  }
  
  time = DURATION_TIME_ONE_LAYER;
  this->schedule(schedule_selector(GameScene::TimerMehod), 0.01f);


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
  timer.label->setString(timeToDisplay->getCString());

  if(time < 0.1){
    auto scene = ScoresScene::createScene();

    Director::getInstance()->pushScene(TransitionFade::create(0.5f, scene));
  }
}
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
  ////getContentSize();
  //if(!pauseGame){
  //  this->stopAllActions();
  //  auto action = MoveTo::create(1.2f, Point(this->getPosition().x, -100));
  //  //sprite[0].at(i)->setPosition(Point(-100, -100));
  //  this->runAction(action);
  //  
    
  //}

  //return true;
  auto target = static_cast<Sprite*>(event->getCurrentTarget());

  //Get the position of the current point relative to the button
  Point locationInNode = target->convertToNodeSpace(touch->getLocation());
  Size s = target->getContentSize();
  Rect rect = Rect(0, 0, s.width, s.height);

  //Check the click area
  if (rect.containsPoint(locationInNode))
  {
      log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
      target->setOpacity(180);
      score++;
      __String *scoreToDisplay = __String::createWithFormat("%i", score);
      scoreNum.label->setString(scoreToDisplay->getCString());
      return true;
  }
  return false;
}
std::string GameLogic::genRandNumToNameFile(const std::string &pathToFileModel, int randRange, const std::string &formatFile){
  std::string pathAndNameFileModel;
  
  pathAndNameFileModel += pathToFileModel;
  pathAndNameFileModel += cocos2d::__String::createWithFormat("%i", rand() % randRange + 1)->getCString();
  pathAndNameFileModel += ".";
  pathAndNameFileModel += formatFile;

  return pathAndNameFileModel;
}
cocos2d::Sprite* GameLogic::createSpriteUsingPolygon(const std::string fileName){
  cocos2d::PolygonInfo pInfoModel = AutoPolygon::generatePolygon(fileName);
  
  return Sprite::create(pInfoModel);
}
cocos2d::Sprite* GameLogic::initSprite(GameObject &obj, std::string &fileName, float scaleSprite, cocos2d::Point position){
  obj.sprite = createSpriteUsingPolygon(fileName);

  obj.sprite->setPosition(position);
  obj.sprite->setScale(scaleSprite);

  return obj.sprite;
}
cocos2d::DelayTime* GameLogic::getDelayAction(int range){
  return cocos2d::DelayTime::create(rand() % rand() % range);
}
cocos2d::Action* GameLogic::initAction(GameObject &obj, cocos2d::Point position, cocos2d::DelayTime *delay, const float duration){
  cocos2d::Action *action = cocos2d::MoveTo::create(duration, position);
  obj.action = Sequence::create(delay, action, NULL);
  
  return obj.action;
}
GameObject::GameObject(){
  this->sprite = NULL;
  this->action = NULL;
  this->startSpritePosition = cocos2d::Point(0,0);
  this->actionPosition = cocos2d::Point(0,0);
  this->nameFileSprite = "";
}
void GameScene::pauseGame(cocos2d::Ref *pSender){
  /*if(!pauseGame){
    for(unsigned int i = 0; i < balloon.size(); i++){
      cocos2d::Director::getInstance()->getActionManager()->pauseTarget(balloon[i].sprite);
    }
    for(unsigned int i = 0; i < cat.size(); i++){
      cocos2d::Director::getInstance()->getActionManager()->pauseTarget(cat[i].sprite);
    }
  } else {
    for(unsigned int i = 0; i < balloon.size(); i++){
      cocos2d::Director::getInstance()->getActionManager()->resumeTarget(balloon[i].sprite);
    }
    for(unsigned int i = 0; i < cat.size(); i++){
      cocos2d::Director::getInstance()->getActionManager()->resumeTarget(cat[i].sprite);
    }
  }
  pauseGame = !pauseGame;*/
}
void GameScene::goBackToMenu(cocos2d::Ref *pSender){
  Director::getInstance()->startAnimation();
  auto scene = MenuScene::createScene();
  Director::getInstance() -> pushScene(TransitionFade::create(0.5f, scene));
}