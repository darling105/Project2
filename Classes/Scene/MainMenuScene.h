#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include"cocos2d.h"
USING_NS_CC;

class MainMenuScene : public Scene
{
public:
	bool init();
	static Scene* createScene(); 
	CREATE_FUNC(MainMenuScene);
private:
	Sprite* _background;
	std::string _gameName;
	std::vector<Label*> _options;
	
};

#endif // !MAIN_MENU_SCENE_H__
