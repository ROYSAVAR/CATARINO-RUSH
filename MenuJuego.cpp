#include "MenuJuego.h"
#include "HelloWorldScene.h"
#include "Controles.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* MenuJuego::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuJuego::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MenuJuego::init()
{
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    musica = AudioEngine::play2d("IntroSound.mp3", false, 1);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //crear un label 
    auto crecer = ScaleBy::create(3, 2);  //ScaleBy nos hace crecer cosas recibe tiempo y veces que crece
    auto aparecer = FadeIn::create(3); //Hara que aparezca poco a poco

    auto WelcomeLbel = Label::createWithTTF("Welcome to CatarinoRush", "fonts/Marker Felt.ttf", 20);
    WelcomeLbel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - WelcomeLbel->getContentSize().height));
    this->addChild(WelcomeLbel, 4);
    WelcomeLbel->setOpacity(0);

    WelcomeLbel->runAction(aparecer);
    WelcomeLbel->runAction(crecer);

    //fondo del menu loading
    auto Fondo1 = Sprite::create("loading.png");
    Fondo1->setAnchorPoint(Vec2::ZERO);
    Fondo1->setPosition(Vec2(-150, 0));  // (x,y)
    addChild(Fondo1, 1);

    //fondo del menu ciudad
    auto Fondo2 = Sprite::create("ciudadHD.jpg");
    Fondo2->setAnchorPoint(Vec2::ZERO);
    Fondo2->setPosition(Vec2(250, 145));  // (x,y)
    addChild(Fondo2, 2);

    //botones del menu
    auto BotonStart = MenuItemImage::create("StartButton.png", "StartButtonPressed.png", CC_CALLBACK_1(MenuJuego::PlayButton, this));
    auto BotonControles = MenuItemImage::create("ControlsButton.png", "ControlsButtonPressed.png", CC_CALLBACK_1(MenuJuego::ControlsButton, this));
    auto BotonExit = MenuItemImage::create("ExitButton.png", "ExitButtonPressed.png", CC_CALLBACK_1(MenuJuego::ExitButton, this));

    BotonStart->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4));
    BotonControles->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));
    BotonExit->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2));

    auto* menu = Menu::create(BotonStart, BotonControles, BotonExit, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu,3);

    //vochito animado derecho
    auto animadoder = Sprite::create("animadoder.png");
    animadoder->setAnchorPoint(Vec2::ZERO);
    animadoder->setPosition(Vec2(100, 100));  // (x,y)
    addChild(animadoder, 3);

    //vochito animado izquierdo
    auto animadoizq = Sprite::create("animadoizq.png");
    animadoizq->setAnchorPoint(Vec2::ZERO);
    animadoizq->setPosition(Vec2(1050, 100));  // (x,y)
    addChild(animadoizq, 3);
    
    //llanta que vota
    auto rebote = JumpTo::create(3, Point(-150, 30), 50, 10);
    auto girar = Repeat::create(RotateBy::create(1, -360),5);
    auto llanta = Sprite::create("llanta.png");
    llanta->setPosition(Vec2(2000, 200));  // (x,y)
    addChild(llanta, 4);
    llanta->runAction(rebote);
    llanta->runAction(girar);

    //bloque blanco de loading
    auto movBloque = MoveBy::create(20, Point(1000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* bloque = nullptr;

    bloque = Sprite::create("bloqueBlanco.png");
    bloque->setPosition(-200, 80);
    bloque->runAction(movBloque);
    this->addChild(bloque, 0);
    

    return true;
}

void MenuJuego::PlayButton(cocos2d::Ref *pSender)
{
    auto ConFisica = Scene::createWithPhysics();
    AudioEngine::stop(musica);
    auto scene = HelloWorld::createScene();

    ConFisica->addChild(scene);
  //  ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE muestre el cuadro rojo O NO

    Director::getInstance()->replaceScene(TransitionFade::create(4, ConFisica));

    musica = AudioEngine::play2d("PushButton.mp3", false, 1);
    playID = AudioEngine::play2d("AudioFondo.mp3", false, 1);
}

void MenuJuego::ControlsButton(cocos2d::Ref* pSender)
{
    AudioEngine::stopAll();
    auto scene = Controles::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(4, scene));
    musica = AudioEngine::play2d("PushButton.mp3", false, 1);
}

void MenuJuego::ExitButton(cocos2d::Ref* pSender)
{
    AudioEngine::stopAll();
    musica = AudioEngine::play2d("PushButton.mp3", false, 1);
    Director::getInstance()->end();

}

void MenuJuego::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
