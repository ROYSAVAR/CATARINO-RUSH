#include "Controles.h"
#include "MenuJuego.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* Controles::createScene()
{
    auto scene = Scene::create();
    auto layer = Controles::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Controles::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    //crear un label 
    auto crecer = ScaleBy::create(3, 2);  //ScaleBy nos hace crecer cosas recibe tiempo y veces que crece
    auto aparecer = FadeIn::create(3); //Hara que aparezca poco a poco

    auto WelcomeLbel = Label::createWithTTF("Controls", "fonts/Marker Felt.ttf", 20);
    WelcomeLbel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - WelcomeLbel->getContentSize().height));
    this->addChild(WelcomeLbel, 1);
    WelcomeLbel->setOpacity(0);

    WelcomeLbel->runAction(aparecer);
    WelcomeLbel->runAction(crecer);

    //fondo del menu
    auto Fondo = Sprite::create("FondoNegro.png");
    Fondo->setAnchorPoint(Vec2::ZERO);
    Fondo->setPosition(Vec2(100, 0));  // (x,y)
    addChild(Fondo, 0);

    //botones controles
    auto Controles = Sprite::create("botones_controles.png");
    Controles->setAnchorPoint(Vec2::ZERO);
    Controles->setPosition(Vec2(100, 0));  // (x,y)
    addChild(Controles, 1);

    //instrucciones
    auto instrucciones = Sprite::create("instructions.png");
    instrucciones->setAnchorPoint(Vec2::ZERO);
    instrucciones->setPosition(Vec2(origin.x + visibleSize.width / 4, tamano.height * 0.5));
    addChild(instrucciones, 1);

    //botones del menu
    auto volver = MenuItemImage::create("ReturnButton.png", "ReturnButtonPressed.png", CC_CALLBACK_1(Controles::Regresar, this));
    volver->setPosition(Point(visibleSize.width / 16, (visibleSize.height / 5) * 4.4));
  
    auto* menu = Menu::create(volver, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    

    return true;
}

void Controles::Regresar(cocos2d::Ref* pSender)
{
    AudioEngine::stopAll();
    CCLOG("Start Button");
    auto scene = MenuJuego::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(4, scene));
    musica = AudioEngine::play2d("PushButton.mp3", false, 1);
}


void Controles::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
