#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

class GameManager
{
public:
    static GameManager* getInstance();
    void endMap();
    void pauseGame();
    void resumeGame();
    void gameOver();
    void showPauseMenu(bool show);

private:
    GameManager();
    static GameManager* _instance;
    bool _isPaused;
    bool isMap1Completed();
};

#endif // __GAME_MANAGER_H__