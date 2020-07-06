#pragma once

#ifndef __BONUS_WHEEL_H__
#define __BONUS_WHEEL_H__

#include "cocos2d.h"

class BonusWheel : public cocos2d::Sprite
{
public:
	static BonusWheel* create(std::string wheelBorderFile, std::string wheelSectionFile);

	// Add BonusWheel parts
	void addWheelSections(int numOfSections, const std::string sectionFiles[], const std::string sectionLabels[], const int dropChance[]);
	void addArrow(std::string wheelArrowFile);

	// Getters
	int getNumOfSections();
	cocos2d::Sprite* getSectionReward(int section);
	int getWinningSectionNumber();

	// Spin the wheel
	// Returns rotating action
	cocos2d::TargetedAction* spin();


private:
	// Add a single section
	void addSection(int section, std::string sectionFile, std::string sectionLabel);
	
	// Sections' attributes
	int numOfSections;
	int *dropChances;

	Sprite** sectionRewards;

	// BonusWheel parts
	Sprite* wheelArrow;
	Sprite* wheelSections;

	// Winning section number
	int winningSection = -1;
};


#endif // __BONUS_WHEEL_H__