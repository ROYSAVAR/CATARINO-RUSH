#include "Nivel3.h"
#include "YouWin.h"
#include "GameOver.h"
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* Nivel3::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    auto layer = Nivel3::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  //mostrar circulos al rededor
    scene->addChild(layer);
    return scene;
}
bool Nivel3::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //peces
    peces[0] = { "pezNaranja.png" };
    peces[1] = { "pezGris.png" };
    peces[2] = { "pezVerde.png" };
    peces[3] = { "pezAmarillo.png" };


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    //label de scoreboard
    LabelScore = Label::createWithTTF("", "fonts/Marker Felt.ttf", 55);
    LabelScore->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y - 20 + visibleSize.height - LabelScore->getContentSize().height - 20));
    this->addChild(LabelScore, 4);
    //fondo 
    auto spriteFondo = Sprite::create("fondoAgua.jpg");
    spriteFondo->setAnchorPoint(Vec2::ZERO);
    spriteFondo->setPosition(0, 0);
    addChild(spriteFondo, 0);
    //acciones del teclado
    auto listener2 = EventListenerKeyboard().create();
    listener2->onKeyPressed = CC_CALLBACK_2(Nivel3::onKeyPressed, this);
    listener2->onKeyReleased = CC_CALLBACK_2(Nivel3::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
    //vochito
    auto cuerpo = AutoPolygon::generatePolygon("submarino.png");
    _vochito = Sprite::create(cuerpo);
    _vochito->setPosition(tamano.width / 4, tamano.height * 0.23);  //poner en el centro
    addChild(_vochito, 5);
    auto cuadro = PhysicsBody::createBox(Size(_vochito->getContentSize().width, _vochito->getContentSize().height-25));
    cuadro->setDynamic(false);
    cuadro->setCollisionBitmask(1);
    cuadro->setContactTestBitmask(true);
    _vochito->setPhysicsBody(cuadro);
    //vidas
    _vidas = Sprite::create("5_vidas.png");
    _vidas->setPosition(tamano.width / 1.2, tamano.height * 0.92);
    addChild(_vidas, 5);
    //monedas contador
    _contador_monedas = Sprite::create("0_monedas.png");
    _contador_monedas->setPosition(tamano.width / 1.275, tamano.height * 0.82);
    addChild(_contador_monedas, 5);
    //sprite nivel 3
    auto movAvion = MoveBy::create(8, Point(3000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* avion = nullptr;
    avion = Sprite::create("LEVEL3.png");
    avion->setAnchorPoint(Vec2::ZERO);
    avion->setPosition(-900, tamano.height * 0.7);
    avion->runAction(movAvion);
    this->addChild(avion, 15);

    //Fondo que se mueve / enemigos
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::FondoMovimiento), 2.7);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::FondoMovimiento2), 1.1);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::agregarTorpedos), 1.2);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::agregarMonedas), 20);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel3::ScoreBoard), .5);

    this->scheduleUpdate();

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Nivel3::onContactBegin, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}
void Nivel3::update(float deltaTime)
{

    pos = _vochito->getPosition();
    if (pos.y <= 40 && U == true)
    {
        auto action2 = MoveBy::create(.1, Vec2(0, 8));
        _vochito->runAction(action2);
    }

    if (pos.y >= 705 && D == true)
    {
        auto action2 = MoveBy::create(.1, Vec2(0, -8));
        _vochito->runAction(action2);
    }
}
void Nivel3::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto pos = _vochito->getPosition();

    if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) //mover con flecha arriba
    {
        if (pos.y >= 0)
        {
            auto action = RepeatForever::create(MoveBy::create(.05, Vec2(0, 40)));
            _vochito->runAction(action);
            posArriba = true;
            U = true;
        }
    }

    if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) //mover con flecha abajo
    {
        if (pos.y >= 0)
        {
            auto action = RepeatForever::create(MoveBy::create(.05, Vec2(0, -40)));
            _vochito->runAction(action);
            posAbajo = true;
            D = true; 
        }
    }
}

void Nivel3::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    if (key == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        CCLOG("Key UP ARROW pressed");
        _vochito->stopAllActions();
        posArriba = false;
    }

    if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        CCLOG("Key DOWN pressed");
        _vochito->stopAllActions();
        posAbajo = false;
    }
}
void Nivel3::FondoMovimiento(float delta)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    //corales
    auto movCoral = MoveBy::create(11, Point(-2000, -.01));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* coral = nullptr;

    coral = Sprite::create("coral1.png");
    coral->setAnchorPoint(Vec2::ZERO);
    coral->setPosition(1600, tamano.height * -0.01);
    coral->runAction(movCoral);
    this->addChild(coral, 2);

    //algas
    auto movAlga = MoveBy::create(9, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* alga = nullptr;

    alga = Sprite::create("algas.png");
    alga->setAnchorPoint(Vec2::ZERO);
    alga->setPosition(1600, tamano.height * -.05);
    alga->runAction(movAlga);
    this->addChild(alga, 2);

}
void Nivel3::FondoMovimiento2(float delta)  //mover linea blanca
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    int num = rand() % 4;
    //peces
    auto movPez = MoveBy::create(5, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* pez = nullptr;
    pez = Sprite::create(peces[num]);
    pez->setAnchorPoint(Vec2::ZERO);
    pez->setPosition(1600, CCRANDOM_0_1() * tamano.height);
    pez->runAction(movPez);
    this->addChild(pez, 1);
}

