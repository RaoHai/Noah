#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "cocos2d.h"

USING_NS_CC;
class Widget :public cocos2d::Object
{
public:
	Widget();
	~Widget();
	void setPosition(Point);
	void setPosition(float, float);
	Vec2 getPosition();
	Size getSize();

	Sprite* getSprite();
	void release();
	void addTo(Layer*);

	void flipX(bool flipped);
	void update(float delta);

	//force
	void addForce(Vec2, float);
protected:
	Sprite *_sprite;

	Vec2 _force_vect;
	Vec2 _speed_vect;

	
};


#endif