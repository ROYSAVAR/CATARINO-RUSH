#include "Nivel2.h"
#include "Nivel3.h"
#include "HelloWorldScene.h"
#include "GameOver.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* Nivel2::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    auto layer = Nivel2::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  //mostrar circulos al rededor
    scene->addChild(layer);
    return scene;
}


bool Nivel2::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //label de scoreboard
    LabelScore = Label::createWithTTF("", "fonts/Marker Felt.ttf", 55);
    LabelScore->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y - 20 + visibleSize.height - LabelScore->getContentSize().height - 20));
    this->addChild(LabelScore, 4);

    //fondo 
  
    auto spriteFondo = Sprite::create("desierto.jpg");
    spriteFondo->setAnchorPoint(Vec2::ZERO);
    spriteFondo->setPosition(0, 0);
    addChild(spriteFondo, 0);
    //acciones del teclado
    auto listener2 = EventListenerKeyboard().create();
    listener2->onKeyPressed = CC_CALLBACK_2(Nivel2::onKeyPressed, this);
    listener2->onKeyReleased = CC_CALLBACK_2(Nivel2::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
    //vochito
    auto cuerpo = AutoPolygon::generatePolygon("catarino6.png");
    _vochito = Sprite::create(cuerpo);
    _vochito->setPosition(tamano.width / 4.2, tamano.height * 0.24);  //poner en el centro
    addChild(_vochito, 5);
    auto cuadro = PhysicsBody::createBox(Size(_vochito->getContentSize().width, _vochito->getContentSize().height));
    cuadro->setDynamic(false);
    cuadro->setCollisionBitmask(1);
    cuadro->setContactTestBitmask(true);
    _vochito->setPhysicsBody(cuadro);
    //sprite nivel 3
    auto movAvion = MoveBy::create(8, Point(3000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* avion = nullptr;
    avion = Sprite::create("LEVEL2.png");
    avion->setAnchorPoint(Vec2::ZERO);
    avion->setPosition(-900, tamano.height * 0.7);
    avion->runAction(movAvion);
    this->addChild(avion, 15);
    //vidas
    _vidas = Sprite::create("5_vidas.png");
    _vidas->setPosition(tamano.width / 1.2, tamano.height * 0.92);
    addChild(_vidas, 5);
    //monedas contador
    _contador_monedas = Sprite::create("0_monedas.png");
    _contador_monedas->setPosition(tamano.width / 1.275, tamano.height * 0.82);
    addChild(_contador_monedas, 5);
   

    this->schedule(CC_SCHEDULE_SELECTOR(Nivel2::FondoMovimiento), 6);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel2::FondoMovimiento2), 2);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel2::agregarCarros), 3);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel2::agregarMonedas), 15);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel2::agregarMeteoros), 6);
    this->schedule(CC_SCHEDULE_SELECTOR(Nivel2::ScoreBoard), .5);

    this->scheduleUpdate();

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Nivel2::onContactBegin, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    
    return true;
}

void Nivel2::FondoMovimiento(float delta)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    //nube1
    auto movMontain = MoveBy::create(20, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* Montana = nullptr;
    Montana = Sprite::create("nube.png");
    Montana->setAnchorPoint(Vec2::ZERO);
    Montana->setPosition(1600, tamano.height * 0.65);
    Montana->runAction(movMontain);
    this->addChild(Montana, 1);
    //nube2
    auto movNube = MoveBy::create(13, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* nube = nullptr;
    nube = Sprite::create("nube.png");
    nube->setAnchorPoint(Vec2::ZERO);
    nube->setPosition(1600, tamano.height * 0.8);
    nube->runAction(movNube);
    this->addChild(nube, 2);
    //nopal
    auto movNopal = MoveBy::create(7, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* nopal = nullptr;
    nopal = Sprite::create("nopal.png");
    nopal->setAnchorPoint(Vec2::ZERO);
    nopal->setPosition(1600, tamano.height * 0.21);
    nopal->runAction(movNopal);
    this->addChild(nopal, 3);
    //bola que gira
    auto rebote = JumpTo::create(5, Point(-150, 185), 50, 10);
    auto girar = Repeat::create(RotateBy::create(1, -360), 7);
    auto llanta = Sprite::create("bolaDesierto.png");
    llanta->setPosition(Vec2(2000, tamano.height * 0.03));  // (x,y)
    addChild(llanta, 10);
    llanta->runAction(rebote);
    llanta->runAction(girar);
}

void Nivel2::FondoMovimiento2(float delta)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    //linea blanca
    auto movLinea = MoveBy::create(3, Point(-2000, 0));
    Sprite* linea = nullptr;
    linea = Sprite::create("lineaCarretera.png");
    linea->setAnchorPoint(Vec2::ZERO);
    linea->setPosition(1600, tamano.height * 0.10);
    linea->runAction(movLinea);
    this->addChild(linea, 4);
}
void Nivel2::update(float deltaTime)
{

    pos = _vochito->getPosition();
    if (pos.x <= 800 && R == true)
    {
        auto action2 = MoveBy::create(.1, Vec2(8, 0));
        _vochito->runAction(action2);
    }

    if (pos.x >= 3000 && L == true)
    {
        auto action2 = MoveBy::create(.1, Vec2(-8, 0));
        _vochito->runAction(action2);
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (der == true)
    {
        Vec2 pos = _vochito->getPosition();
        if (pos.x <= visibleSize.width)
        {
            auto action = MoveBy::create(.2, Vec2(20, 0));
            _vochito->runAction(action);
        }
    }
    if (izq == true)
    {
        Vec2 pos = _vochito->getPosition();
        if (pos.x >= 0)
        {
            auto action = MoveBy::create(.2, Vec2(-20, 0));
            _vochito->runAction(action);
        }
    }
}
void Nivel2::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto pos = _vochito->getPosition();

    if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        der = true;
        R = true;
    }
    if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        izq = true;
        L = true;
    }

    if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) //saltar con flecha arriba
    {
        Vec2 pos = _vochito->getPosition();
        auto rebote = JumpTo::create(1, Point(pos.x, pos.y), 300, 1);
        _vochito->runAction(rebote);
        int playID = AudioEngine::play2d("saltar.mp3", false, 1);
        _vochito->setTexture("catarino7.png");
        salto = true;
    }
}

