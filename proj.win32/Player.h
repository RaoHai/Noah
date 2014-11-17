#include "cocos2d.h"
using namespace cocos2d;

#define ANI_STAND 0
#define ANI_RUN 1
#define ANI_JUMP 2
#define ANI_ATTACK 3

#define STAND 0
#define RUN 1
#define JUMP 2
#define ATTACK 3

#define playerState int

class Player : public CCSprite
{
public:
	Player();
	~Player();

	void Render();
	void setAction(playerState action);
	playerState getAction();
private:
	CCSprite *sprite;

	Animation** animates;
	Animate* stand_animate;
	Animate* run_animate;
	Animate* jump_animate;
	Animate* attack_animate;

	SpriteFrame* default_frame;

	//Animation* stand_animation;
	//Animation* run_animation;
	//Animation* jump_animation;
	//Animation* attack_animation;

	bool status;


	Animation* loadAnimation(char*);
};
