#pragma once
#include "cocos2d.h"
#include <string>


class GameOver : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameOver);

    int playID;

    void Play(Ref* pSender);
    void Highscores(Ref* pSender);
    void Settings(Ref* pSender);

    void PlayButton(Ref* Sender);
    std::string scoreS;
};