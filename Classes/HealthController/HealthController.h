#ifndef __HEALTH_CONTROLLER_H__
#define __HEALTH_CONTROLLER_H__

#include "cocos2d.h"
#include "Camera/CameraFollow.h";
USING_NS_CC;

class HealthController : public Sprite
{
public:
	static HealthController* getInstance(float maxHealth, std::string fillPath);

	void setOnDie(std::function<void()> onDie) { this->_onDie = onDie; }

	void setCurrentHealth(float newVal);
	float getCurrentHealth();

	void setMaxHealth(float newVal);
	float getMaxHealth();
private:
	bool init(float current, std::string fillPath);
	static HealthController* _instance;

	float _currentHealth, _maxHealth;
	std::function<void()> _onDie;
	void onChangeCurrent(float newVal);
};

#endif // !__HEALTH_CONTROLLER_H__