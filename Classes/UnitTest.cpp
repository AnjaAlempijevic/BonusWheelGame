#include <fstream>

#include "UnitTest.h"

void testFunction(BonusWheel* wheel, int iterations) {
	int* sectionsWinCount = new int[wheel->getNumOfSections()]{ 0 };
	int winningSection = -1;

	std::ofstream myfile;
	myfile.open("Test.txt");

	myfile << iterations << " generated sections: " << std::endl;

	for (int i = 0; i < iterations; i++) {
		wheel->spin();
		winningSection = wheel->getWinningSectionNumber();

		sectionsWinCount[winningSection]++;

		myfile << winningSection + 1 << " ";
	}

	myfile << std::endl << std::endl;

	for (int i = 0; i < wheel->getNumOfSections(); i++)
		myfile << "Section " << i + 1 << ": Number of wins = " << sectionsWinCount[i] << std::endl;

	myfile.close();
}