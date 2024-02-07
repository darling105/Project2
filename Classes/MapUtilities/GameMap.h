#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
USING_NS_CC;

class GameMap : public TMXTiledMap
{
public:
	static GameMap* create(const std::string& tmxFile);
	bool initWithTMXFile(const std::string& tmxFile);

	static const std::string Collidable;

	static const int MetaOrange = 0;
	static const int MetaPink = 1;
	static const int MetaRed = 2;

	int getMetaAtPos(const Vec2& position);
	Point convertPosTileMap(Vec2 objectPos);

protected:
	TMXLayer* _metaLayer;
};
#endif // !__GAME_MAP_H__
