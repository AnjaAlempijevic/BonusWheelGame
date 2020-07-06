#include "BonusWheel.h"
#include "Constants.h"

BonusWheel* BonusWheel::create(std::string wheelBorderFile, std::string wheelSectionsFile)
{
	// Create a BonusWheel instance
	// Initialize it with a border file
	BonusWheel* wheel = new BonusWheel();
	wheel->initWithFile(wheelBorderFile);

	// Add a Sprite to hold wheel sections
	wheel->wheelSections = Sprite::create(wheelSectionsFile);

	// Position wheel sections in the center of the wheel
	wheel->wheelSections->setPosition(cocos2d::Vec2(wheel->getContentSize().width / 2, wheel->getContentSize().height / 2));
	wheel->wheelSections->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

	wheel->addChild(wheel->wheelSections, -1);

	return wheel;
}

void BonusWheel::addWheelSections(int numOfSections, const std::string sectionFiles[], const std::string sectionLabels[], const int dropChance[])
{
	this->numOfSections = numOfSections;
	this->sectionRewards = new Sprite*[numOfSections];

	// Add rewards to wheel sections
	for (int i = 0; i < numOfSections; i++)
	{
		this->addSection(i, sectionFiles[i], sectionLabels[i]);
	}

	// Form a drop chance percent array
	this->dropChances = new int[numOfSections];

	for (int i = 0; i < numOfSections; i++)
		this->dropChances[i] = (i > 0)? this->dropChances[i - 1] + dropChance[i] : dropChance[i];

	// Set random number generator seed
	srand(time(nullptr));
}

void BonusWheel::addArrow(std::string wheelArrowFile)
{
	// Add a sprite to hold wheel arrow
	this->wheelArrow = Sprite::create(wheelArrowFile);

	// Position arrow in the top center of the wheel
	this->wheelArrow->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height - this->wheelArrow->getContentSize().height / 3));

	this->addChild(this->wheelArrow, 0);
}

int BonusWheel::getNumOfSections()
{
	return this->numOfSections;
}

cocos2d::Sprite* BonusWheel::getSectionReward(int section) 
{
	return this->sectionRewards[section];
}

int BonusWheel::getWinningSectionNumber()
{
	return this->winningSection;
}


cocos2d::TargetedAction* BonusWheel::spin()
{
	// Generate a random number between 0 and 99
	int randomNum = rand() % 100;

	// Determine a winning section based on the drop chance probabilities
	int section;
	for (section = 0; section < this->numOfSections; section++)
		if (randomNum < this->dropChances[section]) break;

	this->winningSection = section;

	// Create rotating action
	auto rotation = cocos2d::RotateBy::create(Constants::wheelRotationDuration, 360 + 360 / this->numOfSections * (this->numOfSections - section - 0.5));
	auto easeRotation = cocos2d::EaseExponentialOut::create(rotation);

	return cocos2d::TargetedAction::create(this->wheelSections, easeRotation);
}


void BonusWheel::addSection(int section, std::string sectionFile, std::string label)
{
	// Create a sprite to hold and position a section on the wheel.
	auto sectionDummy = Sprite::create();
	sectionDummy->setContentSize(this->getContentSize());

	// Position it in the center of the wheel
	sectionDummy->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	sectionDummy->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));


	// Create a sprite to hold wheel section reward
	auto reward = Sprite::create(sectionFile);
		
	// Set uniform reward size
	if (section > 0)
		reward->setContentSize(sectionRewards[0]->getContentSize());


	// Create label
	auto sectionLabel = cocos2d::Label::createWithTTF(label, Constants::ttfFontName, reward->getContentSize().height * Constants::fontScale);
	sectionLabel->enableOutline(cocos2d::Color4B::BLACK, Constants::outlineWidth);

	// Add label to reward
	reward->addChild(sectionLabel, 0);
	sectionLabel->setAnchorPoint(cocos2d::Vec2(0, 0));
	

	// Add section reward to the positioning sprite
	sectionDummy->addChild(reward, 0);

	// Position section reward on the wheel
	reward->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height - reward->getContentSize().height * 1.5));
	sectionDummy->setRotation(360 / numOfSections * section + 360 / numOfSections / 2);


	// Add section to wheel sections sprite
	this->wheelSections->addChild(sectionDummy, 0);
		


	// Assign the pointer to rewards array
	this->sectionRewards[section] = reward;
}
