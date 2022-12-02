#ifndef __NIVEL2_SCENE_H__
#define __NIVEL2_SCENE_H__

#include "cocos2d.h"

class Nivel2 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Nivel2);

    void update(float delta);
    bool Nivel2::onContactBegin(cocos2d::PhysicsContact& contact); //colisiones
    
    void Nivel2::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void Nivel2::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

    void Nivel2::FondoMovimiento(float delta);  //montañas y nubes
    void Nivel2::FondoMovimiento2(float delta); //lineas y arboles
    void Nivel2::ScoreBoard(float delta);

    bool salto = false;
    bool der = false;
    bool izq = false;

    int playID;

    int vidas = 5;
    int monedas = 3;  //volver a cambiar a 3
    std::string scoreS;

    cocos2d::Label* LabelScore;

private:
    cocos2d::Sprite* _vochito;
    cocos2d::Sprite* _taxi;
    cocos2d::Sprite* _carro;
    cocos2d::Sprite* _vidas;
    cocos2d::Sprite* _monedas;
    cocos2d::Sprite* _meteoros;
    cocos2d::Sprite* _contador_monedas;

    cocos2d::Vec2 pos;

    bool R = false;
    bool L = false;

    void agregarTaxis(float dt);
    void agregarCarros(float dt);
    void agregarMonedas(float dt);
    void agregarMeteoros(float dt);

};

#endif // __NIVEL2_SCENE_H__
