#ifndef __MAP_3_H__
#define __MAP_3_H__

#include "cocos2d.h"
#include "Maps/BaseMap.h"
#include "ButtonController/ButtonController.h"
#include "Camera/CameraFollow.h"

USING_NS_CC;

class Map3 : public BaseMap
{
public:
	static Map3* create();
	virtual bool init();
	CameraFollow* cam;
protected:
	Sprite* _background;
	Character* _character;
	Vec2 _pauseButtonPosition;
protected:
	void goToGameScene();
	void onEnter() override;
	void callPauseScene(Ref* sender);
};
#endif //__MAP_3_H__