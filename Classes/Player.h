#include "cocos2d.h"
#include "Widget.h"

#define GRAVITY -980.0f

using namespace cocos2d;

class Player : public Widget
{
public:
	Player();
	~Player();

	void Render();
	void setAction(char* action);
	char* getAction();

	//actions
	void stand();
	void jump(bool _jumped = true);
	void attack();
private:

	Animate** animates;
	Animation** animations;
	Action* _action;

	char* default_action;

	SpriteFrame* default_frame;

	//Animation* stand_animation;
	//Animation* run_animation;
	//Animation* jump_animation;
	//Animation* attack_animation;

	char* status;
	bool isJump;

	void loadAnimation(char*, char*, int, int, float duration = 0.15f);
};
