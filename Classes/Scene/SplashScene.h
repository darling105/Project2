#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include"cocos2d.h"
USING_NS_CC;

class SplashScene : public Scene
{
private:
	Sprite* _background;

public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(SplashScene);
private:
	void goToMainMenuScene();
};

#endif // !__SPLASH_SCENE_H__
