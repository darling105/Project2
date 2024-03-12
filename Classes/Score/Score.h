#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"

USING_NS_CC;

class Score : public Label
{
public:
	static Score* getInstance();
	void update(int value);
	void reset();
	Label* scoreLabel;
protected:
	bool init() override;
protected:
	static Score* _instance;
	int score;

};

#endif // !__SCORE_H__