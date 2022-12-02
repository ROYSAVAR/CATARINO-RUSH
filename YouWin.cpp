#include "YouWin.h"
#include "MenuJuego.h"
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* YouWin::createScene()
{
    auto scene = Scene::create();
    auto layer = YouWin::create();
    scene->addChild(layer);
    return scene;
}

bool YouWin::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //crear un label 
    auto crecer = ScaleBy::create(3, 2);  //ScaleBy nos hace crecer cosas recibe tiempo y veces que crece
    auto aparecer = FadeIn::create(3); //Hara que aparezca poco a poco
    auto WelcomeLbel = Label::createWithTTF("CONGRATULATIONS", "fonts/Marker Felt.ttf", 20);
    WelcomeLbel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y - 20 + visibleSize.height - WelcomeLbel->getContentSize().height));
    this->addChild(WelcomeLbel, 1);
    WelcomeLbel->setOpacity(0);
    WelcomeLbel->runAction(aparecer);
    WelcomeLbel->runAction(crecer);

    //sprite youWin
    auto YW = Sprite::create("YouWin.png");
    YW->setAnchorPoint(Vec2::ZERO);
    YW->setPosition(Vec2(400, 225));  // (x,y)
    addChild(YW, 0);
    
    //botones del menu
    auto BotonReplay = MenuItemImage::create("GoBack.png", "GoBackPressed.png", CC_CALLBACK_1(YouWin::ReturnToMenu, this));
    BotonReplay->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 1));

    auto* menu = Menu::create(BotonReplay, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    //label de scoreboard
    auto ScoreLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 55);
    ScoreLabel->setPosition(Vec2(origin.x + visibleSize.width / 1.1, origin.y - 20 + visibleSize.height - ScoreLabel->getContentSize().height - 20));
    scoreS = std::to_string(score);  //CONVERTIR EL PUNTAJE A CADENA
    ScoreLabel->setString("Score: " + scoreS);
    this->addChild(ScoreLabel, 4);

    return true;
}

void YouWin::ReturnToMenu(cocos2d::Ref* pSender)
{
    AudioEngine::stopAll();
    auto scene = MenuJuego::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(4, scene));
    playID = AudioEngine::play2d("PushButton.mp3", false, 1);
    score = 15000;
}

void YouWin::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}