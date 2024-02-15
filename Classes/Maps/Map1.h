#ifndef __MAP_1_H__
#define __MAP_1_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "MapUtilities/GameMap.h"
#include "Enemy/Enemy.h"
USING_NS_CC;

class Map1 : public Scene
{
public:
	static Scene* create();
	virtual bool init();
protected:
	Sprite* _background;
	Character* _character;
	GameMap* _gameMap;
	Enemy* _enemy;
protected:
	void goToGameScene();
	void onEnter() override;

};
#endif //__MAP_1_H__