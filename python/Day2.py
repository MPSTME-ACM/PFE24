import math

statNames = ["Attack", "Defense", "Mana", "Speed", "Health", "SPower"]  # All Stat Names
classTypes = ["Knight", "Mage", "Archer", "Thief"]  # All Class Types
classStats = [[5, 8, 1, 3, 10, 3], [2, 3, 15, 3, 4, 8], [6, 3, 2, 6, 5, 10], [4, 4, 3, 10, 5, 6]]  # Each List Defines The Stats For Each Class In The Same Order As Above
maxedOutStats = [15, 15, 15, 15, 20, 15] 
currentMaxStats = []

# Defining Base Variables And Values
pName = "Koneko"
pStats, statAdjustment = [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]
pClass, pLevel, pExp = -1, 0, 0
activityMenu = ["Main Story", "View Stats", "Inventory"]
enemyData = [["Soldier-1", "Soldier-2", "Soldier-3", "Soldier-4", "Soldier-5", "General"], [2, 3, 4, 5, 6, 8], [2, 3, 4, 5, 6, 8], [1, 2, 3, 4, 5, 8], [1, 2, 3, 4, 5, 8], [2, 3, 4, 5, 6, 8], [2, 3, 4, 5, 6, 8]]
healthPotionCount = 3
sLine = ""
bDodgeAttempt = False
currentTurn = 1  # Initialize currentTurn

# Start Of Game
pName = input("What Is Your Name? ")
sLine = "=" * 15
print(sLine)
print(sLine)

print("Story a.1")

for i in range(len(classTypes)):
    print(f"\033[1m{classTypes[i]}\033[0m")
    for j in range(len(classStats[i])):
        print(statNames[j] + " - " + str(classStats[i][j]))
    print(sLine)

print("Choose Your Class!")
for i in range(len(classTypes)):
    print(f"{i}) {classTypes[i]}")

pClass = int(input("Enter the class number: "))
print("You Have Chosen " + classTypes[pClass] + "!")
pStats = classStats[pClass]
currentMaxStats = list(classStats[pClass])
print(sLine)
print(sLine)
print(f"Henceforth You Shall Be Known As {pName} The {classTypes[pClass]}")
print(sLine)



enemyStats = [0] * 6
enemyChoice = 0
inFight = True
print(sLine)
print("You Are Fighting Against " + str(enemyData[0][enemyChoice]))
print(sLine)

valueIndex = 0
enemyStats = [0] * 6
for i in enemyData[enemyChoice + 1]:
    enemyStats[valueIndex] = int(i)
    valueIndex += 1

enemyMaxStats = list(enemyStats)
chanceAdditional = 25  # Fixed value for additional chance

turnChance = 50 + chanceAdditional
fixed_chance = 50  # Fixed value for turnChance comparison
if fixed_chance < turnChance:
    currentTurn = -1

while inFight and pStats[4] > 0:
    # Player Turn!
    if currentTurn == 1:
        print("Your Turn: ")
        print("0) Fight\n1) Heal")
        fightChoice = int(input())
        
        if fightChoice == 0:
            print("Choose Your Attack!")
            print("0) Slash\n1) Stab\n2) Magic Bolt\n3) Special Attack\n4) Dodge\n5) Block")
            attackType = int(input())
            enemyDefPercent = 1 - enemyStats[1] / 12
            damage = 0
            if attackType == 0:
                print(str(pName) + " Slashes with all their might!")
                damage = pStats[0] * enemyDefPercent
            elif attackType == 1:
                print(str(pName) + " Quickly Stabs the opponent!")
                damage = pStats[3] * enemyDefPercent
            elif attackType == 2:
                print(str(pName) + " Casts Magic on the opponent!")
                damage = pStats[2] * enemyDefPercent
            elif attackType == 3:
                print(str(pName) + " Uses Their Speciality on the opponent!")
                damage = pStats[5] * enemyDefPercent
                critChance = 70  # Fixed value for critical hit
                if critChance > 69:
                    print("Critical Hit!")
                damage = (pStats[5] * enemyDefPercent) * (1.5 if critChance > 69 else 1)
            elif attackType == 4:
                bDodgeAttempt = True
            enemyStats[4] = max(min(enemyStats[4] - math.floor(damage), 100), 0)
            print(pName + " Dealt " + str(math.floor(damage)) + " Damage!")
            print(enemyData[0][enemyChoice] + " Currently Has " + str(enemyStats[4]) + "HP left!")
            if (enemyStats[4] == 0):
                inFight = False
                print(enemyData[0][enemyChoice] + " Has Been Killed!")
                break
        elif fightChoice == 1:
            if healthPotionCount > 0:
                pStats[4] = max(min(pStats[4] + 5, currentMaxStats[4]), 0)
                if pStats[4] == currentMaxStats[4]:
                    print(f"{pName} Has Fully Recovered!")
                else:
                    print(f"{pName} has been Healed for 5 HP")
                print(f"{pName} Now Has {pStats[4]} HP!")
                healthPotionCount -= 1
            else:
                print("You have no health potions left!")
        currentTurn = 0
    
    # Enemy Turn!
    else:
        print("Enemy Turn!")
        print(sLine)
        attackOptionChance, damage, pDefPercent = 50, 0, 1 - pStats[1] / 20  # Fixed value for attackOptionChance
        if attackOptionChance < 15:  # Ultimate Attack
            print(str(enemyData[0][enemyChoice]) + " Uses Ultimate!")
            damage = enemyStats[5] * pDefPercent
        elif attackOptionChance < 80:  # Normal Attack
            print(str(enemyData[0][enemyChoice]) + " Uses Slash!")
            damage = enemyStats[0] * pDefPercent
        else:
            print(str(enemyData[0][enemyChoice]) + " Misses!")
        pStats[4] = max(pStats[4] - math.floor(damage), 0)
        print(f"{pName} Now Has {pStats[4]} HP!")
        if pStats[4] == 0:
            print(f"{pName} has been defeated!")
            inFight = False
        currentTurn = 1

print("Game Over")
