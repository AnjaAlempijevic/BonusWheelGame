#include "BonusWheelScene.h"
#include "Constants.h"
#include "ClaimRewardScene.h"

USING_NS_CC;

cocos2d::Scene* BonusWheelScene::createScene()
{
    return BonusWheelScene::create();
}

// Initialize an instance
bool BonusWheelScene::init()
{
    // Super init
    if ( !Scene::init() )
        return false;

	// Set scene attributes
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	/*
    // "Close" icon to exit the progress
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(BonusWheelScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        closeItem->setPosition( Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + visibleSize.height - closeItem->getContentSize().height / 2) );
    }

    // Create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ANCHOR_TOP_RIGHT);
    this->addChild(menu, 1);
	*/

	// Scene    

	// Add wheel
	this->addWheel();

	// Add button
	this->addPlayOnButton();

    return true;
}

void BonusWheelScene::addWheel()
{
	// Create the BonusWheel
	bonusWheel = BonusWheel::create(Constants::wheelBorderFile, Constants::wheelSectionFile);

	// Add wheel sections
	bonusWheel->addWheelSections(Constants::numOfSections, Constants::wheelSectionFiles, Constants::wheelSectionLabels, Constants::wheelDropChances);

	// Add arrow
	bonusWheel->addArrow(Constants::wheelArrowFile);

	// Position the bonus wheel sprite on the screen
	bonusWheel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 6 / 10));
	bonusWheel->setScale(visibleSize.width / bonusWheel->getContentSize().width * 0.9);

	// Add the sprite as a child to this layer
	this->addChild(bonusWheel, 0);
}

void BonusWheelScene::addPlayOnButton()
{
	// Create the play button
	this->buttonPlayOn = cocos2d::ui::Button::create(Constants::buttonPlayFile);
	
	// Add label
	auto buttonLabel = cocos2d::Label::createWithTTF(Constants::buttonPlayLabel, Constants::ttfFontName, this->buttonPlayOn->getContentSize().height * Constants::fontScale);
	buttonLabel->enableOutline(cocos2d::Color4B::GRAY, Constants::outlineWidth);
	this->buttonPlayOn->setTitleLabel(buttonLabel);

	// Position button on the screen
	this->buttonPlayOn->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10));
	this->buttonPlayOn->setScale(visibleSize.height / this->buttonPlayOn->getContentSize().height / 10);

	// Set touch listener 
	this->buttonPlayOn->addTouchEventListener([&](Ref * sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			// Disable touch listener
			this->buttonPlayOn->setTouchEnabled(false);

			// Creating an action sequence
			cocos2d::TargetedAction* rotation = this->bonusWheel->spin(); // Rotation
			cocos2d::FiniteTimeAction* enableListener = cocos2d::CallFuncN::create(CC_CALLBACK_1(BonusWheelScene::enableListenerCallBack, this)); // Enable Listener	
			cocos2d::FiniteTimeAction* pushScene = cocos2d::CallFuncN::create(CC_CALLBACK_1(BonusWheelScene::pushSceneCallBack, this, this->bonusWheel->getWinningSectionNumber())); // Push ClaimRewardScene

			cocos2d::Sequence* seq = cocos2d::Sequence::create(rotation, enableListener, pushScene, NULL);

			// Run sequence of actions
			this->runAction(seq);
		}
		
		});

	this->addChild(this->buttonPlayOn, 0);
}

void BonusWheelScene::enableListenerCallBack(cocos2d::Ref* pSender)
{
	this->buttonPlayOn->setTouchEnabled(true);
}

void BonusWheelScene::pushSceneCallBack(cocos2d::Ref* pSender, int section)
{
	// Push Claim Reward Scene on top
	cocos2d::Sprite* reward = this->bonusWheel->getSectionReward(section);
	cocos2d::Director::getInstance()->pushScene(ClaimRewardScene::createScene(reward));
}

void BonusWheelScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/* To navigate back to native iOS screen(if present) without quitting the application,
	do not use Director::getInstance()->end() as given above,
	instead trigger a custom event created in RootViewController.mm as below */

	// EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}

