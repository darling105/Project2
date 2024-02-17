#include "SettingScene.h"
#include "fstream"
#include "iostream"
#include "ui/CocosGUI.h"
#include "Scene/MainMenuScene.h"
#include "AudioManager/AudioManager.h"
#include "audio/include/AudioEngine.h"


Scene* SettingScene::create()
{
	auto newObject = new SettingScene();
	if (newObject != nullptr && newObject->init())
	{
		newObject->autorelease();
		return newObject;
	}
	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool SettingScene::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto _background = Sprite::create("BackGround/Background1.png");
	_background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	_background->setScale(2.25f);
	this->addChild(_background);
	Vector<MenuItem*> MenuItems;
	//create Back 
	auto miFont = MenuItemFont::create("Back", [&](Ref* sender) {
		auto mainMenuScene = MainMenu::create();
		Director::getInstance()->replaceScene(mainMenuScene);
		log("Main Menu Clicked");
		});
	miFont->setPosition(Vec2(visibleSize.width / 2 - 1100, visibleSize.height / 2 - 50));
	MenuItems.pushBack(miFont);
	auto menuA = Menu::createWithArray(MenuItems);
	this->addChild(menuA, 1);
	//create Slider Audio

	auto slider = ui::Slider::create();
	slider->loadBarTexture("Buttons/SliderBar_ProgressBar.png");
	slider->loadSlidBallTextures("Buttons/Slider02.png");
	slider->loadProgressBarTexture("Buttons/Progress04.png");
	slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	float savedVolume = SettingScene::getSavedVolume(); // Thay thế bằng cách lấy giá trị từ cài đặt cố định của bạn
	slider->setPercent(AudioManager::getInstance()->getMusicVolume() * 100);
	slider->addEventListener(CC_CALLBACK_2(SettingScene::sliderValueChanged, this));

	/*auto slider2 = ui::Slider::create();
	slider2->loadBarTexture("Slider_Back.png");
	slider2->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	slider2->loadProgressBarTexture("Slider_PressBar.png");
	slider2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-50));
	slider2->addEventListener(CC_CALLBACK_2(SettingScene::sliderValueChanged, this));
	this->addChild(slider2);*/
	this->addChild(slider);
	AudioManager::getInstance()->playMusic("bgmusic.mp3");
	return true;
}


void SettingScene::goToMainMenuScene()
{
	Director::getInstance()->popScene();
}

void SettingScene::sliderValueChanged(Ref* sender, ui::Slider::EventType type)
{
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		auto slider = dynamic_cast<ui::Slider*>(sender);
		if (slider)
		{
			float volume = slider->getPercent() / 100.0f;
			// Adjust audio volume based on the slider's value
			AudioManager::getInstance()->setMusicVolume(volume);
			SettingScene::saveVolume(volume);
		}
	}
}

void SettingScene::saveVolume(float volume)
{
	std::ofstream configFile("settings.cfg");
	if (configFile.is_open()) {
		configFile << volume;
		configFile.close();
		std::cout << "Volume saved: " << volume << std::endl;
	}
	else {
		std::cerr << "Failed to open settings.cfg for writing!" << std::endl;
	}
}

float SettingScene::getSavedVolume()
{
	float volume = 0.5f; // Giá trị mặc định nếu không tìm thấy tệp cấu hình
	std::ifstream configFile("settings.cfg");
	if (configFile.is_open()) {
		configFile >> volume;
		configFile.close();
		std::cout << "Volume loaded: " << volume << std::endl;
	}
	else {
		std::cerr << "Failed to open settings.cfg for reading!" << std::endl;
	}
	return volume;
}
