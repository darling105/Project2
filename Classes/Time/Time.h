#ifndef __TIME_H__
#define __TIME_H__

#include "cocos2d.h"

USING_NS_CC;

class Time : public Label
{
public:
	static Time* getInstance();
	void update(float dt);
	void reset();
	int getTime() const { return time; }
	Label* timeLabel;
protected:
	bool init() override;
	void onEnter() override;
protected:
	static Time* _instance;
	int time;
};

#endif // !__TIME_H__