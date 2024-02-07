#include "GameMap.h"

const std::string GameMap::Collidable = "Collidable";

GameMap* GameMap::create(const std::string& tmxFile)
{
	GameMap* ret = new (std::nothrow) GameMap();
	if (ret->initWithTMXFile(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool GameMap::initWithTMXFile(const std::string& tmxFile)
{
	if (!TMXTiledMap::initWithTMXFile(tmxFile))
	{
		log("init GameMap failed!");
		return false;
	}
	/*_metaLayer = this->getLayer("Meta");
	_metaLayer->setVisible(false);*/
	return true;
}

//int GameMap::getMetaAtPos(const Vec2& position)
//{
//	Point posTile = convertPosTileMap(position);
//	int result = -1;
//	int tileGid = _metaLayer->getTileGIDAt(posTile);
//	if (tileGid != 0)
//	{
//		Value temp = this->getPropertiesForGID(tileGid);
//		if (!temp.isNull())
//		{
//			ValueMap properties = temp.asValueMap();
//			auto properName = properties.find(GameMap::Collidable);
//			auto properValue = properties.at(GameMap::Collidable).asInt();
//			if (properName != properties.end() && properValue == MetaOrange)
//			{
//				result = GameMap::MetaOrange;
//			}
//			else if (properName != properties.end() && properValue == MetaPink)
//			{
//				result = GameMap::MetaPink;
//			}
//			else if (properName != properties.end() && properValue == MetaRed)
//			{
//				result = GameMap::MetaRed;
//			}
//		}
//	}
//	return result;
//}

Point GameMap::convertPosTileMap(Vec2 objectPos) {
	int x = objectPos.x / _tileSize.width;  // Tính toán vị trí x trên tilemap
	int y = (_mapSize.height * _tileSize.height - objectPos.y) / _tileSize.height;  // Tính toán vị trí y trên tilemap
	return Point(x, y);
}

