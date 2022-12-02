#include "GameOver.h"
#include "MenuJuego.h"
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

bool GameOver::init()
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

    auto WelcomeLbel = Label::createWithTTF("You Lose", "fonts/Marker Felt.ttf", 50);
    WelcomeLbel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y-20 + visibleSize.height - WelcomeLbel->getContentSize().height -20));
    this->addChild(WelcomeLbel, 1);
    WelcomeLbel->setOpacity(0);

    WelcomeLbel->runAction(aparecer);
    WelcomeLbel->runAction(crecer);

    //fondo del menu
    auto Fondo = Sprite::create("GameOver.png");
    Fondo->setAnchorPoint(Vec2::ZERO);
    Fondo->setPosition(Vec2(50, 150));  // (x,y)
    addChild(Fondo, 0);

    //botones del menu
    auto BotonReplay = MenuItemImage::create("ReplayButton.png", "PressedReplayButton.png", CC_CALLBACK_1(GameOver::PlayButton, this));
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

void GameOver::PlayButton(cocos2d::Ref* pSender)
{
    //volver a poner Score en 15000
    score = 15000;

    auto ConFisica = Scene::createWithPhysics();
    AudioEngine::stopAll();
    auto scene = HelloWorld::createScene();
    ConFisica->addChild(scene);
    //  ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE LO COLOREE O NO
    Director::getInstance()->replaceScene(TransitionFade::create(2.5, ConFisica));
    int apretar = AudioEngine::play2d("PushButton.mp3", false, 1);
    playID = AudioEngine::play2d("AudioFondo.mp3", false, 1);
}

void GameOver::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}