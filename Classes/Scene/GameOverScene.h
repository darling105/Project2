#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "Camera/CameraFollow.h"
USING_NS_CC;

class GameOverScene : public LayerColor
{
public:
	virtual bool init();
	static LayerColor* create();
	void goToMainMenuScene(Ref* sender);
	void replayScene();
	void onEnter() override;
};

#endif // !__GAME_OVER_SCENE_H__
