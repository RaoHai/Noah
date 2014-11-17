#include "GearWheel.h"


GearWheel::GearWheel(std::string path)
{	
	_sprite = Sprite::create(path);
}

GearWheel::~GearWheel()
{
}

void GearWheel::rotate(int speed)
{
	CCActionInterval * rotateAction = CCRotateBy::create(speed, 180);
	_sprite->runAction(CCRepeatForever::create(rotateAction));
}