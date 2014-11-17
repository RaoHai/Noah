#ifndef _GEAR_WHEEL_H_
#define _GEAR_WHEEL_H_

#include "Widget.h"


class GearWheel : public Widget
{
public:
	GearWheel(std::string);
	~GearWheel();

	void rotate(int);


};


#endif