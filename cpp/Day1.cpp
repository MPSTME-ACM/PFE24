#include <iostream>

#include <string>



using namespace std;



const int numStats = 6; // Number of stats per class

string statNames[numStats] = { "Attack", "Defense", "Mana", "Speed", "Health", "SPower" };

const int numClasses = 4; // Number of classes

string classTypes[numClasses] = { "Knight", "Mage", "Archer", "Thief" };

int classStats[numClasses][numStats] = {

    {5, 8, 1, 3, 10, 3},  // Knight

    {2, 3, 15, 3, 4, 8},  // Mage

    {6, 3, 2, 6, 5, 10},  // Archer

    {4, 4, 3, 10, 5, 6}   // Thief

};

const int numEnemies = 6; // Number of enemies

string enemyNames[numEnemies] = { "Soldier-1", "Soldier-2", "Soldier-3", "Soldier-4", "Soldier-5", "General" }; // Enemy Names

int enemyData[numEnemies][numStats] = {

	{2, 3, 4, 5, 6, 8}, // Enemy 1 Stats

    {2, 3, 4, 5, 6, 8}, // Enemy 2 Stats

    {1, 2, 3, 4, 5, 8}, // Enemy 3 Stats

    {1, 2, 3, 4, 5, 8}, // Enemy 4 Stats

    {2, 3, 4, 5, 6, 8}, // Enemy 5 Stats

    {2, 3, 4, 5, 6, 8}  // Enemy 6 Stats

};

string pName;

int pStats[numStats] = { 0, 0, 0, 0, 0, 0 }, currentMaxStats[numStats] = { 0, 0, 0, 0, 0, 0 };

int pClass = -1, enemyChoice = -1, enemyStats[numStats] = { 0, 0, 0, 0, 0, 0 };

int pLevel = 0, pExp = 0, healthPotionCount = 3, checkPoint = 0;

string sLine = "";

bool bDodgeAttempt = false, inGameLoop = false;
