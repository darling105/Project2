#include "ButtonController.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"
#include "Manager/GameManager.h"
#include "Scene/PauseGame.h"
#include "AudioManager/AudioManager.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

ButtonController* ButtonController::_instance;

ButtonController* ButtonController::getInstance() {
    if (_instance == nullptr)
    {
        _instance = new ButtonController();
        _instance->init();
        _instance->retain();
    }
    return _instance;
}


bool ButtonController::init() {
    if (!Node::init()) {
        return false;
    }

    AudioManager* audioManager = AudioManager::getInstance();

    EntityInfo info(1, "character");

    _leftButton = ui::Button::create("Buttons/Icon44.png");
    _leftButton->setContentSize(Size(50, 50));
    _leftButton->setPosition(Vec2(100, 40));
    _leftButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
    switch (type)
    {
    case ui::Widget::TouchEventType::BEGAN:
        log("LeftButton Pressed");
        if (ButtonController::getInstance()) {
            auto _character = Character::getInstance(&info)->getCharacter(0);
            if (_character) {
                _character->setLeftButtonDown(true);
            }
        }
        break;
    case ui::Widget::TouchEventType::ENDED:
        log("LeftButton Released");
        if (ButtonController::getInstance()) {
            auto _character = Character::getInstance(&info)->getCharacter(0);
            if (_character) {
                _character->setLeftButtonDown(false);
            }
        }
        break;
    case ui::Widget::TouchEventType::CANCELED:
        log("LeftButton Released");
        if (ButtonController::getInstance()) {
            auto _character = Character::getInstance(&info)->getCharacter(0);
            if (_character) {
                _character->setLeftButtonDown(false);
            }
        }
        break;
    }

});

    addChild(_leftButton);

    _upButton = ui::Button::create("Buttons/Icon43.png");
    _upButton->setContentSize(Size(50, 50));
    _upButton->setPosition(Vec2(900, 40));
    _upButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            log("UpButton Pressed");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setUpButtonDown(true);
                    
                }
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("UpButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setUpButtonDown(false);
                    
                }
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            log("UpButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setUpButtonDown(false);
                }
            }
            break;
        }
        });


    
    addChild(_upButton);
    
    _rightButton = ui::Button::create("Buttons/Icon45.png");
    _rightButton->setContentSize(Size(50, 50));
    _rightButton->setPosition(Vec2(300, 40));
    _rightButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            log("RightButton Pressed");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(true);
                }
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("RightButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(false);
                }
            }
        case ui::Widget::TouchEventType::CANCELED:
            log("RIghtButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(false);
                }
            }
            break;
        }
        });
    addChild(_rightButton);

    _downButton = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    _downButton->setScale(2.0f);
    _downButton->setContentSize(Size(50, 50));
    _downButton->setPosition(Vec2(400, 40));
    _downButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            log("DownButton Pressed");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setDownButtonDown(true);
                }
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("DownButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setDownButtonDown(false);
                }
            }
        case ui::Widget::TouchEventType::CANCELED:
            log("DownButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setDownButtonDown(false);
                }
            }
            break;
        }
        });
    addChild(_downButton);

    _stopMenu = ui::Button::create("Buttons/Icon06.png");
    _stopMenu->setContentSize(Size(50, 50));
    _stopMenu->setPosition(Vec2(-150, 500));
    _stopMenu->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            log("StopButton Pressed");
            // Tạm dừng game khi nhấn nút stop
            GameManager::getInstance()->pauseGame();
            
            break;
        }
        });



    addChild(_stopMenu);

    addButton(_leftButton);
    addButton(_upButton);
    addButton(_rightButton);
    addButton(_downButton);

    return true;
}

void ButtonController::addButton(ui::Button* button) {
    _buttons.insert(button);
}

bool ButtonController::getButton(ui::Button* button) {
    return (_buttons.find(button) != _buttons.end());
}

ui::Button* ButtonController::getUpButton()
{
    return _upButton;
}

