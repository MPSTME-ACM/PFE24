#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

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

string animatedPrint(string message, int userInput = -1, double delayBetweenChars = 0.03, double delayBetweenLine = 1, bool newLine = true, bool bold = false) {
    if (bold == true)
        cout << "\033[1m";
    for (char c : message) {
        cout << c;
        cout.flush();
        if (c != '\n')
            this_thread::sleep_for(chrono::milliseconds(int(delayBetweenChars * 1000)));
        else
            this_thread::sleep_for(chrono::milliseconds(int(delayBetweenLine * 1000)));
    }
    cout << "\033[0m";
    if (newLine == true)
        cout << endl;
    if (userInput == -1)
        return "";
    if (userInput == 0) {
        string Input;
        cin >> Input;
        return Input;
	}
	while (true) {
		int intInput;
		cin >> intInput;
		if (std::cin.fail()) { // If the input is not an integer
			std::cin.clear(); // Clear the error flag
			std::cin.ignore(10000, '\n'); // Ignore invalid input
			std::cout << "Invalid input. Please enter a valid integer.\n";
		}
		else {
			std::cin.ignore(10000, '\n'); // Ignore any remaining input
			return to_string(intInput);
		}
	}
    return "";
}

int indexInList(string item, string itemList[], int size) {
    for (int i = 0; i < size; i++) {
        if (itemList[i] == item) 
            return i;
    }
    return -1;
}

string listToText(string itemList[], int size) {
    string combinedText = (size == 0) ? "" : "\n";
    for (int i = 0; i < size; i++) {
        combinedText += to_string(i) + ") " + itemList[i] + "\n";
    }
    return combinedText;
}

int checkMenuRange(string question, string listName[], int size, bool isCanceable = false) {
    int index = -1;
    index = stoi(animatedPrint(question + listToText(listName, size) + sLine + "\n", 1, 0.025, 0.04, false));
    bool validInput = false;
    while (!validInput) {
        if (isCanceable == true && index == -1)
            return -1;
        else if (index < 0 || index >= size) {
            animatedPrint("Invalid Choice! Please Try Again!");
            index = stoi(animatedPrint(question + listToText(listName, size) + sLine + "\n", 1, 0.025, 0.04, false));
        }
        else
            return index;
    }
    return index;
}

void starLine(int numRows, double timeWait, int newLineCount = 0) {
    for (int i = 0; i < numRows; i++) {
        cout << string(15, '=') << endl;
        this_thread::sleep_for(chrono::milliseconds(int(timeWait * 1000)));
    }
    for (int i = 0; i < newLineCount; i++)
        cout << endl;
}

void showHealthPotions() {
    if (healthPotionCount == 0) 
        animatedPrint("You have no health potions left!");
    else 
        animatedPrint("You have " + to_string(healthPotionCount) + "x Health Potions in your Inventory!");
}

int clampValue(int value, int minimum, int maximum = 100) {
    return max(minimum, min(maximum, value));    
}

void useHealthPotion() {
    showHealthPotions();
    if (healthPotionCount == 0) 
        return;
    pStats[4] = clampValue(pStats[4] + 5, 0, currentMaxStats[4]);
    if (pStats[4] == currentMaxStats[4]) \
        animatedPrint(pName + " Has Fully Recovered!");
    else 
        animatedPrint(pName + " has been Healed for 5 HP");
    animatedPrint(pName + " Now Has " + to_string(pStats[4]) + " HP!");
    healthPotionCount -= 1;
}

void playerAttack(int enemyStats[]) {
    string fightOptions[] = { "Fight", "Heal" };
    int fightChoice = checkMenuRange("Your Turn: ", fightOptions, 2);
    if (fightChoice == 0) {
        string attackOptions[] = { "Slash", "Stab", "Magic Bolt", "Special Attack", "Dodge", "Block" };
        int attackType = checkMenuRange("Choose Your Attack!", attackOptions, 6);
        double enemyDefPercent = 1 - enemyStats[1] / 12;
        int damage = 0;
        if (attackType == 0) {
            animatedPrint(pName + " Slashes with all their might!");
            damage = pStats[0] * enemyDefPercent;
        }
        else if (attackType == 1) {
            animatedPrint(pName + " Quickly Stabs the opponent!");
            damage = pStats[3] * enemyDefPercent;
        }
        else if (attackType == 2) {
            animatedPrint(pName + " Casts Magic on the opponent!");
            damage = pStats[2] * enemyDefPercent;
        }
        else if (attackType == 3) {
            animatedPrint(pName + " Uses Their Speciality on the opponent!");
            damage = pStats[5] * enemyDefPercent;
            if (pClass == 0) {
                int critChance = rand() % 100;
                if (critChance > 65) 
                    animatedPrint("Critical Hit!");
                damage = (pStats[0] * enemyDefPercent) * (critChance > 65 ? 1.5 : 1);
            }
        }
        else if (attackType == 4) 
            bDodgeAttempt = true;
        enemyStats[4] = clampValue(enemyStats[4] - damage, 0);
        animatedPrint(pName + " Dealt " + to_string(damage) + " Damage!");
        animatedPrint(enemyNames[enemyChoice] + " Currently Has " + to_string(enemyStats[4]) + "HP left!");
    }
    else if (fightChoice == 1) 
        useHealthPotion();
}

