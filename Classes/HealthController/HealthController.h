#ifndef __HEALTH_CONTROLLER_H__
#define __HEALTH_CONTROLLER_H__

#include "cocos2d.h"
#include "Camera/CameraFollow.h";
USING_NS_CC;

class HealthController : public Sprite
{
public:
	static HealthController* getInstance();
	void setCurrentHealth(float newVal);
	float getCurrentHealth();
	void setMaxHealth(float newVal);
	float getMaxHealth();
private:
	bool init();
	static HealthController* _instance;
	static std::vector<HealthController*> _healthBars;
	float _currentHealth, _maxHealth;
	std::function<void()> _onDie;
	void onChangeCurrent(float newVal);

	ClippingNode* _clippingNode;
	DrawNode* _stencil;
	Sprite* _healthBar;

};

#endif // !__HEALTH_CONTROLLER_H__