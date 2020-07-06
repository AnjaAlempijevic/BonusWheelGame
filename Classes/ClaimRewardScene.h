#pragma once
#ifndef __CLAIM_REWARD_SCENE_H__
#define __CLAIM_REWARD_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

class ClaimRewardScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(cocos2d::Sprite* reward);
	CREATE_FUNC(ClaimRewardScene);

private:
	virtual bool init();

	// Add scene parts
	void addClaimButton();
	void addReward();

	// Scene parts
	cocos2d::Sprite* reward;
	cocos2d::ui::Button* buttonClaim;

	// Reward old arguments
	cocos2d::Node* rewardParent;
	cocos2d::Vec2 rewardPosition;

	// Scene attributes
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

#endif //__CLAIM_REWARD_SCENE_H__