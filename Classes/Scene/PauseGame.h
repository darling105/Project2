#ifndef __PAUSE_GAME_H__
#define __PAUSE_GAME_H__

#include "cocos2d.h"
USING_NS_CC;

class PauseGame : public Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(PauseGame);

    // Hàm hiển thị và ẩn menu
    void show();
    void hide();

private:
    // Các hàm xử lý sự kiện nhấn nút
    void onResumeButtonClicked(Ref* sender);

    // Các thành phần UI, chẳng hạn các nút
    
};

#endif // !__PAUSE_GAME_H__