void Nivel3::agregarTorpedos(float delta)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto cuerpo = AutoPolygon::generatePolygon("torpedo.png");
    auto movTaxi = MoveBy::create(5, Point(-3000, 0));  //mover de un punto a otro    MobeBy Point(x,y)

    _carro = Sprite::create(cuerpo);
    _carro->setAnchorPoint(Vec2::ZERO);
    _carro->setPosition(1600, CCRANDOM_0_1() * tamano.height);
    _carro->runAction(movTaxi);

    this->addChild(_carro, 4);
    auto cuadro = PhysicsBody::createBox(Size(_carro->getContentSize().width, _carro->getContentSize().height));
    cuadro->setDynamic(false);  //poner false para desactivar gravedad
    cuadro->setCollisionBitmask(2);
    cuadro->setContactTestBitmask(true);
    _carro->setPhysicsBody(cuadro);
}
void Nivel3::agregarMonedas(float dt)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto cuerpo = AutoPolygon::generatePolygon("moneda.png");
    auto movMoneda = MoveBy::create(5, Point(-3000, 0));  //mover de un punto a otro    MobeBy Point(x,y)

    _monedas = Sprite::create(cuerpo);
    _monedas->setAnchorPoint(Vec2::ZERO);
    _monedas->setPosition(1600, CCRANDOM_0_1() * tamano.height);
    _monedas->runAction(movMoneda);

    this->addChild(_monedas, 5);
    auto cuadro = PhysicsBody::createBox(Size(_monedas->getContentSize().width, _monedas->getContentSize().height));
    cuadro->setDynamic(false);  //poner false para desactivar gravedad
    cuadro->setCollisionBitmask(3);
    cuadro->setContactTestBitmask(true);
    _monedas->setPhysicsBody(cuadro);
}
void Nivel3::ScoreBoard(float dt)
{
    scoreS = std::to_string(score);  //CONVERTIR EL PUNTAJE A CADENA
    LabelScore->setString("Score: " + scoreS);
}
bool Nivel3::onContactBegin(PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    //vocho 1
    //taxi 2
    //moneda 3
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        CCLOG("COLISSION HAS OCURRED");
        AudioEngine::play2d("golpe.mp3", false);
        //  a->getNode()->removeFromParent();
        vidas--;
        score = score - 1000; 
    }
    if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        CCLOG("COLISSION HAS OCURRED");
        AudioEngine::play2d("agarrarMoneda.mp3", false);
        auto GuardarMoneda = MoveBy::create(1, Point(-500, 2000));  //mover de un punto a otro    MobeBy Point(x,y)
        //  b->getNode()->removeFromParent();
        //  _monedas->setTexture("transparente.png");
        _monedas->runAction(GuardarMoneda);
        monedas--;
    }
    if (monedas == 2) { _contador_monedas->setTexture("1_monedas.png"); }
    if (monedas == 1) { _contador_monedas->setTexture("2_monedas.png"); }
    if (monedas == 0)
    {
        _contador_monedas->setTexture("3_monedas.png");
        auto ConFisica = Scene::createWithPhysics();
        AudioEngine::stopAll();
        auto scene = YouWin::createScene();
        ConFisica->addChild(scene);
        // ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE LO COLOREE O NO
        Director::getInstance()->replaceScene(TransitionFade::create(4, ConFisica));
        playID = AudioEngine::play2d("WinSound.mp3", false, 1);
    }

    if (vidas == 4) { _vidas->setTexture("4_vidas.png"); }
    if (vidas == 3) { _vidas->setTexture("3_vidas.png"); }
    if (vidas == 2) { _vidas->setTexture("2_vidas.png"); }
    if (vidas == 1) { _vidas->setTexture("1_vidas.png"); }
    if (vidas == 0)
    {
        auto ConFisica = Scene::createWithPhysics();
        AudioEngine::stopAll();
        auto scene = GameOver::createScene();
        ConFisica->addChild(scene);
        ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE LO COLOREE O NO
        Director::getInstance()->replaceScene(TransitionFade::create(4, ConFisica));
        playID = AudioEngine::play2d("perder.mp3", false, 1);
    }
    return true;
}
void Nivel3::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
