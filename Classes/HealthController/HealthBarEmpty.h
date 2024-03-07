#ifndef __HEALTH_BAR_EMPTY_H__
#define __HEALTH_BAR_EMPTY_H__

#include "cocos2d.h"
USING_NS_CC;

class HealthBarEmpty : public Sprite
{
public:
	static HealthBarEmpty* getInstance(std::string fillPath);
private:
	bool init(std::string fillPath);
	static HealthBarEmpty* _instance;
};

#endif // !__HEALTH_BAR_EMPTY_H__