void Nivel2::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
    if (key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        CCLOG("Key derecha pressed");
        der = false;
        R = false;
    }

    if (key == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        CCLOG("Key izauierda pressed");
        izq = false;
        L = false;
    }

    if (key == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        _vochito->setTexture("catarino6.png");
        salto = false;
    }
}

void Nivel2::agregarMonedas(float dt)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto cuerpo = AutoPolygon::generatePolygon("moneda.png");

    _monedas = Sprite::create(cuerpo);
    _monedas->setAnchorPoint(Vec2::ZERO);
    _monedas->setPosition(CCRANDOM_0_1() * tamano.width, tamano.height);

    this->addChild(_monedas, 5);
    auto cuadro = PhysicsBody::createBox(Size(_monedas->getContentSize().width, _monedas->getContentSize().height));
    cuadro->setDynamic(true);  //poner false para desactivar gravedad
    cuadro->setCollisionBitmask(3);
    cuadro->setContactTestBitmask(true);
    _monedas->setPhysicsBody(cuadro);
}
void Nivel2::agregarMeteoros(float dt)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto cuerpo = AutoPolygon::generatePolygon("meteorito.png");
    auto movMeteoro = MoveBy::create(1, Point(0, -1200));

    _meteoros = Sprite::create(cuerpo);
    _meteoros->setAnchorPoint(Vec2::ZERO);
    _meteoros->setPosition(CCRANDOM_0_1() * tamano.width, tamano.height);

    this->addChild(_meteoros, 5);
    _meteoros->runAction(movMeteoro);
    auto cuadro = PhysicsBody::createBox(Size(_meteoros->getContentSize().width, _meteoros->getContentSize().height));
    cuadro->setDynamic(false);  //poner false para desactivar gravedad
    cuadro->setCollisionBitmask(4);
    cuadro->setContactTestBitmask(true);
    _meteoros->setPhysicsBody(cuadro);
}
void Nivel2::agregarCarros(float delta)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto cuerpo = AutoPolygon::generatePolygon("vochoDesierto.png");
    auto movTaxi = MoveBy::create(5, Point(-3000, 0));  //mover de un punto a otro    MobeBy Point(x,y)

    _carro = Sprite::create(cuerpo);
    _carro->setAnchorPoint(Vec2::ZERO);
    _carro->setPosition(1600, tamano.height * 0.12);
    _carro->runAction(movTaxi);

    this->addChild(_carro, 4);
    auto cuadro = PhysicsBody::createBox(Size(_carro->getContentSize().width, _carro->getContentSize().height));
    cuadro->setDynamic(false);  //poner false para desactivar gravedad
    cuadro->setCollisionBitmask(2);
    cuadro->setContactTestBitmask(true);
    _carro->setPhysicsBody(cuadro);
}
void Nivel2::ScoreBoard(float dt)
{
    scoreS = std::to_string(score);  //CONVERTIR EL PUNTAJE A CADENA
    LabelScore->setString("Score: " + scoreS);
}

bool Nivel2::onContactBegin(PhysicsContact& contact)
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
    }

    if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
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
        auto scene = Nivel3::createScene();
        ConFisica->addChild(scene);
       // ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE LO COLOREE O NO
        Director::getInstance()->replaceScene(TransitionFade::create(4, ConFisica));
        playID = AudioEngine::play2d("AudioAgua.mp3", false, 1); //musica agua 
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
        //ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE LO COLOREE O NO
        Director::getInstance()->replaceScene(TransitionFade::create(4, ConFisica));
        playID = AudioEngine::play2d("perder.mp3", false, 1);

    }

    return true;
}
void Nivel2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}
