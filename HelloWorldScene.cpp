#include "HelloWorldScene.h"
#include "GameOver.h"
#include "Nivel2.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;

int score = 15000; 

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);  //mostrar circulos al rededor
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
    carros[0] = { "blanco.png" };
    carros[1] = { "azul.png" };
    carros[2] = { "verde.png" };
    carros[3] = { "taxi.png" };

    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

   //label de scoreboard
    LabelScore = Label::createWithTTF("", "fonts/Marker Felt.ttf", 55);
    LabelScore->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y - 20 + visibleSize.height - LabelScore->getContentSize().height - 20));
    LabelScore->setTextColor(Color4B::BLUE);
    this->addChild(LabelScore, 4);

    //fondo 
    auto spriteFondo = Sprite::create("fondo1.png");
    spriteFondo->setAnchorPoint(Vec2::ZERO);
    spriteFondo->setPosition(0, 0);
    addChild(spriteFondo, 0);
    //acciones del teclado
    auto listener2 = EventListenerKeyboard().create();
    listener2->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    listener2->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
    //vochito
    auto cuerpo = AutoPolygon::generatePolygon("catarino5.png");
    _vochito = Sprite::create(cuerpo);
    _vochito->setPosition(tamano.width / 4, tamano.height * 0.23);  //poner en el centro
    addChild(_vochito, 5);
    auto cuadro = PhysicsBody::createBox(Size(_vochito->getContentSize().width, _vochito->getContentSize().height));
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
    //avion de la buena suerte
    auto movAvion = MoveBy::create(8, Point(3000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* avion = nullptr;
    avion = Sprite::create("GoodLucky.png");
    avion->setAnchorPoint(Vec2::ZERO);
    avion->setPosition(-900, tamano.height * 0.7);
    avion->runAction(movAvion);
    this->addChild(avion, 15);

    //Fondo que se mueve / enemigos
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::FondoMovimiento), 6);
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::FondoMovimiento2), 1.8);
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::agregarTaxis), 11);
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::agregarCarros), 5);
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::agregarMonedas), 15);
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::ScoreBoard), .5);


    this->scheduleUpdate();

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}
void HelloWorld::update(float deltaTime) 
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
void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
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
        _vochito->setTexture("catarino4.png"); 
        salto = true; 
    }
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
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
        _vochito->setTexture("catarino5.png");
        salto = false; 
    }
}

