#ifndef __MAP_1_H__
#define __MAP_1_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "ButtonController/ButtonController.h"
#include "MapUtilities/GameMap.h"
#include "Enemy/Enemy.h"
#include "Camera/CameraFollow.h"
USING_NS_CC;

class Map1 : public Scene
{
public:
	static Scene* create();
	virtual bool init();
	
	ButtonController* _buttonController;
	CameraFollow* cam;
protected:
	Sprite* _background;
	Character* _character;
	ButtonController* _button;
	GameMap* _gameMap;
	Enemy* _enemy;
protected:
	void goToGameScene();
	void onEnter() override;
	void resetInput();
private:
	void update(float dt);
};
#endif //__MAP_1_H__