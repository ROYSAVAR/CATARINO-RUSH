#ifndef __NIVEL3_SCENE_H__
#define __NIVEL3_SCENE_H__

#include "cocos2d.h"

class Nivel3 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);


    bool Nivel3::onContactBegin(cocos2d::PhysicsContact& contact); //colisiones
    // implement the "static create()" method manually
    CREATE_FUNC(Nivel3);

    void update(float delta);

    void Nivel3::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void Nivel3::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

    void Nivel3::FondoMovimiento(float delta);  //montañas y nubes
    void Nivel3::FondoMovimiento2(float delta); //lineas y arboles
    void Nivel3::ScoreBoard(float delta);

    bool salto = false;
    bool der = false;
    bool izq = false;
    bool posArriba; bool posAbajo;
    int playID;

    int vidas = 5;
    int monedas = 3;   //volver a cambiar a 3

    std::string peces[4];

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

    bool U = false;
    bool D = false;

    void agregarTorpedos(float dt);
    void agregarMonedas(float dt);

};

#endif // __NIVEL3_SCENE_H__
