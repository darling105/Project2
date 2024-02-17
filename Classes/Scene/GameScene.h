#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"cocos2d.h"
USING_NS_CC;

class GameScene : public Scene
{
public:
	static Scene* create();
	virtual bool init();

private:
	Sprite* _background;
private:
	void goToMainMenuScene();
	void goToMap1();
};

#endif //__GAME_SCENE_H__