#pragma once
#include "cocos2d.h"



class Controles : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Controles);

    /*void Play(Ref* pSender);
    void Highscores(Ref *pSender);
    void Settings(Ref *pSender);*/

    void Regresar(Ref* Sender);
    
    int musica;


private:
    cocos2d::Sprite* _Start1;
    cocos2d::Sprite* _Start2;

};


