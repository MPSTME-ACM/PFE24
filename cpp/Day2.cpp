#include <iostream>
#include <string>
#include <cmath>

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

string activityMenu[3] = {"Main Story", "View Stats", "Inventory"};
int currentTurn = -1;

int main() {
    cout << "What Is Your Name? ";
    cin >> pName;
    
    sLine = string(15, '=');
    cout << sLine << endl << sLine << endl;

    cout << "Story a.1" << endl;

    for (int i = 0; i < 4; ++i) {
        cout << classTypes[i] << endl;
        for (int j = 0; j < 6; ++j) {
            cout << statNames[j] << " - " << classStats[i][j] << endl;
        }
        cout << sLine << endl;
    }

    cout << "Choose Your Class!" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << i << ") " << classTypes[i] << endl;
    }

    cout << "Enter the class number: ";
    cin >> pClass;
    
    cout << "You Have Chosen " << classTypes[pClass] << "!" << endl;
    for (int i = 0; i < 6; ++i) {
        pStats[i] = classStats[pClass][i];
        currentMaxStats[i] = classStats[pClass][i];
    }
    cout << sLine << endl << sLine << endl;
    cout << "Henceforth You Shall Be Known As " << pName << " The " << classTypes[pClass] << endl;
    cout << sLine << endl;

    int enemyStats[6] = {0,0,0,0,0,0};
    int enemyChoice = 0;
    bool inFight = true;
    int valueIndex = 6;

    cout << sLine << endl;
    cout << "You Are Fighting Against " << enemyData[0][enemyChoice] << endl;
    cout << sLine << endl;

    for (int i = 0; i < 6; ++i) {
        enemyStats[i] = enemyData[enemyChoice + 1][i];
    }
    int enemyMaxStats[6];
    for (int i = 0; i < 6; ++i) {
        enemyMaxStats[i] = enemyStats[i];
    }

    int chanceAdditional = 25; // Fixed value for additional chance
    int turnChance = 50 + chanceAdditional;
    int fixed_chance = 50; // Fixed value for turnChance comparison
    if (fixed_chance < turnChance) {
        currentTurn = -1;
    }

    while (inFight && pStats[4] > 0) {
        if (currentTurn == 1) { // Player Turn
            cout << "Your Turn: " << endl;
            cout << "0) Fight\n1) Heal" << endl;
            int fightChoice;
            cin >> fightChoice;

            if (fightChoice == 0) {
                cout << "Choose Your Attack!" << endl;
                cout << "0) Slash\n1) Stab\n2) Magic Bolt\n3) Special Attack\n4) Dodge\n5) Block" << endl;
                int attackType;
                cin >> attackType;
                double enemyDefPercent = 1 - (double)(enemyStats[1]) / 12;
                double damage = 0;
                if (attackType == 0) {
                    cout << pName << " Slashes with all their might!" << endl;
                    damage = pStats[0] * enemyDefPercent;
                } 
                else if (attackType == 1) {
                    cout << pName << " Quickly Stabs the opponent!" << endl;
                    damage = pStats[3] * enemyDefPercent;
                } 
                else if (attackType == 2) {
                    cout << pName << " Casts Magic on the opponent!" << endl;
                    damage = pStats[2] * enemyDefPercent;
                } 
                else if (attackType == 3) {
                    cout << pName << " Uses Their Speciality on the opponent!" << endl;
                    damage = pStats[5] * enemyDefPercent;
                    int critChance = 70; // Fixed value for critical hit
                    if (critChance > 65) {
                        cout << "Critical Hit!" << endl;
                    }
                    damage = (pStats[5] * enemyDefPercent) * (critChance > 65 ? 1.5 : 1);
                } 
                else if (attackType == 4) 
                    bDodgeAttempt = true;

                enemyStats[4] = max(min((int)(enemyStats[4] - floor(damage)), 100), 0);
                cout << pName << " Dealt " << floor(damage) << " Damage!" << endl;
                cout << enemyData[0][enemyChoice] << " Currently Has " << enemyStats[4] << " HP left!" << endl;
                if (enemyStats[4] == 0) {
                    inFight = false;
                    cout << enemyData[0][enemyChoice] << " Has Been Killed!" << endl;
                    break;
                }
            } 
            else if (fightChoice == 1) {
                if (healthPotionCount > 0) {
                    pStats[4] = min(pStats[4] + 5, currentMaxStats[4]);
                    if (pStats[4] == currentMaxStats[4]) 
                        cout << pName << " Has Fully Recovered!" << endl;
                    else 
                        cout << pName << " has been Healed for 5 HP" << endl;
                    cout << pName << " Now Has " << pStats[4] << " HP!" << endl;
                    healthPotionCount--;
                } 
                else 
                    cout << "You have no health potions left!" << endl;
            }
            currentTurn = 0;
        } 
        else { // Enemy Turn
            cout << "Enemy Turn!" << endl;
            cout << sLine << endl;
            int attackOptionChance = 50; // Fixed value for attackOptionChance
            double damage = 0;
            double pDefPercent = 1 - (double)(pStats[1]) / 20; // Fixed value for pDefPercent
            if (attackOptionChance < 15) { // Ultimate Attack
                cout << enemyData[0][enemyChoice] << " Uses Ultimate!" << endl;
                damage = enemyStats[5] * pDefPercent;
            } 
            else if (attackOptionChance < 80) { // Normal Attack
                cout << enemyData[0][enemyChoice] << " Uses Slash!" << endl;
                damage = enemyStats[0] * pDefPercent;
            } 
            else
                cout << enemyData[0][enemyChoice] << " Misses!" << endl;
            pStats[4] = max(pStats[4] - (int)(floor(damage)), 0);
            cout << pName << " Now Has " << pStats[4] << " HP!" << endl;
            if (pStats[4] == 0) {
                cout << pName << " has been defeated!" << endl;
                inFight = false;
            }
            currentTurn = 1;
        }
    }
    cout << "Game Over" << endl;
    return 0;
}
