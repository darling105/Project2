#include "Score.h"
#include "Entity/EntityInfo.h"
#include "Character/Character.h"

Score* Score::_instance;

Score* Score::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Score();
        _instance->init();
    }
    return _instance;
}

bool Score::init()
{
    scoreLabel = Label::createWithTTF("Score: 0", "fonts/Planes_ValMore.ttf", 64);
    this->addChild(scoreLabel);
    return true;
}

void Score::update(int value)
{
    score += value;
    scoreLabel->setString("Score: " + std::to_string(score));

}

void Score::reset()
{
    score = 0;
    scoreLabel->setString("Score: " + std::to_string(score));
}