void decideEnemyAttack(string enemyName, int enemyMaxStats[]) {
    animatedPrint("Enemy Turn!");
    starLine(1, 1);
    int attackOptionChance = rand() % 100, damage = 0;
    double pDefPercent = 1 - pStats[1] / 20;
    if (attackOptionChance < 15) {
        animatedPrint(enemyName + " Uses Ultimate!");
        damage = enemyMaxStats[5] * pDefPercent;
    }
    else if (attackOptionChance < 80) {
        animatedPrint(enemyName + " Uses Slash!");
        damage = enemyMaxStats[0] * pDefPercent;
    }
    else {
        if (rand() % 100 < 30) {
            animatedPrint(enemyName + " Uses Heal!");
            enemyMaxStats[4] = clampValue(enemyMaxStats[4] + 3, 0, enemyMaxStats[4]);
            animatedPrint(enemyName + " Now Has " + to_string(enemyMaxStats[4]) + "HP!");
        }
        else 
            animatedPrint("Hah! You Think You Can Beat ME?");        
    }
    pStats[4] = clampValue(pStats[4] - damage, 0);
    animatedPrint(pName + " Took " + to_string(damage) + " Damage!");
    animatedPrint(pName + " Currently Has " + to_string(pStats[4]) + "HP!");
}

void showPStats() {
    starLine(1, 0);
    animatedPrint("Your Stats: ", -1, .025, .3);
    for (int i = 0; i < 6; i++) 
        animatedPrint(statNames[i] + " " + to_string(pStats[i]), -1, .025, .1);    
    starLine(1, 0);
}

void fightEnemy(int enemyNum) {
    enemyChoice = enemyNum;
    bool inFight = true;
    starLine(1, 0);
    animatedPrint("You Are Fighting Against " + enemyNames[enemyNum]);
    starLine(1, 1);
    int valueIndex = 0;
    int enemyMaxStats[numEnemies] = { 0, 0, 0, 0, 0, 0 };
    for (int i = 0; i < numStats; i++) {
		enemyStats[i] = enemyData[enemyNum][i];
		enemyMaxStats[i] = enemyData[enemyNum][i];
	}
    int chanceAdditional = (rand() % 100) - 50, currentTurn = -1;
    if (pStats[3] > enemyStats[3])  // pStats[3] is speed
        chanceAdditional += (rand() % 25) + 25;    
    int turnChance = 50 + chanceAdditional;
    if (rand() % 100 < turnChance)
        currentTurn = currentTurn * -1;    
    while (inFight == true && pStats[4] > 0) {
        if (currentTurn == 1) 
            playerAttack(enemyStats);        
        else {
            int dodgeChance = 25 + chanceAdditional;
            if (bDodgeAttempt == true) { 
                if (dodgeChance >= (rand() % 100))
                   animatedPrint(pName + " has narrowly avoided the attack!");                
                else {
                    animatedPrint("Dodge Failed!");
                    decideEnemyAttack(enemyNames[enemyNum], enemyMaxStats);
                    bDodgeAttempt = false;
                }
            }
			else 
				decideEnemyAttack(enemyNames[enemyNum], enemyMaxStats);
            starLine(1, 1);
        }
        currentTurn *= -1;
        if (pStats[4] == 0) {
            animatedPrint(pName + " has Died! RIP");
            inGameLoop = false; break;
        }
        if (enemyStats[4] == 0) {
            animatedPrint(pName + " has defeated " + enemyNames[enemyNum]);
            return;
        }
    }
}

