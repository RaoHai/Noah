#include "Player.h"

void Player::loadAnimation(char* status, char* path, int width, int height, float duration) {
	CCLOG("loadAnimation: %d. %s", status, path);
	Vector<SpriteFrame*> animFrames(8);
	for (int i = 0; i < 8; i++)
	{
		auto frame = SpriteFrame::create(path, CCRectMake(i * width, 0, width, height)); //we assume that the sprites' dimentions are 40*40 rectangles.
		animFrames.pushBack(frame);
	}
	if (strcmp(status,"STAND")!= -1)
	{
		default_frame = animFrames.at(0);
	}
	
	auto _animation = Animation::createWithSpriteFrames(animFrames, duration);
	//auto _animate = Animate::create(_animation);
	AnimationCache::getInstance()->addAnimation(_animation, status);
	
}

Player::Player()
{	
	isJump = false;
	default_action = "STAND";
	status = default_action;
	animates = (Animate**)malloc(4 * sizeof(Animate*));
	animations = (Animation**)malloc(4 * sizeof(Animation*));

	loadAnimation("STAND","player_stand.png", 82, 118);
	loadAnimation("RUN" , "player_run.png", 108, 114);
	loadAnimation("JUMP", "player_jump.png", 82, 114);
	loadAnimation("ATTACK", "player_attack.png", 128, 128, 0.08);

	_sprite = Sprite::createWithSpriteFrame(default_frame);
	auto body = PhysicsBody::createCircle(_sprite->getContentSize().width / 2);
	//auto body = PhysicsBody::createBox(Size(_sprite->getContentSize().width / 2, _sprite->getContentSize().width / 2));
	body->getShape(0)->setRestitution(0);
	body->getShape(0)->setFriction(1.0f);
	body->getShape(0)->setDensity(1.0f);
	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x01);

	body->setRotationEnable(false);
	_sprite->setPhysicsBody(body);

	_action = _sprite->runAction(
		RepeatForever::create(
			Animate::create(
				AnimationCache::getInstance()->getAnimation(status)
			)
		)
	);

	
}

void Player::setAction(char* action) {
	if (strcmp(action, status) == 0 || (status == "ATTACK" ))
	{
		return;
	}

	if (action == "DEFAULT")
	{
		action = default_action;
	}
	if (status == "JUMP" && action == "RUN")
	{
		return;
	}
	CCLOG(" CHANGE ANIMATION -> %s ", action);
	status = action;

	_sprite->stopAction(_action);
	if (action == "ATTACK")
	{
		_action = _sprite->runAction(
			CCSequence::create(
				Animate::create(
					AnimationCache::getInstance()->getAnimation(status)
				),
				CCCallFunc::create(this, callfunc_selector(Player::stand)), NULL
			)
		);
	}
	else {
		_action = _sprite->runAction(
			RepeatForever::create(
				Animate::create(
					AnimationCache::getInstance()->getAnimation(status)
				)
			)
			);
	}

}

char* Player::getAction() {
	return status;
}

void Player::Render() {
	auto animation = status;
	_sprite->runAction(
		Animate::create(AnimationCache::getInstance()->getAnimation(animation))
	);
}

Player::~Player()
{
}

void Player::stand()
{
	status = "STAND";
	setAction("STAND");
}

void Player::attack()
{
	setAction("ATTACK");
}
void Player::jump(bool _jumped)
{
	if (_jumped == false)
	{
		isJump = false;
		default_action = "STAND";
		setAction("STAND");
		return;
	}
	if (!isJump)
	{
		isJump = true;
		default_action = "JUMP";
		setAction("JUMP");

		Vect impulse = Vect(0.0f, -GRAVITY / 2);
		_sprite->getPhysicsBody()->setVelocity(impulse);

	}
	
}

