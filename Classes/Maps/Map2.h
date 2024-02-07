#ifndef __MAP_2_H__
#define __MAP_2_H__

#include "cocos2d.h"
USING_NS_CC;

class Map2 : public Scene
{
public:
	static Scene* create();
	virtual bool init();
private:
	Sprite* _background;
private:
	void goToGameScene();
};
#endif //__MAP_1_H__