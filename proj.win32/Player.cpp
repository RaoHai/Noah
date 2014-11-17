#include "Player.h"

Animation* Player::loadAnimation(char* path) {
	Vector<SpriteFrame*> animFrames(8);
	for (int i = 0; i < 8; i++)
	{
		auto frame = SpriteFrame::create(path, CCRectMake(i * 82, 0, 82, 118)); //we assume that the sprites' dimentions are 40*40 rectangles.
		animFrames.pushBack(frame);
	}
	default_frame = animFrames.at(0);
	auto _animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto _animate = Animate::create(_animation);
	return _animation;
}

Player::Player()
{	
	status = STAND;
	animates = (Animation**)malloc(4 * sizeof(Animation*));

	animates[ANI_STAND] = loadAnimation("player_stand.png");
	animates[ANI_RUN] = loadAnimation("player_run.png");

	sprite = Sprite::createWithSpriteFrame(default_frame);
}

void Player::setAction(playerState action) {
	status = action;
}

playerState Player::getAction() {
	return status;
}

void Player::Render() {
	auto animation = animates[status];
	runAction(RepeatForever::create(Animate::create(animation)));
}

Player::~Player()
{
}