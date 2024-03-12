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

    EntityInfo info("character");
    _leftButton = ui::Button::create("Buttons/Icon44.png");
    _leftButton->setScale(1.3);
    _leftButton->setContentSize(Size(50, 50));
    _leftButton->setPosition(Vec2(-75, -30));
    _leftButton->setOpacity(170.0f);
    _leftButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setLeftButtonDown(true);
                }
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            _touchMovedPos = Vec2::ZERO;
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setLeftButtonDown(false);
                }
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            _touchMovedPos = Vec2::ZERO;
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setLeftButtonDown(false);
                    _character->setRightButtonDown(false);
                }
            }
            break;
        case ui::Widget::TouchEventType::MOVED:
            _touchMovedPos = _leftButton->getTouchMovePosition();
            break;
        }

        });

    addChild(_leftButton);

    _upButton = ui::Button::create("Buttons/Icon43.png");
    _upButton->setScale(1.1);
    _upButton->setContentSize(Size(50, 50));
    _upButton->setPosition(Vec2(1080, 50));
    _upButton->setOpacity(170.0f);
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
    _rightButton->setScale(1.3);
    _rightButton->setContentSize(Size(50, 50));
    _rightButton->setPosition(Vec2(100, -30));
    _rightButton->setOpacity(170.0f);
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
            _touchMovedRightPos = Vec2::ZERO;
            log("RightButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(false);
                }
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            _touchMovedRightPos = Vec2::ZERO;
            log("RightButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(false);
                    _character->setLeftButtonDown(false);
                }
            }
            break;
        case ui::Widget::TouchEventType::MOVED:
            _touchMovedRightPos = _rightButton->getTouchMovePosition();
            break;
        }
        });
    addChild(_rightButton);

    _downButton = ui::Button::create("Buttons/Icon40.png");
    _downButton->setScale(1.1f);
    _downButton->setContentSize(Size(50, 50));
    _downButton->setPosition(Vec2(1080, -50));
    _downButton->setOpacity(170.0f);
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
            break;
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
            // _stopMenu->setVisible(false);
            GameManager::getInstance()->pauseGame();

            break;

        }
        });
    addChild(_stopMenu);
    addButton(_leftButton);
    addButton(_upButton);
    addButton(_rightButton);
    addButton(_downButton);
    addButton(_stopMenu);
    this->scheduleUpdate();
    return true;
}

void ButtonController::addButton(ui::Button* button) {
    _buttons.insert(button);
}

bool ButtonController::getButton(ui::Button* button) {
    return (_buttons.find(button) != _buttons.end());
}

ui::Button* ButtonController::getPauseButton()
{
    return _stopMenu;
}

void ButtonController::showStopMenu(bool show)
{
    _stopMenu->setVisible(true);
}

void ButtonController::update(float dt) {
    Rect boundingbox = _rightButton->getBoundingBox();
    Vec2 pos1 = Vec2(55, -75);
    Vec2 rightPos = _rightButton->getPosition();
    Vec2 worldright = this->convertToWorldSpace(rightPos);
    Vec2 newpos = worldright - rightPos + pos1;
    Rect bound2 = { newpos.x - 10, newpos.y - 4, 110, 98};
   
    auto adjustLeftTouch = Vec2(_touchMovedPos.x - 300, _touchMovedPos.y - 160);
    auto adjustRightTouch = Vec2(_touchMovedRightPos.x - 300, _touchMovedRightPos.y - 160);

    /*DrawNode* drawNodeRight = DrawNode::create();
    this->addChild(drawNodeRight);
    drawNodeRight->drawPoint(adjustRightTouch, 5, Color4F::RED);

    DrawNode* drawNode = DrawNode::create();
    this->addChild(drawNode);
    drawNode->drawPoint(adjustLeftTouch, 5, Color4F::RED);*/


    Rect leftBoundingBox = _leftButton->getBoundingBox();
    Vec2 leftPos = _leftButton->getPosition();
    Vec2 worldLeft = this->convertToWorldSpace(leftPos);
    Vec2 minLeftPos = Vec2(-123, -75);
    Vec2 newLeftPos = worldLeft - leftPos + minLeftPos;
    Rect boundLeft = { newLeftPos.x  - 10, newLeftPos.y - 4, 112, 100};

    EntityInfo info("character");
    auto _charInstance = Character::getInstance(&info);
    auto _char = _charInstance->getCharacter(0);

    /*DrawNode* drawNode2 = DrawNode::create();
    this->addChild(drawNode2);
    Vec2 bound2TopLeft = Vec2(boundLeft.getMinX(), boundLeft.getMaxY());
    Vec2 bound2BottomRight = Vec2(boundLeft.getMaxX(), boundLeft.getMinY());
    drawNode2->drawRect(bound2TopLeft, bound2BottomRight, Color4F::BLUE);

    DrawNode* drawNode22 = DrawNode::create();
    this->addChild(drawNode22);
    Vec2 bound2TopLeftt = Vec2(bound2.getMinX(), bound2.getMaxY());
    Vec2 bound2BottomRightt = Vec2(bound2.getMaxX(), bound2.getMinY());
    drawNode22->drawRect(bound2TopLeftt, bound2BottomRightt, Color4F::RED);*/

    if (bound2.containsPoint(this->convertToWorldSpace(adjustLeftTouch))) {
        _char->setRightButtonDown(true);
        _char->setLeftButtonDown(false);
    }
    else if (boundLeft.containsPoint(this->convertToWorldSpace(adjustRightTouch))) {
            _char->setRightButtonDown(false);
            _char->setLeftButtonDown(true);
    }

    if (boundLeft.containsPoint(this->convertToWorldSpace(adjustLeftTouch))) {
        _char->setRightButtonDown(false);
        _char->setLeftButtonDown(true);
    }
    else if (bound2.containsPoint(this->convertToWorldSpace(adjustRightTouch))) {
        _char->setRightButtonDown(true);
        _char->setLeftButtonDown(false);
    }
}

void ButtonController::onEnter() {
    Node::onEnter();
    this->scheduleUpdate();
}

