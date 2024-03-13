#include "SettingScene.h"
#include "Camera/CameraFollow.h"
bool SettingScene::init()
{
    if (!LayerColor::initWithColor(cocos2d::Color4B(0, 0, 0, 0)))
    {
        return false;
    }
    auto overlayLayer = LayerColor::create(Color4B(0, 0, 0, 0));
    overlayLayer->setContentSize(Director::getInstance()->getVisibleSize());
    overlayLayer->setPosition(Vec2::ZERO);
    this->addChild(overlayLayer, -1);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool {
        return true;
        };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, overlayLayer);

    auto settingWindow = Sprite::create("BackGround/Setting.png");
    settingWindow->setScale(2.0f);
    //settingWindow->setPosition(Director::getInstance()->getVisibleSize() *2);
    this->addChild(settingWindow);

    auto settingWindowSize = settingWindow->getContentSize();

    auto backButton = MenuItemImage::create("Buttons/Icon02.png", "Buttons/Icon02.png", CC_CALLBACK_1(SettingScene::goBack, this));

    auto menu = Menu::create(backButton, nullptr);
    menu->setPosition(Vec2(settingWindowSize.width / 2, settingWindowSize.height / 8));
    settingWindow->addChild(menu);

    float musicVolume = UserDefault::getInstance()->getFloatForKey("MusicVolume", AudioManager::getInstance()->getMusicVolume());

    auto slider = ui::Slider::create();
    slider->loadBarTexture("Buttons/SliderBar_ProgressBar.png");
    slider->loadSlidBallTextures("Buttons/Slider02.png");
    slider->loadProgressBarTexture("Buttons/Progress04.png");
    slider->setPosition(Vec2(settingWindowSize.width / 2, settingWindowSize.height / 1.6));
    slider->setPercent(musicVolume * 100);
    slider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            auto s = dynamic_cast<ui::Slider*> (sender);
            if (s) {
                float volume = (float)s->getPercent() / 100;
                AudioManager::getInstance()->setMusicVolume(volume);

                UserDefault::getInstance()->setFloatForKey("MusicVolume", volume);
                UserDefault::getInstance()->flush();
            }
        }
        });
    settingWindow->addChild(slider);

    float sfxVolume = UserDefault::getInstance()->getFloatForKey("SfxVolume", AudioManager::getInstance()->getSFXVolume());

    auto sliderSFX = ui::Slider::create();
    sliderSFX->loadBarTexture("Buttons/SliderBar_ProgressBar.png");
    sliderSFX->loadSlidBallTextures("Buttons/Slider02.png");
    sliderSFX->loadProgressBarTexture("Buttons/Progress04.png");
    sliderSFX->setPosition(Vec2(settingWindowSize.width / 2, settingWindowSize.height / 2.5));
    //sliderSFX->setScale(1.5);
    sliderSFX->setPercent(sfxVolume * 100);
    sliderSFX->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            auto sfx = dynamic_cast<ui::Slider*> (sender);
            if (sfx) {
                float volumesfx = (float)sfx->getPercent() / 100;
                AudioManager::getInstance()->setSFXVolume(volumesfx);

                UserDefault::getInstance()->setFloatForKey("SfxVolume", volumesfx);
                UserDefault::getInstance()->flush();
            }
        }
        });
    settingWindow->addChild(sliderSFX);

    auto musicLabel = Label::createWithTTF("Music", "fonts/Planes_ValMore.ttf", 30);
    musicLabel->setPosition(Vec2(settingWindowSize.width / 2, settingWindowSize.height / 1.4));
    settingWindow->addChild(musicLabel);
    auto sfxLabel = Label::createWithTTF("SFX", "fonts/Planes_ValMore.ttf", 30);
    sfxLabel->setPosition(Vec2(settingWindowSize.width / 2, settingWindowSize.height / 2.0));
    settingWindow->addChild(sfxLabel);
    this->scheduleUpdate();
    return true;
}

void SettingScene::goBack(Ref* sender)
{
    this->removeFromParent();
}
void SettingScene::onEnter()
{
    LayerColor::onEnter(); // Gọi phương thức onEnter của lớp cha

    // Lấy thông tin camera
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();

    // Lấy vị trí của camera
    auto cameraPosition = camera->getPosition();

    // Đặt vị trí mới cho PauseGame
    this->setPosition(cameraPosition);

    // Thêm PauseGame vào CameraFollow (nếu có)
    if (auto cameraFollow = dynamic_cast<CameraFollow*>(camera->getParent())) {
        cameraFollow->addChild(this);
    }
}