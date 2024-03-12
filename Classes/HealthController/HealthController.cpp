#include "HealthController.h"

HealthController* HealthController::_instance;

HealthController* HealthController::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) HealthController();
        _instance->init();
    }
    return _instance;
}

bool HealthController::init()
{
    if (!Node::init())
    {
        return false;
    }

    // Tạo Clipping Node
    _clippingNode = ClippingNode::create();
    _clippingNode->setInverted(false); // Hiển thị phần được cắt
    addChild(_clippingNode);

    // Tạo Sprite đại diện cho thanh máu
    _healthBar = Sprite::create("Character/Health/Healthbar_full.png");
    _healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT); // Đặt Anchor Point ở góc dưới bên trái


    // Thêm Sprite thanh máu vào Clipping Node
    _clippingNode->addChild(_healthBar);

    // Tạo mặt nạ cho Clipping Node
    _stencil = DrawNode::create();
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0); // Bắt đầu từ góc dưới bên trái
    rectangle[1] = Vec2(_healthBar->getContentSize().width, 0);
    rectangle[2] = Vec2(_healthBar->getContentSize().width, _healthBar->getContentSize().height);
    rectangle[3] = Vec2(0, _healthBar->getContentSize().height);
    Color4F white(1, 1, 1, 1);
    _stencil->drawPolygon(rectangle, 4, white, 1, white);
    //this->addChild(_stencil);
    // Đặt lại kích thước của mặt nạ dựa trên kích thước mới của healthBar
    Size healthBarSize = _healthBar->getContentSize();
    _stencil->setContentSize(healthBarSize);
    _stencil->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    // Đặt lại vị trí của mặt nạ để bắt đầu từ góc dưới bên trái của healthBar
    //_stencil->setPosition(Vec2(-_healthBar->getAnchorPointInPoints().x, -_healthBar->getAnchorPointInPoints().y));

    // Đặt mặt nạ cho Clipping Node
    _clippingNode->setStencil(_stencil);
    _clippingNode->setPosition(Vec2::ZERO); // Đặt vị trí của Clipping Node
    _clippingNode->setContentSize(_healthBar->getContentSize()); // Đặt kích thước của Clipping Node

    // Đặt lại vị trí của mặt nạ để bắt đầu từ góc dưới bên trái của Clipping Node
    _stencil->setPosition(Vec2::ZERO);

    return true;
}





void HealthController::setCurrentHealth(float newVal)
{
    _currentHealth = newVal;
    onChangeCurrent(_currentHealth);
}

float HealthController::getCurrentHealth()
{
    return _currentHealth;
}

void HealthController::setMaxHealth(float newVal)
{
    _maxHealth = newVal;
}

float HealthController::getMaxHealth()
{
    return _maxHealth;
}

void HealthController::onChangeCurrent(float newVal)
{
    if (newVal <= 0)
    {
        _currentHealth = 0;
    }

    // Tính toán tỷ lệ phần trăm của currentHealth so với maxHealth
    float percentage = (_currentHealth / _maxHealth);

    // Độ dài thực tế của thanh máu sau khi cắt đi 1/3 từ phải sang trái
    float actualLength = _healthBar->getContentSize().width * percentage;

    // Cập nhật kích thước của mặt nạ theo tỷ lệ phần trăm
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(actualLength - 2.0f, 0); // Chiều dài cắt bớt
    rectangle[2] = Vec2(actualLength - 2.0f, 24); // Chiều rộng thanh máu
    rectangle[3] = Vec2(0, 24); // Chiều rộng thanh máu
    _stencil->clear();
    _stencil->drawPolygon(rectangle, 4, Color4F::WHITE, 1, Color4F::WHITE);

}


