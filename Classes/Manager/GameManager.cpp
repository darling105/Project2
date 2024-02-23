#include "GameManager.h"
#include "audio/include/AudioEngine.h"
#include "Scene/GameScene.h"
#include "Scene/PauseGame.h"

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

    // Tạo lớp đối tượng (layer) thông báo
    auto messageLayer = LayerColor::create(Color4B(0, 0, 0, 128)); // Một layer màu đen với độ trong suốt 128
    scene->addChild(messageLayer, INT_MAX); // Đặt layer này lên phía trên cùng
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // Hiển thị thông báo
    auto messageLabel = Label::createWithTTF("Congratulation", "fonts/arial.ttf", 32);
    messageLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    messageLayer->addChild(messageLabel);

    // Đợi một khoảng thời gian trước khi thoát
    messageLayer->runAction(Sequence::create(
        DelayTime::create(2.0f), // Đợi 2 giây
        CallFunc::create([=]() {
            // Thoát khỏi ứng dụng
            /*Director::getInstance()->end();*/
            auto gameScene = GameScene::create();
            Director::getInstance()->replaceScene(gameScene);
            log("Game Clicked");
            }),
        nullptr
    ));
}

void GameManager::pauseGame()
{
    _isPaused = true;
    // Pause game ở đây, ví dụ:
    Director::getInstance()->pause();
    AudioEngine::pauseAll();
    // Nếu bạn có các hoạt động khác cần pause thì thực hiện ở đây
    showPauseMenu(true);
}

void GameManager::resumeGame()
{
    _isPaused = false;
    Director::getInstance()->resume();
    AudioEngine::resumeAll();
    showPauseMenu(false);
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
        auto pauseMenu = Director::getInstance()->getRunningScene()->getChildByName("PauseMenu");
        if (pauseMenu != nullptr) {
            pauseMenu->removeFromParent();
        }
    }
}
