#ifndef __BUTTON_CONTROLLER_H__
#define __BUTTON_CONTROLLER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ButtonController : public Node
{
public:
    static ButtonController* getInstance();
    void addButton(ui::Button* button);
    bool getButton(ui::Button* button);
    ui::Button* getPressedButton() { return _pressedButton; }
    ui::Button* getUpButton();
private:
    bool init() override;
private:
    static ButtonController* _instance;
    std::set<ui::Button*> _buttons;
    ui::Button* _pressedButton;
    bool _upButtonPressed = false;
    bool _leftButtonPressed = false;
    bool _rightButtonPressed = false;
    bool _downButtonPressed = false;
    ui::Button* _upButton;
    ui::Button* _leftButton;
    ui::Button* _rightButton;
    ui::Button* _downButton;
};

#endif // __BUTTON_CONTROLLER_H__
