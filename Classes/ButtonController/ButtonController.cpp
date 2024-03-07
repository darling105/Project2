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

    nodeLeftTouch = Node::create();
    nodeLeftTouch->setPosition(touchLeftButton.x - 200, touchLeftButton.y);
    this->addChild(nodeLeftTouch);

    nodeRightTouch = Node::create();
    nodeRightTouch->setPosition(touchRightButton.x , touchRightButton.y);
    this->addChild(nodeRightTouch);

    EntityInfo info("character");
    _leftButton = ui::Button::create("Buttons/Icon44.png");
    _leftButton->setContentSize(Size(50, 50));
    _leftButton->setPosition(Vec2(-75, -30));
    _leftButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            previousTouchPos = _leftButton->getTouchBeganPosition();
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setLeftButtonDown(true);
                }
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            nodeLeftTouch->setPosition(touchLeftButton.x - 200, touchLeftButton.y);
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setLeftButtonDown(false);
                }
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            _moveLeftPos = Vec2::ZERO;
            
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
            _moveLeftPos = _touchMovedPos - previousTouchPos;
            nodeLeftTouch->setPosition(_moveLeftPos.x - 78, _moveLeftPos.y - 30);
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
    _rightButton->setPosition(Vec2(100, -30));
    _rightButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            previousTouchRightPos = _rightButton->getTouchBeganPosition();
            log("RightButton Pressed");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(true);
                }
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            nodeRightTouch->setPosition(touchRightButton.x - 100, touchRightButton.y);
            log("RightButton Released");
            if (ButtonController::getInstance()) {
                auto _character = Character::getInstance(&info)->getCharacter(0);
                if (_character) {
                    _character->setRightButtonDown(false);
                }
            }
            break;
        case ui::Widget::TouchEventType::CANCELED:
            _moveRightPos = Vec2::ZERO;
            log("RIghtButton Released");
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
            _moveRightPos = _touchMovedRightPos - previousTouchRightPos;
            nodeRightTouch->setPosition(_moveRightPos.x + 100, _moveRightPos.y - 30);
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
    Vec2 pos1 = Vec2(48, -75);
    Vec2 rightPos = _rightButton->getPosition();
    Vec2 worldright = this->convertToWorldSpace(rightPos);
    Vec2 newpos = worldright - rightPos + pos1;
    Rect bound2 = { newpos.x + 10, newpos.y + 8, 80, 72 };

    touchLeftButton = Vec2(_moveLeftPos.x - 75, _moveLeftPos.y - 30);
    Vec2 touchLeftButton1 = nodeLeftTouch->getPosition();

    touchRightButton = Vec2(_moveRightPos.x + 100, _moveRightPos.y - 30);
    Vec2 touchRightButton1 = nodeRightTouch->getPosition();

    //DrawNode* drawNode = DrawNode::create();
    //this->addChild(drawNode);
    //drawNode->drawPoint(touchRightButton, 5, Color4F::RED);

    //DrawNode* drawNode1 = DrawNode::create();
    //this->addChild(drawNode1);
    //drawNode1->drawPoint(touchLeftButton, 5, Color4F::RED);

    // Vẽ bound2
    /*DrawNode* drawNode2 = DrawNode::create();
    this->addChild(drawNode2);
    Vec2 bound2TopLeft = Vec2(bound2.getMinX(), bound2.getMaxY());
    Vec2 bound2BottomRight = Vec2(bound2.getMaxX(), bound2.getMinY());
    drawNode2->drawRect(bound2TopLeft, bound2BottomRight, Color4F::BLUE);*/

    //DrawNode* drawNodeTest = DrawNode::create();
    //this->addChild(drawNodeTest);
    //drawNodeTest->drawPoint(nodeRightTouch->getPosition(), 5, Color4F::ORANGE);

    //DrawNode* drawNodeTest1 = DrawNode::create();
    //this->addChild(drawNodeTest1);
    //drawNodeTest1->drawPoint(nodeLeftTouch->getPosition(), 5, Color4F::GREEN);

    Rect leftBoundingBox = _leftButton->getBoundingBox();
    Vec2 leftPos = _leftButton->getPosition();
    Vec2 worldLeft = this->convertToWorldSpace(leftPos);
    Vec2 minLeftPos = Vec2(-127, -75);
    Vec2 newLeftPos = worldLeft - leftPos + minLeftPos;
    Rect boundLeft = { newLeftPos.x + 10, newLeftPos.y + 8, 80, 72 };
    Vec2 newRightMove = Vec2(_moveRightPos.x + 100, _moveRightPos.y - 30);
    EntityInfo info("character");
    auto _charInstance = Character::getInstance(&info);
    auto _char = _charInstance->getCharacter(0);

    if (bound2.containsPoint(this->convertToWorldSpace(touchLeftButton))) {
        _char->setRightButtonDown(true);
        _char->setLeftButtonDown(false);
    }
    else if (boundLeft.containsPoint(this->convertToWorldSpace(touchLeftButton1))) {
            _char->setRightButtonDown(false);
            _char->setLeftButtonDown(true);
    }

    if (boundLeft.containsPoint(this->convertToWorldSpace(touchRightButton))) {
        _char->setRightButtonDown(false);
        _char->setLeftButtonDown(true);
    }
    else if (bound2.containsPoint(this->convertToWorldSpace(touchRightButton1))) {
        _char->setRightButtonDown(true);
        _char->setLeftButtonDown(false);
    }
}

void ButtonController::onEnter() {
    Node::onEnter();
    this->scheduleUpdate();
}

