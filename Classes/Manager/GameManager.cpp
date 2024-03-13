#include "GameManager.h"
#include "audio/include/AudioEngine.h"
#include "Scene/GameScene.h"
#include "Scene/WinningScene.h"
#include "Scene/GameOverScene.h"
#include "Scene/PauseGame.h"
#include "ButtonController/ButtonController.h"
#include "Maps/BaseMap.h"
#include "Maps/Map1.h"
#include "Maps/Map2.h"

USING_NS_CC;

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::getInstance()
{
    if (!_instance)
    {
        _instance = new GameManager();
    }
    return _instance;
}

GameManager::GameManager()
{
    // Constructor
}

bool GameManager::isMap1Completed()
{
    return false;
}

void GameManager::endMap()
{
    Director::getInstance()->getScheduler()->pauseTarget(Director::getInstance()->getRunningScene());
   // AudioEngine::pauseAll();
    Scene* currentScene = Director::getInstance()->getRunningScene();
    if (currentScene->getTag() == 10)
    {
        if (isMap1Completed())
        {
            Director::getInstance()->replaceScene(WinningScene::create());
        }
        else
        {
            auto winningScene = WinningScene::create();
            Director::getInstance()->replaceScene(winningScene);
        }
    }
    else if (currentScene->getTag() == 05)
    {
        auto winningScene = WinningScene::create();
        Director::getInstance()->replaceScene(winningScene);
    }
    
}

void GameManager::pauseGame()
{
    _isPaused = true;
    // Pause game ở đây, ví dụ:
    Director::getInstance()->pause();
   // AudioEngine::pauseAll();
    showPauseMenu(true);
}

void GameManager::resumeGame()
{
    _isPaused = false;
    Director::getInstance()->resume();
   // AudioEngine::resumeAll();
    showPauseMenu(false);
}

void GameManager::gameOver()
{  
    //Director::getInstance()->getScheduler()->pauseTarget(Director::getInstance()->getRunningScene());
    //AudioEngine::pauseAll();
    // Hiển thị màn hình kết thúc hoặc thực hiện hành động khác tùy thuộc vào yêu cầu của bạn
    //Director::getInstance()->pause();
    auto gameOverScene = GameOverScene::create();
    auto currentScene = Director::getInstance()->getRunningScene();
    currentScene->addChild(gameOverScene, INT_MAX);
    log("Game Over!");
}

void GameManager::showPauseMenu(bool show)
{
    if (show) {
        // Hiển thị menu tạm dừng
        auto pauseMenu = PauseGame::create();
        Director::getInstance()->getRunningScene()->addChild(pauseMenu, INT_MAX);
    }
    else {
        // Ẩn menu tạm dừng
        auto pauseMenu = Director::getInstance()->getRunningScene()->getChildByName("PauseGame");
        if (pauseMenu != nullptr) {
            pauseMenu->removeFromParent();
        }
    }
}
