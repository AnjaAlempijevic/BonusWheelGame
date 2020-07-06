#include <string>
#pragma once

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "cocos2d.h"

class Constants
{
private:
	Constants() {};

public:
	// Wheel background file names 
	const static std::string wheelBorderFile;
	const static std::string wheelSectionFile;

	// Wheel sections attributes
	const static int numOfSections;
	const static std::string wheelSectionFiles[];
	const static std::string wheelSectionLabels[];

	const static int wheelDropChances[];

	// Wheel arrow file name
	const static std::string wheelArrowFile;

	// Play button attributes
	const static std::string buttonPlayFile;
	const static std::string buttonPlayLabel;

	// Claim reward button attributes
	const static std::string buttonClaimFile;
	const static std::string buttonClaimLabel;

	// Rotation duration
	const static double wheelRotationDuration;

	// Reward scaling attributes
	const static double rewardScale;
	const static double rewardScaleDuration;

	// Font attributes
	const static double outlineWidth;
	const static double fontScale;

	const static std::string ttfFontName;

};

#endif //__CONSTANTS_H__