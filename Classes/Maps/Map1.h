#ifndef __MAP_1_H__
#define __MAP_1_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "ButtonController/ButtonController.h"
#include "MapUtilities/GameMap.h"
#include "Camera/CameraFollow.h"
#include "Maps/BaseMap.h"
USING_NS_CC;

class Map1 : public BaseMap
{
public:
    static Map1* create();
    virtual bool init() override;
protected:
    Sprite* _background;
    Character* _character;
    Vec2 _pauseButtonPosition;
protected:
    void onEnter() override;
    void callPauseScene(Ref* sender);
    void callGameOver(Ref* sender);
    void update(float dt) override;
};

#endif // __MAP_1_H__
