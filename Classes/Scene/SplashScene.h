#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include"cocos2d.h"

class SplashScene : public cocos2d::Scene
{
private:
	cocos2d::Sprite* _background;
private:
	void goToMainMenuScene();
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SplashScene);
};
#endif // !__SPLASH_SCENE_H__