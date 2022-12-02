#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

extern int score;

#include "cocos2d.h"
#include <string>

//using namespace  std;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void update(float delta);

    void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

    void HelloWorld::FondoMovimiento(float delta);  //montañas y nubes
    void HelloWorld::FondoMovimiento2(float delta); //lineas y arboles
    void HelloWorld::ScoreBoard(float delta); 

    bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact); //colisiones
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


    bool salto = false;
    bool der = false;
    bool izq = false;

    int playID;

    int vidas = 5;
    int monedas = 3;   //volver a cambiar a 3

    std::string carros[4]; // = { "blanco.png", "verde.png", "azul.png", "taxi.png" };
    std::string scoreS; 

    cocos2d::Label* LabelScore;

private: 
    cocos2d::Sprite* _vochito;
    cocos2d::Sprite* _taxi;
    cocos2d::Sprite* _carro;
    cocos2d::Sprite* _vidas;
    cocos2d::Sprite* _monedas;
    cocos2d::Sprite* _contador_monedas;



    cocos2d::Vec2 pos; 

    bool R = false;
    bool L = false; 

    void agregarTaxis(float dt);
    void agregarCarros(float dt);
    void agregarMonedas(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
