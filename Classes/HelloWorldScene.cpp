#include "HelloWorldScene.h"
#include "MapParser.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
		
	
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vec2(0, GRAVITY));

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	
	
    // add layer as a child to scene
    scene->addChild(layer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();

	body->setCategoryBitmask(0x01);
	body->setContactTestBitmask(0x01);
	body->setCollisionBitmask(0x01);

	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);


	auto body1 = PhysicsBody::createEdgeBox(Size(200, 20), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode1 = Node::create();

	body1->setCategoryBitmask(0x01);
	body1->setContactTestBitmask(0x01);
	body1->setCollisionBitmask(0x01);

	edgeNode1->setPosition(Point(visibleSize.width / 2, 120));
	edgeNode1->setPhysicsBody(body1);
	edgeNode1->setTag(WORLD);
	scene->addChild(edgeNode1);

	edgeNode->setTag(WORLD);
	scene->addChild(edgeNode);

    // return the scene
    return scene;
}
void HelloWorld::setViewpointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


	std::string file = "demo.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	_tileMap = TMXTiledMap::createWithXML(str->getCString(), "");
	_background = _tileMap->layerNamed("Background");

	addChild(_tileMap);

	TMXObjectGroup *objects = _tileMap->getObjectGroup("Objects");
	CCASSERT(NULL != objects, "'Objects' object group not found");
	auto spwanPoint = objects->getObject("SpawnPoint");
	CCASSERT(!spwanPoint.empty(), "SpwanPoint object not found");
	int x = spwanPoint["x"].asInt();
	int y = spwanPoint["y"].asInt();
	CCSprite *sprite;
	


	//Vector<SpriteFrame*> animFrames(8);
	//for (int  i = 0; i < 8; i++)
	//{
	//	/*for (int j = 1; i < 4; i++)
	//	{*/
	//		
	//		auto frame = SpriteFrame::create("player_stand.png", CCRectMake(i * 82 , 0, 82, 118)); //we assume that the sprites' dimentions are 40*40 rectangles.
	//		animFrames.pushBack(frame);
	//	//}
	//}
	//auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
 //   auto animate = Animate::create(animation);
	//
	//_player = Sprite::createWithSpriteFrame(animFrames.at(0));
	//_player->setPosition(x, y);
	/*addChild(_player);
	_player->runAction(RepeatForever::create(Animate::create(animation)));*/
	
	

	_player = new Player();
	_player->setPosition(x, y);
	_player->getSprite()->setTag(PLAYER);

	auto ground_body = PhysicsBody::createBox(Size(1000, 10));



	addChild(_player->getSprite());


	MapParser *parser = MapParser::getInstance();
	parser->setLayer(this);
	parser->loadMap(_tileMap);
	
	//setViewpointCenter(_player->getPosition());


	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::keyReleased, this);
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	
	scheduleUpdate();
    return true;
}

void HelloWorld::update(float delta)
{
		
	auto _playerpos = _player->getPosition();
	if (strcmp(_player->getAction(), "ATTACK") != 0)
	{

		if (keys.find(EventKeyboard::KeyCode::KEY_A) != keys.end())
		{
			_playerpos.x -= 3.0f;
			_player->setAction("RUN");
			_player->flipX(true);
		}

		if (keys.find(EventKeyboard::KeyCode::KEY_D) != keys.end())
		{
			_playerpos.x += 3.0f;
			_player->setAction("RUN");
			_player->flipX(false);
		}

		if (keys.find(EventKeyboard::KeyCode::KEY_SPACE) != keys.end())
		{
			_player->jump();
		}
	}
	if (keys.find(EventKeyboard::KeyCode::KEY_J) != keys.end())
	{
		_player->attack();
	}


	//switch (_keycode) {
	///*case EventKeyboard::KeyCode::KEY_W:
	//	_playerpos.y += 10;
	//	break;
	//case EventKeyboard::KeyCode::KEY_S:
	//	_playerpos.y -= 10;
	//	break;*/
	//case EventKeyboard::KeyCode::KEY_A:
	//	
	//case EventKeyboard::KeyCode::KEY_D:
	//	_playerpos.x += 3.0f;
	//	_player->setAction("RUN");
	//	_player->flipX(false);
	//	break;
	//case EventKeyboard::KeyCode::KEY_SPACE:
	//	_player->jump();
	//	break;
	//}
	
	setPlayerPosition(_playerpos); 
	//_player->Render();
}

void HelloWorld::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) 
{
	if (keys.find(keyCode) == keys.end()){
		keys[keyCode] = std::chrono::high_resolution_clock::now();
	}
	
	
}

void HelloWorld::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	keys.erase(keyCode);
	_player->setAction("DEFAULT");
	/*_keycode = EventKeyboard::KeyCode::KEY_NONE;
	_player->setAction("DEFAULT");*/
}

bool HelloWorld::onContactBegin(PhysicsContact& contact) {
	CCLOG("onContactBegin");
	auto sp1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if ((sp1->getTag() == PLAYER && sp2->getTag() == WORLD) ||
		(sp1->getTag() == WORLD && sp2->getTag() == PLAYER))
	{
		_player->jump(false);
	}
	CCLOG("sp1 :%d, sp2 %d \n", sp1->getTag(), sp2->getTag());

	return true;
}

void HelloWorld::setPlayerPosition(cocos2d::Point position) {
	_player->setPosition(position);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



std::map<cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point> HelloWorld::keys;