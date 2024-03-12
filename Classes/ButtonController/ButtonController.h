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
    ui::Button* getPauseButton();
    void showStopMenu(bool show);
protected:
    void onEnter() override;
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
    bool _stopMenuPressed = false;
    ui::Button* _upButton;
    ui::Button* _leftButton;
    ui::Button* _rightButton;
    ui::Button* _downButton;
    ui::Button* _stopMenu;

    Vec2 _touchMovedPos;
    Vec2 _touchMovedRightPos;

    void update(float dt);

};

#endif // __BUTTON_CONTROLLER_H__
