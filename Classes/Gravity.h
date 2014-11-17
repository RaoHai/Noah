#ifndef _GRAVITY_H_
#define _GRAVITY_H_
#include "Widget.h"

USING_NS_CC;

class Gravity
{
public:
	Gravity();
	~Gravity();
	void Add(Widget* object);
	void update(float delta);
private:
	std::shared_ptr<Vector<Widget*>> objects;
};

#endif