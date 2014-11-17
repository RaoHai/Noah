#include "Gravity.h"

Gravity::Gravity()
{
	objects = std::make_shared<Vector <Widget*>>();

}

Gravity::~Gravity()
{
}

void Gravity::Add(Widget* object)
{
	objects->pushBack(object);
}

void Gravity::update(float delta) {
	for (auto iter = objects->begin(); iter != objects->end(); iter++)
	{
		auto obj = (*iter);
		obj->addForce(Vec2(0, -1), 0.98 *delta / 1000);
		obj->update(delta);
	}
}
