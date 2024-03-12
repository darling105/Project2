#ifndef __MAP_2_H__
#define __MAP_2_H__

#include "cocos2d.h"
#include "Maps/BaseMap.h"
#include "ButtonController/ButtonController.h"
#include "Camera/CameraFollow.h"

USING_NS_CC;

class Map2 : public BaseMap
{
public:
	static Map2* create();
	virtual bool init();

	//ButtonController* _buttonController;
	CameraFollow* cam;
protected:
	Sprite* _background;
	Character* _character;
	//GameMap* _gameMap;
	Vec2 _pauseButtonPosition;
protected:
	void goToGameScene();
	void onEnter() override;
	void callPauseScene(Ref* sender);
};
#endif //__MAP_2_H__