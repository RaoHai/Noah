#include "Widget.h"

Widget::Widget()
{
	_speed_vect = Vec2(0, 0);
}

Widget::~Widget()
{
}

void Widget::release()
{
	this->~Widget();
}

void Widget::setPosition(Point point)
{
	_sprite->setPosition(point);
}

void Widget::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);
}

Size Widget::getSize()
{
	return _sprite->getBoundingBox().size;

}
Vec2 Widget::getPosition()
{
	return _sprite->getPosition();
}

Sprite* Widget::getSprite(){
	return _sprite;
}
void Widget::addTo(Layer* layer)
{
	layer->addChild(_sprite);
}

void Widget::flipX(bool flipped)
{
	_sprite->setFlipX(flipped);
}

//force

void Widget::addForce(Vec2 vect, float strength)
{
	auto _vect = ccpNormalize(vect) * strength;
	if (_force_vect == Vec2::ZERO)
	{
		_force_vect = _vect;
	}
	else {
		_force_vect += _vect;
	}
}

void Widget::update(float delta) {
	Vec2 deltaSpeed = Vec2(_force_vect.x / delta, _force_vect.y / delta);
	_speed_vect += deltaSpeed;
	_force_vect = Vec2::ZERO;
	setPosition(getPosition() + _speed_vect);
}