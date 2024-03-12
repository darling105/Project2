    #include "CameraFollow.h"

    CameraFollow* CameraFollow::create(Node* target, Rect fieldOfView, ButtonController* buttonController, Sprite* healthBar, Sprite* healthEmpty, Label* scoreLabel)
    {
        auto newObject = new CameraFollow();
        if (newObject != nullptr && newObject->init(target, fieldOfView, buttonController, healthBar, healthEmpty, scoreLabel)) {
            newObject->autorelease();
            return newObject;
        }
        CC_SAFE_DELETE(newObject);
        return nullptr;
    }

    bool CameraFollow::init(Node* target, Rect fieldOfView, ButtonController* buttonController, Sprite* healthBar, Sprite* healthEmpty, Label* scoreLabel)
    {
        if (!target) {
            return false;
        }
        _target = target;
        _fieldOfView = fieldOfView;
        _buttonController = buttonController; // Lưu trữ con trỏ đến ButtonController
        _dirty = false;
        _previousPosition = target->getPosition();
        _healthBar = healthBar;
        _healthEmpty = healthEmpty;
        _scoreLabel = scoreLabel;
        Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
        Size cameraSize = size / 2;
        _cameraSize = cameraSize;
        this->scheduleUpdate();
        return true;
    }

    void CameraFollow::update(float dt)
    {
        if (!_target)
            return;

        // Get the camera's position
        cocos2d::Camera* camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
        cocos2d::Vec2 targetPosition = _target->getPosition();
        if (_previousPosition != targetPosition) {
            _previousPosition = targetPosition;
            _dirty = true;
        }
        else {
            _dirty = false;
        }

        float left_x = _fieldOfView.getMinX();
        float down_y = _fieldOfView.getMinY();
        float right_x = _fieldOfView.getMaxX();
        float up_y = _fieldOfView.getMaxY();

        if (targetPosition.x >= left_x && targetPosition.x <= right_x && targetPosition.y >= down_y && targetPosition.y <= up_y) {
            camera->setPosition(targetPosition);
        }
        else {
            if (targetPosition.x < left_x && targetPosition.y < down_y) {
                camera->setPosition(Vec2(left_x, down_y));
            }
            else if (targetPosition.x < left_x && targetPosition.y > up_y) {
                camera->setPosition(Vec2(left_x, up_y));
            }
            else if (targetPosition.x > right_x && targetPosition.y < down_y) {
                camera->setPosition(Vec2(right_x, down_y));
            }
            else if (targetPosition.x > right_x && targetPosition.y > up_y) {
                camera->setPosition(Vec2(right_x, up_y));
            }
            else if (targetPosition.y < down_y) {
                camera->setPosition(Vec2(targetPosition.x, down_y));
            }
            else if (targetPosition.y > up_y) {
                camera->setPosition(Vec2(targetPosition.x, up_y));
            }
            else if (targetPosition.x < left_x) {
                camera->setPosition(Vec2(left_x, targetPosition.y));
            }
            else if (targetPosition.x > right_x) {
                camera->setPosition(Vec2(right_x, targetPosition.y));
            }
        }

        // Cập nhật vị trí của ButtonController
        if (_buttonController) {
            _buttonController->setPosition(camera->getPosition().x - 500, camera->getPosition().y - 200);
        }
        if (_resumeButton) {
            _resumeButton->setPosition(camera->getPosition().x - 500, camera->getPosition().y - 200);
        }
        if (_healthBar) {
            _healthBar->setPosition(camera->getPosition().x + 550, camera->getPosition().y + 300);
        }
        if (_healthEmpty) {
            _healthEmpty->setPosition(camera->getPosition().x + 550, camera->getPosition().y + 300);
        }
        if (_scoreLabel) {
            _scoreLabel->setPosition(camera->getPosition().x + 450, camera->getPosition().y + 300);
        }
    }

    bool CameraFollow::isDirty() const
    {
        return _dirty;
    }
    