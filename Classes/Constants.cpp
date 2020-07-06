#include "Constants.h"

// Wheel background file names 
const std::string Constants::wheelBorderFile = "wheel_border.png";
const std::string Constants::wheelSectionFile = "wheel_sections_8.png";

// Wheel section file names and labels
const int Constants::numOfSections = 8;
const std::string Constants::wheelSectionFiles[]{ "heart.png", "brush.png", "gem.png", "hammer.png", "coin.png", "brush.png", "gem.png", "hammer.png" };
const std::string Constants::wheelSectionLabels[]{ "30 min", "x3", "x35", "x3", "x750", "x1", "x75", "x1" };

// Wheel section drop chances
const int Constants::wheelDropChances[]{ 20, 10, 10, 10, 5, 20, 5, 20 };

// Wheel arrow file name
const std::string Constants::wheelArrowFile = "wheel_arrow.png";

// Play button attributes
const std::string Constants::buttonPlayFile = "spin_button.png";
const std::string Constants::buttonPlayLabel = "Play On";

// Claim reward button attributes
const std::string Constants::buttonClaimFile = "spin_button.png";
const std::string Constants::buttonClaimLabel = "Claim";

// Rotation duration
const double Constants::wheelRotationDuration = 4;

// Reward scaling attributes
const double Constants::rewardScale = 1.5;
const double Constants::rewardScaleDuration = 1;

// Font attributes
const double Constants::outlineWidth = 1;
const double Constants::fontScale = 0.5;

const std::string Constants::ttfFontName = "fonts/arial.ttf";
