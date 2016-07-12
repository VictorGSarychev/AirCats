#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "MenuScene.h"
#include "cocos2d.h"
#include <vector>
#include <string.h>

class GameScene : public cocos2d::Layer, Visible, LabelCreator{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    cocos2d::Vector<cocos2d::Sprite*> sprite[2];
    cocos2d::Vector<cocos2d::Sequence*> action[2];
    unsigned int score;
    float scaleModel;
    bool pauseGame;
    cocos2d::Label *timerTabel;
    cocos2d::Label *labelScoreScore;
    cocos2d::Label *labelScoreNum;
    float time;
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void TimerMehod(float dt);
    void GoBackToMenu(Ref *pSender);
    void Pause(Ref *pSender);
};

#endif // __GAME_SCENE_H__