void startFromCheckPoint() {
    if (checkPoint == 0) {
        string options[] = { "Rebel", "Sacrifice Civilians" };
        int choice = checkMenuRange("Choose Wisely:", options, 2);
        if (choice == 0) {
			animatedPrint(R"(As )" + pName + R"( listened to their reasons for rebellion, he began to see that the king was not as just and fair as he had thought. The rebels had suffered under the king's rule, with high taxes, unfair laws, and oppression. )" + pName + R"( realized that if the king was defeated, the rebels could create a new, fairer society in Valoria, and he decided to ally himself with them. Together, )" + pName + R"( and the rebels plotted their attack on the kingdom while it was distracted by the invaders. They waited for the opportune moment when the king's army was away, fighting the enemy. They marched into the castle.)");
            fightEnemy(0); checkPoint = 1;
        }
        else if (choice == 1) {
			animatedPrint(R"(After fighting for a while, )" + pName + R"( observed that the enemy had far more soldiers and resources than Valoria. In a desperate move, )" + pName + R"( decided to sacrifice the innocent lives of the people in the village in order to draw the enemy's attention away from the city and onto the villagers. It was a terrible decision, and )" + pName + R"( knew it. But he also knew that if he did not act quickly, the kingdom would be lost. The enemy army attacked the village, and a fierce battle ensued. Many innocent lives were lost, but in the end, )" + pName + R"('s plan worked. The enemy was distracted, and )" + pName + R"( was able to lead a surprise attack that caught them off guard.)");
            fightEnemy(1); checkPoint = -1;
        }
    }
    else if (checkPoint == 1) {
        animatedPrint(R"(While fighting against the soldiers, )" + pName + R"( was in deep pain as he had to kill the people he fought side by side against. He then realised that he will not have to do that if he defeats the king whom they are protecting. So )" + pName + R"( spots the king and sprints towards him while shoving the other soldiers trying to block him to the side. As he is moving towards the king, the kingdom General blocks his way and he could only pass if he defeats the general.)");
        fightEnemy(5); checkPoint = 2;
    }
    else if (checkPoint == 2) {
		animatedPrint(R"(After defeating the General, )" + pName + R"( runs towards the king and knocks him unconscious. The king was finally captured and brought to justice by the rebellion led by )" + pName + R"(. The people of Valoria were shocked and confused by what had happened. They had always trusted their king, and now they were unsure of what to believe. The rebels declared that they had taken over the kingdom to create a better society for all, with equal rights and justice for everyone. At first, there was some resistance from the people who remained loyal to the king.)");
        fightEnemy(4); checkPoint = 3;
        if (pStats[4] <= 0) 
            return;
        animatedPrint(R"(After being defeated, the unsatisfied soldiers over time saw that the rebels were sincere in their intentions. The rebels worked hard to establish a new government that was fair and just, with laws that protected the people's rights and freedoms.)");
        starLine(1, 1);
        animatedPrint("The kingdom of Valoria had been saved, not by force of arms, but by the courage and determination of its people, who had stood up for what they believed in and created a better society for all.");
        inGameLoop = false;
    }
    else if (checkPoint == -1) {
		animatedPrint(R"(After fighting for a while, )" + pName + R"( observed that the enemy had far more soldiers and resources than Valoria. In a desperate move, )" + pName + R"( decided to sacrifice the innocent lives of the people in the village in order to draw the enemy's attention away from the city and onto the villagers. It was a terrible decision, and )" + pName + R"( knew it. But he also knew that if he did not act quickly, the kingdom would be lost. The enemy army attacked the village, and a fierce battle ensued. Many innocent lives were lost, but in the end, )" + pName + R"('s plan worked. The enemy was distracted, and )" + pName + R"( was able to lead a surprise attack that caught them off guard.)");
        fightEnemy(1); checkPoint = -2;
    }
    else if (checkPoint == -2) {
        animatedPrint("While fighting the enemy soldiers, " + pName + " located the enemy General and sprinted towards him. The General also noticed " + pName + " and both were ready to fight each other.");
        fightEnemy(5);
        if (pStats[4] <= 0) 
            return;
		animatedPrint(R"(The enemy General was defeated. The enemy troops which noticed this started surrendering, following which the remaining enemy army surrendered. The battle was long and grueling, but )" + pName + R"( and his army emerged victorious. The enemy army was defeated, and the kingdom of Valoria was saved. However, the victory came at a great cost. Many lives had been lost, and )" + pName + R"( knew that he would be haunted by the memory of the innocent lives he had sacrificed for the rest of his life. When the king returned to the city and saw the devastation, he was horrified. He could not believe that )" + pName + R"( had made the decision to sacrifice innocent lives, even if it was for the greater good of the kingdom. The king banished )" + pName + R"( from the kingdom, declaring him a traitor and a murderer. )" + pName + R"( left Valoria, his heart heavy with grief and regret. He knew that he had done what he thought was necessary to save the kingdom, but he could not shake the feeling that he had betrayed his own conscience. He wandered the land, seeking redemption and forgiveness for his actions.)");
        starLine(1, 0.5);
        animatedPrint("Years passed, and " + pName + " grew old and tired. He had never been able to forgive himself for what he had done, and he knew that he would never be able to return to Valoria. \nHowever, as he lay on his deathbed, he received a message from the king of Valoria. The message read: \"My dear " + pName + ", I am an old man now, and I have seen many things in my life. \nI have come to realize that sometimes, in order to save the ones we love, we must make difficult choices. \nYou did what you thought was right, and for that, I forgive you. I ask that you return to Valoria, to be honored as the hero that you are.\"\n " + pName + " wept tears of joy and relief. He knew that he would never be able to erase the memory of the lives he had sacrificed, but he also knew that he had been forgiven.\n He returned to Valoria, and was greeted as a hero. The people of Valoria honored him with a statue in the city square. After " + pName + "'s death, a memorial was made as the same city square to honor him.");
        inGameLoop = false;
    }
}

