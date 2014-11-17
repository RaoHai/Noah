
#ifndef _MAP_PARSER_H
#define _MAP_PARSER_H

#include "cocos2d.h"
#include "Wall.h"

USING_NS_CC;

typedef std::vector<Widget *> widgetArray;

class MapParser
{
public:
	MapParser();
	~MapParser();
	
	widgetArray * WallVects;
	
	/**
	 *	Gets the instance of MapParser
	 */
	static MapParser* getInstance();

	/**
	 * Destroy the instance of MapParser
	 */
	static void destroyInstance();

	void setLayer(Layer*);
	bool loadMap(cocos2d::TMXTiledMap* );

protected:
	static MapParser* s_sharedParserUtils;

	TMXTiledMap * _map;
	Layer * _layer;
	//Vector<GearWheel*> gearwheels;


private:
	void readlayer(std::string);
};


#endif