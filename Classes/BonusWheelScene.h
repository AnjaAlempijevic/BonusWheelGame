
#ifndef __BONUS_WHEEL_SCENE_H__
#define __BONUS_WHEEL_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "BonusWheel.h"

class BonusWheelScene : public cocos2d::Scene
{
public:
	// Create the BonusWheelScene
    static cocos2d::Scene* createScene();

	// Implement the "static create()" method manually
	CREATE_FUNC(BonusWheelScene);
 
private:
	virtual bool init();
    
	// Add parts of the scene
	void addWheel();
	void addPlayOnButton();

	// CallBack functions
	void enableListenerCallBack(cocos2d::Ref* pSender);
	void pushSceneCallBack(cocos2d::Ref* pSender, int section);

    // Close callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	// Scene parts
	BonusWheel* bonusWheel;
	cocos2d::ui::Button* buttonPlayOn;

	// Scene attributes
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};


#endif // __BONUS_WHEEL_SCENE_H__
