#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public Scene
{
private:
	Sprite* _background;
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(MainMenu);
	std::string _gameName;
	std::vector<Label*> _options;

private:
	void goToGameScene();
	void menuCloseCallback(Ref* pSender);
};

#endif // !MAIN_MENU_SCENE_H__
