#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class SettingScene : public Scene
{
public:
	static Scene* create();
	virtual bool init();
private:
	Sprite* _background;
private:
	void goToMainMenuScene();
	void sliderValueChanged(Ref* sender, ui::Slider::EventType type);
	static void saveVolume(float volume);
	static float getSavedVolume();
};
#endif // !__SETTING_SCENE_H__
