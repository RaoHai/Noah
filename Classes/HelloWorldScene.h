#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include <map>

#define PLAYER 0
#define WORLD 1

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_background;
	Player* _player;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewpointCenter(cocos2d::Point position);

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	bool onContactBegin(PhysicsContact& contact);

	void setPlayerPosition(cocos2d::Point position);

	void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void setPhyWorld(PhysicsWorld* world){ m_world = world; }
private:
	PhysicsWorld* m_world;

	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;

};

#endif // __HELLOWORLD_SCENE_H__
