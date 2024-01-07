#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"


class MainMenu : public cocos2d::Scene
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(MainMenu);
	void menuCloseCallback(cocos2d::Ref* pSender);
	cocos2d::Sprite* _background;
	std::string _gameName;
	std::vector<cocos2d::Label*> _options;
	
};

#endif // !MAIN_MENU_SCENE_H__
