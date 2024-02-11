#include "ButtonController.h"
#include "ui/CocosGUI.h"
#include "Character/Character.h"

USING_NS_CC;

ButtonController* ButtonController::_instance = nullptr;

ButtonController* ButtonController::getInstance() {
    if (!_instance) {
        _instance = new (std::nothrow) ButtonController();
        if (_instance && _instance->init()) {
            _instance->autorelease();
        }
        else {
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

ButtonController* ButtonController::create() {
    ButtonController* controller = new (std::nothrow) ButtonController();
    if (controller && controller->init()) {
        controller->autorelease();
        return controller;
    }
    CC_SAFE_DELETE(controller);
    return nullptr;
}

bool ButtonController::init() {
    if (!Node::init()) {
        return false;
    }
    EntityInfo info(1, "character");

    _leftButton = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    _leftButton->setContentSize(Size(50, 50));
    _leftButton->setPosition(Vec2(100, 100));
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
    case ui::Widget::TouchEventType::MOVED:
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

    _upButton = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    _upButton->setContentSize(Size(50, 50));
    _upButton->setPosition(Vec2(200, 200));
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
        case ui::Widget::TouchEventType::MOVED:
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

    _rightButton = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    _rightButton->setContentSize(Size(50, 50));
    _rightButton->setPosition(Vec2(300, 100));
    _rightButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            log("UpButton Pressed");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(true);
                }
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("UpButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(false);
                }
            }
        case ui::Widget::TouchEventType::MOVED:
            log("UpButton Released");
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
    _downButton->setContentSize(Size(50, 50));
    _downButton->setPosition(Vec2(400, 100));
    //addChild(_downButton);

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

