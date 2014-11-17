#include "MapParser.h"

MapParser* MapParser::s_sharedParserUtils = nullptr;

MapParser::MapParser()
{
	
}

MapParser::~MapParser()
{
}


MapParser* MapParser::getInstance()
{
	if (s_sharedParserUtils == nullptr)
	{
		s_sharedParserUtils = new MapParser();
	}
	return s_sharedParserUtils;
}



bool MapParser::loadMap(cocos2d::TMXTiledMap* map)
{
	_map = map;
	WallVects = new widgetArray();
	
	
	readlayer("Objects");
	
	return true;


}

void MapParser::readlayer(std::string name)
{
	TMXObjectGroup *group = _map->getObjectGroup(name);
	ValueVector object = group->getObjects();
	ValueVector::iterator it = object.begin();
	for (; it != object.end(); it++)
	{
		Value obj = *it;
		ValueMap map = obj.asValueMap();
		//log("type = %s \n", map.at("type"));
		if (map.at("type").asString() == "Wall")
		{
			log("type = Wall");
			float x = map.at("x").asFloat(), y = map.at("y").asFloat();
			int x_index = (int)floor(x / 32), y_index = (int)floor(y / 32);
			auto _wall = new Wall();
			WallVects->push_back(_wall);

		}
	}
}

void MapParser::setLayer(Layer* layer)
{
	_layer = layer;
}