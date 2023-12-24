#ifndef _MAIN_MENU_SCENE_H_
#define _MAIN_MENU_SCENE_H_

#include"cocos2d.h"
USING_NS_CC;

class MainMenuScene : Scene
{
public:
	bool init();
private:
	Sprite* _background;
	std::string _gameName;
	std::vector<Label*> _options;
	void goToGameScene();
	void goToSettingScene();
};

#endif // !MAIN_MENU_SCENE_H__