void HelloWorld::FondoMovimiento(float delta)
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    //montaña
    auto movMontain = MoveBy::create(20, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* Montana = nullptr;

    Montana = Sprite::create("montana.png");
    Montana->setAnchorPoint(Vec2::ZERO);
    Montana->setPosition(1600, tamano.height * 0.51);
    Montana->runAction(movMontain);
    this->addChild(Montana, 1);

    //nube
    auto movNube = MoveBy::create(13, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* nube = nullptr;

    nube = Sprite::create("nube.png");
    nube->setAnchorPoint(Vec2::ZERO);
    nube->setPosition(1600, tamano.height * 0.8);
    nube->runAction(movNube);
    this->addChild(nube, 2);

    //pino
    auto movPino = MoveBy::create(7, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* pino = nullptr;

    pino = Sprite::create("pino.png");
    pino->setAnchorPoint(Vec2::ZERO);
    pino->setPosition(1600, tamano.height * 0.34);
    pino->runAction(movPino);
    this->addChild(pino, 3);

    //arbol
    auto movArbol = MoveBy::create(11, Point(-2000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    Sprite* arbol = nullptr;

    arbol = Sprite::create("arbol.png");
    arbol->setAnchorPoint(Vec2::ZERO);
    arbol->setPosition(1600, tamano.height * 0.42);
    arbol->runAction(movArbol);
    this->addChild(arbol, 2);

}
void HelloWorld::FondoMovimiento2(float delta)  //mover linea blanca
{
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();

    //linea blanca
    auto movLinea = MoveBy::create(3, Point(-2000, 0));  
    Sprite* linea = nullptr;
    linea = Sprite::create("lineaCarretera.png");
    linea->setAnchorPoint(Vec2::ZERO);
    linea->setPosition(1600, tamano.height * 0.14);
    linea->runAction(movLinea);
    this->addChild(linea, 4);
}

void HelloWorld::agregarTaxis(float delta)
{
    int num = rand() % 4;
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto cuerpo = AutoPolygon::generatePolygon(carros[num]);   //volver a cambiar a taxi 
    auto movTaxi = MoveBy::create(2.5, Point(-3000, 0));  //mover de un punto a otro    MobeBy Point(x,y) 3000
    auto sequence1 = Sequence::create(movTaxi, RemoveSelf::create(), NULL);

    _taxi = Sprite::create(cuerpo);
    _taxi->setAnchorPoint(Vec2::ZERO);
    _taxi->setPosition(1600, tamano.height * 0.08);
    _taxi->runAction(movTaxi);

    this->addChild(_taxi, 5);
    auto cuadro = PhysicsBody::createBox(Size(_taxi->getContentSize().width, _taxi->getContentSize().height -30 ));
    cuadro->setDynamic(false);  //poner false para desactivar gravedad
    cuadro->setCollisionBitmask(2);
    cuadro->setContactTestBitmask(true);
    _taxi->setPhysicsBody(cuadro);

    _taxi->runAction(sequence1->clone());
}

void HelloWorld::agregarCarros(float delta)
{
    int num = rand()%4;
    auto director = Director::getInstance();
    auto tamano = director->getWinSize();
    auto cuerpo = AutoPolygon::generatePolygon(carros[num]);
    auto movTaxi = MoveBy::create(5, Point(-3000, 0));  //mover de un punto a otro    MobeBy Point(x,y)
    auto sequence1 = Sequence::create(movTaxi, RemoveSelf::create(), NULL);
    _carro = Sprite::create(cuerpo);
    _carro->setAnchorPoint(Vec2::ZERO);
    _carro->setPosition(1600, tamano.height * 0.18);
    _carro->runAction(movTaxi);

    this->addChild(_carro, 4);
    auto cuadro = PhysicsBody::createBox(Size(_carro->getContentSize().width, _carro->getContentSize().height -30));
    cuadro->setDynamic(false);  //poner false para desactivar gravedad
    cuadro->setCollisionBitmask(2);
    cuadro->setContactTestBitmask(true);
    _carro->setPhysicsBody(cuadro);
    
    _carro->runAction(sequence1->clone());
}
void HelloWorld::agregarMonedas(float dt)
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
void HelloWorld::ScoreBoard(float dt)
{
    scoreS = std::to_string(score);  //CONVERTIR EL PUNTAJE A CADENA
    LabelScore->setString("Score: " + scoreS);
}
bool HelloWorld::onContactBegin(PhysicsContact& contact)
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
        score = score - 1000; 
        vidas--;
    }
    if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        CCLOG("COLISSION HAS OCURRED");
        AudioEngine::play2d("agarrarMoneda.mp3", false);
        auto GuardarMoneda = MoveBy::create(1, Point(-500, 2000));  //mover de un punto a otro    MobeBy Point(x,y)
        _monedas->runAction(GuardarMoneda);
        monedas--;
    }
    if (monedas == 2){ _contador_monedas->setTexture("1_monedas.png");    }
    if (monedas == 1){ _contador_monedas->setTexture("2_monedas.png");    }
    if (monedas == 0)
    {
        _contador_monedas->setTexture("3_monedas.png");
        auto ConFisica = Scene::createWithPhysics();
        AudioEngine::stopAll();
        auto scene = Nivel2::createScene();
        ConFisica->addChild(scene);
       // ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE LO COLOREE O NO
        Director::getInstance()->replaceScene(TransitionFade::create(4, ConFisica));

        playID = AudioEngine::play2d("AudioDesierto.mp3", false, 1); //musica desierto 
    }

    if (vidas == 4){   _vidas->setTexture("4_vidas.png");    }
    if (vidas == 3){   _vidas->setTexture("3_vidas.png");    }
    if (vidas == 2){   _vidas->setTexture("2_vidas.png");    }
    if (vidas == 1){   _vidas->setTexture("1_vidas.png");    }
    if (vidas == 0)
    {
        auto ConFisica = Scene::createWithPhysics();
        AudioEngine::stopAll();
        auto scene = GameOver::createScene();
        ConFisica->addChild(scene);
      //  ConFisica->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //sI QUIERES QUE LO COLOREE O NO
        Director::getInstance()->replaceScene(TransitionFade::create(2.5, ConFisica));

        playID = AudioEngine::play2d("perder.mp3", false, 1);
    }

    return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}


