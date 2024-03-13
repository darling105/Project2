#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "AudioManager/AudioManager.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class SettingScene : public LayerColor
{
public:
	virtual bool init() override;

	void goBack(Ref* sender);

	void onEnter() override;
	CREATE_FUNC(SettingScene);
};
#endif // !__SETTING_SCENE_H__
