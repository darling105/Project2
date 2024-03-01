#include "GameManager.h"
#include "audio/include/AudioEngine.h"
#include "Scene/GameScene.h"
#include "Scene/WinningScene.h"
#include "Scene/GameOverScene.h"
#include "Scene/PauseGame.h"
#include "ButtonController/ButtonController.h"
#include "Maps/BaseMap.h"
#include "Maps/Map1.h"

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

void GameManager::endGame()
{
    // Kết thúc trò chơi
    // Ví dụ: Dừng update, dừng âm thanh, hiển thị màn hình kết thúc, ...
    Director::getInstance()->getScheduler()->pauseTarget(Director::getInstance()->getRunningScene());
    AudioEngine::pauseAll();
    // Hiển thị màn hình kết thúc hoặc thực hiện hành động khác tùy thuộc vào yêu cầu của bạn
    auto scene = Director::getInstance()->getRunningScene();
        auto winningScene = WinningScene::create();
        Director::getInstance()->replaceScene(Map1::create());
        log("Game Clicked");
    
}

void GameManager::pauseGame()
{
    _isPaused = true;
    // Pause game ở đây, ví dụ:
    Director::getInstance()->pause();
    AudioEngine::pauseAll();
    showPauseMenu(true);
}

void GameManager::resumeGame()
{
    _isPaused = false;
    Director::getInstance()->resume();
    AudioEngine::resumeAll();
    showPauseMenu(false);
}

void GameManager::gameOver()
{  
   // Director::getInstance()->getScheduler()->pauseTarget(Director::getInstance()->getRunningScene());
    AudioEngine::pauseAll();
    // Hiển thị màn hình kết thúc hoặc thực hiện hành động khác tùy thuộc vào yêu cầu của bạn
    //Director::getInstance()->pause();
    auto gameOverScene = GameOverScene::create();
    Director::getInstance()->getRunningScene()->addChild(gameOverScene, INT_MAX);;
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
