#ifndef __WINNING_SCENE_H__
#define __WINNING_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class WinningScene : public Scene
{
public:
	static Scene* create();
	virtual bool init();

private:
	Sprite* _background;
private:
	void goToMainMenuScene(Ref* sender);
	void goToNextMap();

};
#endif // !__WINNING_SCENE_H__