int main() {
    std::srand(std::time(0)); // Use current time as seed for random generator
    pName = animatedPrint("What Is Your Name?", 0, 0.1);
    starLine(2, 1);
    animatedPrint("Once upon a time in the kingdom of Valoria, a great darkness began to spread across the land. The king called upon his bravest and most skilled warriors, mages, thieves, and archers to come forth and help save the kingdom. You, as the chosen hero, must decide which class they will take to battle the dark forces that threaten their home.");
    starLine(1, 3);
    for (int i = 0; i < numClasses; i++) {
        animatedPrint(classTypes[i], -1, 0.03, 1, true, true);
        for (int j = 0; j < numStats; j++)
            animatedPrint(statNames[j] + " - " + to_string(classStats[i][j]), -1, .00, .00);
        starLine(1, 1.5);
    }
    pClass = checkMenuRange("Choose Your Class!", classTypes, numClasses);
    animatedPrint("You Have Chosen " + classTypes[pClass] + "!");
    for (int i = 0; i < numStats; i++) {
        pStats[i] = classStats[pClass][i];
        currentMaxStats[i] = classStats[pClass][i];
    }
    starLine(2, 2);
    animatedPrint("Henceforth You Shall Be Known As " + pName + " The " + classTypes[pClass]);
    starLine(1, 3);
    animatedPrint("As soon as " + pName + " received the summons from the king, " + pName + " set out with the army to confront the invaders. But along the way, he encountered a group of rebels who had been fighting against the king's rule for years.");
    starLine(1, 5);
    animatedPrint("The rebels see you as a potential ally and offer you to join forces with them to overthrow the king and take over the kingdom.\nAs " + pName + " pondered his options, he received another message from the king.\nIt read that the situation at the front was not optimistic for their kingdom. This time, the king urged " + pName + " to do whatever it takes to save the kingdom.\n " + pName + "  was shocked by the king's message, and he realized that he was faced with an impossible choice. \nHe could either betray his king and ally with the rebels to seize power, or he could follow the king's orders and commit unspeakable acts to win the war.\nBut then, " + pName + "  met a beautiful maiden named Isabella among the rebels, who stole his heart at first sight. Isabella was a kind and gentle soul who reminded " + pName + " of the values he had fought for all his life: honor, justice, and compassion.\n\nWith Isabella's guidance, " + pName + " realized that he had a choice. He could fight to defend the kingdom with either sacrificing innocent lives or betraying his king. He could use his skills and his army to protect his people and lead them to victory with honor and integrity.\n\nIt is upto you " + pName + " as to which path you choose..\n ");
    animatedPrint("NOTE: ", -1, 0.03, 1, true, true);
    animatedPrint("Each path has its own challenges and outcomes.\n");
    inGameLoop = true;
    while (inGameLoop && pStats[4] > 0) {
        starLine(1, 0);
        string menuRange[] = { "Main Story", "View Stats", "Inventory" };
        int actChoice = checkMenuRange("What do you want to do?", menuRange, 3);
        if (actChoice == 0)
            startFromCheckPoint();
        if (actChoice == 1)
            showPStats();
        else if (actChoice == 2)
            showHealthPotions();
    }
}
