#include "ClaimRewardScene.h"
#include "Constants.h"

cocos2d::Scene* ClaimRewardScene::createScene(cocos2d::Sprite* reward)
{
	// Create ClaimRewardScene instance
	ClaimRewardScene* scene = new ClaimRewardScene();
	
	scene->reward = reward;

	// Memorize old reward attributes
	scene->rewardParent = reward->getParent();
	scene->rewardPosition = reward->getPosition();

	scene->init();
	return scene;
}

bool ClaimRewardScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// Set scene attributes
	this->visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	this->origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Add button
	this->addClaimButton();

	// Add reward
	this->addReward();
		
	return true;

	}

void ClaimRewardScene::addClaimButton()
{
	// Create ClaimRewardButton
	this->buttonClaim = cocos2d::ui::Button::create(Constants::buttonClaimFile);
	// Add label
	auto buttonLabel = cocos2d::Label::createWithTTF(Constants::buttonClaimLabel, Constants::ttfFontName, this->buttonClaim->getContentSize().height * Constants::fontScale);
	buttonLabel->enableOutline(cocos2d::Color4B::GRAY, Constants::outlineWidth);
	this->buttonClaim->setTitleLabel(buttonLabel);

	// Position button on the screen
	this->buttonClaim->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 10));
	this->buttonClaim->setScale(visibleSize.height / this->buttonClaim->getContentSize().height / 10);

	// Set touch listener 
	this->buttonClaim->addTouchEventListener([&](Ref * sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			this->reward->retain();

			// Return reward to the old parent
			this->reward->removeFromParent();
			this->rewardParent->addChild(this->reward);

			// Set old position to the reward
			this->reward->setScale(1);
			this->reward->setPosition(this->rewardPosition);

			this->reward->release();

			// Put the wheel into ZERO position
			this->rewardParent->getParent()->setRotation(0);

			// Pop ClaimReward scene
			cocos2d::Director::getInstance()->popScene();
		}

		});

	this->addChild(this->buttonClaim, 0);
}

void ClaimRewardScene::addReward()
{
	// Get reward position on the screen
	cocos2d::Vec2 point = this->reward->getPosition();
	cocos2d::Vec2 parentPoint = this->reward->getParent()->convertToWorldSpace(point);

	// Add reward as a scene child
	this->reward->retain();

	this->reward->removeFromParent();
	this->addChild(reward);

	reward->release();

	// Set reward position
	this->reward->setPosition(parentPoint);
							  // sectionDummy - wheelSections - wheel 
	this->reward->setScale(this->rewardParent->getParent()->getParent()->getScale());

	// Run reward actions
	// Run ScaleTo
	auto scaleAction = cocos2d::ScaleTo::create(Constants::rewardScaleDuration, this->reward->getScale() * Constants::rewardScale);
	this->reward->runAction(scaleAction);
	// Run MoveTo
	auto moveTo = cocos2d::MoveTo::create(Constants::rewardScaleDuration, cocos2d::Vec2(reward->getPosition().x, reward->getPosition().y - 2 * reward->getContentSize().height * this->reward->getScale()));
	this->reward->runAction(moveTo);
}


