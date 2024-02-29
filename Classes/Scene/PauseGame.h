#ifndef __PAUSE_GAME_H__
#define __PAUSE_GAME_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "Camera/CameraFollow.h"
USING_NS_CC;

class PauseGame : public LayerColor
{
public:
    virtual bool init();
    static LayerColor* create();
    void goToMainMenuScene(Ref* sender);
    void callResume(Ref* sender);
    void goToSettingScene(Ref* sender);
    void onEnter() override;
};

#endif // !__PAUSE_GAME_H__
