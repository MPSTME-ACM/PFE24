import time, math, random, sys

statNames = ["Attack", "Defense", "Mana", "Speed", "Health", "SPower"] # All Stat Names
classTypes = ["Knight", "Mage", "Archer", "Thief"] # All Class Types
classStats = [[5, 8, 1, 3, 10, 3], [2, 3, 15, 3, 4, 8], [6, 3, 2, 6, 5, 10], [4, 4, 3, 10, 5, 6]] # Each List Defines The Stats For Each Class In The Same Order As Above
maxedOutStats = [15, 15, 15, 15, 20, 15] 
currentMaxStats = []
# Defining Base Variables And Values
pName = "Koneko"
pStats, statAdjustment = [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]
pClass, pLevel, pExp = -1, 0, 0
activityMenu = ["Main Story", "View Stats", "Inventory"]
enemyData = [["Soldier-1", "Soldier-2", "Soldier-3", "Soldier-4", "Soldier-5", "General"], [2, 3, 4, 5, 6, 8],[2, 3, 4, 5, 6, 8], [1, 2, 3, 4, 5, 8], [1, 2, 3, 4, 5, 8], [2, 3, 4, 5, 6, 8], [2, 3, 4, 5, 6, 8]]
healthPotionCount = 3
sLine = ""
bDodgeAttempt = False
def animatedPrint(message="", userInput=-1, delayBetweenChars=0.03, delayBetweenLine=1, newLine=True, bold=False):
    if bold == True: print('\033[1m', end="")
    for char in message:
        print(char, end="")
        sys.stdout.flush()
        if char != "\n": time.sleep(delayBetweenChars)
        else: time.sleep(delayBetweenLine)
    print('\033[0m', end="")
    if newLine == True: print() # Input String!
    if userInput == 0: return input()
    while userInput == 1:
        try:
            intInput = int(input())
            return intInput
        except (TypeError, ValueError) as e:
            animatedPrint("Please Enter an Integer!")
            starLine(1,1)

# Returns Index Of Item In Given List, If Doesn't Exist, Returns -1!
def indexInList(item, itemList : list):
    if item not in itemList:  return -1
    return itemList.index(item)

# Converts List Into Menu Text
def listToText(itemList : list):
    combinedText = "\n"
    for i in range(len(itemList)):
        combinedText = combinedText + str(i) + ") " + itemList[i] + "\n"
    if len(itemList) == 0:
        combinedText = ""
    return combinedText

# Checks If The Number Inputted By The User Is Correct!
def checkMenuRange(question : str = "", listName : list = [], isCanceable : bool = False):
    index = -1
    index = animatedPrint(question + listToText(listName) + sLine + "\n", 1, 0.025, 0.04, False)
    validInput = False
    while validInput == False:
        if isCanceable == True and index == -1:
            return -1
        elif index < 0 or index >= len(listName):
            animatedPrint("Invalid Choice! Please Try Again!")
            starLine(1, 1)
            index = animatedPrint(question + listToText(listName) + sLine + "\n", 1, 0.025, 0.04, False)
        else:
            return index

# Adds * 15 Times With A Certain Delay To It and it can also be used to add New Lines!
def starLine(numRows, timeWait, newLineCount=0):
    global sLine; sLine = "=" * 15
    for i in range(numRows):
        print(sLine)
        time.sleep(timeWait)
    for i in range(newLineCount):
        print()
    return

# Function Shows Current Inventory Of Player
def showHealthPotions() -> None:
    animatedPrint("You have no health potions left!") if healthPotionCount == 0 else animatedPrint("You have {}x Health Potions in your Inventory!".format(healthPotionCount))

# Open Menu For Using Item
def useHealthPotion() -> None:
    global pStats, healthPotionCount
    showHealthPotions()
    if healthPotionCount == 0: return
    pStats[4] = clampValue(pStats[4] + 5, 0, currentMaxStats[4])
    animatedPrint(f"{pName} Has Fully Recovered!") if pStats[4] == currentMaxStats[4] else animatedPrint(f"{pName} has been Healed for 5 HP")
    animatedPrint(f"{pName} Now Has {pStats[4]} HP!")
    healthPotionCount -= 1

# Function helps In Clamping Values In A Given Range
def clampValue(value, minimum, maximum=100):
    value = minimum if value < minimum else value
    value = maximum if value > maximum else value
    return value

def playerAttack(enemyStats):
    global pStats
    fightChoice = checkMenuRange("Your Turn: ", ["Fight", "Heal"])
    # Selected Fight!
    if fightChoice == 0:
        attackType = checkMenuRange("Choose Your Attack!", ["Slash", "Stab", "Magic Bolt", "Special Attack", "Dodge", "Block"])
        enemyDefPercent = 1 - enemyStats[1] / 12
        damage = 0
        if attackType == 0:
            animatedPrint(str(pName) + " Slashes with all their might!")
            damage = pStats[0] * enemyDefPercent
        elif attackType == 1:
            animatedPrint(str(pName) + " Quickly Stabs the opponent!")
            damage = pStats[3] * enemyDefPercent
        elif attackType == 2:
            animatedPrint(str(pName) + " Casts Magic on the opponent!")
            damage = pStats[2] * enemyDefPercent
        elif attackType == 3:
            animatedPrint(str(pName) + " Uses Their Speciality on the opponent!")
            damage = pStats[5] * enemyDefPercent
            if pClass == 0:
                critChance = random.randint(0, 100)
                if critChance > 69:
                    animatedPrint("Critical Hit!")
                damage = (pStats[0] * enemyDefPercent) * (1.5 if critChance > 69 else 1)
        elif attackType == 4: global bDodgeAttempt; bDodgeAttempt = True
        enemyStats[4] = clampValue(enemyStats[4] - math.floor(damage), 0)
        animatedPrint(pName + " Dealt " + str(math.floor(damage)) + " Damage!")
        animatedPrint(enemyData[0][enemyChoice] + " Currently Has " + str(enemyStats[4]) + "HP left!")
    elif fightChoice == 1: useHealthPotion()

def decideEnemyAttack(enemyName, enemyMaxStats=[]):
    animatedPrint("Enemy Turn!")
    starLine(1, 1)
    attackOptionChance, damage, pDefPercent = random.randint(0, 100), 0, 1 - pStats[1] / 20
    if attackOptionChance < 15: #<15
        animatedPrint(str(enemyName) + " Uses Ultimate!") # No Element Type Enemy Special!
        damage = enemyStats[5] * pDefPercent
    elif attackOptionChance < 80: # Enemy Normal Attack!
        animatedPrint(str(enemyName) + " Uses Slash!")
        damage = enemyStats[0] * pDefPercent
    else: # Enemy Taunt Or Heal!
        if random.randint(0, 100) < 30:
            animatedPrint(str(enemyName) + " Uses Heal!")
            enemyStats[4]  = clampValue(enemyStats[4] + 3, 0, enemyMaxStats[4])
            animatedPrint(enemyName + " Now Has " + str(enemyStats[4]) + "HP")
        else: animatedPrint("Hah! You Think You Can Beat ME?")
    pStats[4] = clampValue(pStats[4] - math.ceil(damage), 0)
    animatedPrint(pName + " Took " + str(math.ceil(damage)) + " Damage!")
    animatedPrint(pName + " Currently Has " + str(pStats[4]) + "HP!")

def showPStats():
    starLine(1, 0)
    animatedPrint("Your Stats: ", -1, .025, .3)
    for i in range(len(statNames)):
        animatedPrint(str(statNames[i]) + " " + str(pStats[i]), -1, .025, .1)
    starLine(1, 0)

# Start Of Game
pName = animatedPrint("What Is Your Name?", 0, delayBetweenChars=0.1)
starLine(2, 1, )
animatedPrint("Once upon a time in the kingdom of Valoria, a great darkness began to spread across the land. The king called upon his bravest and most skilled warriors, mages, thieves, and archers to come forth and help save the kingdom. You, as the chosen hero, must decide which class they will take to battle the dark forces that threaten their home.")
starLine(1, 3, ) 
for i in range(len(classTypes)):
    animatedPrint(str(classTypes[i]), bold=True)
    for j in range(len(classStats[i])):
        animatedPrint(statNames[j] + " - " + str(classStats[i][j]), -1, .00, .00)
    starLine(1, 1.5)

pClass = checkMenuRange("Choose Your Class!", classTypes)
animatedPrint("You Have Chosen " + classTypes[pClass] + "!")
pStats = classStats[pClass]
currentMaxStats = list(classStats[pClass])
starLine(2, 2)
animatedPrint(f"Henceforth You Shall Be Known As {pName} The " + classTypes[pClass])
starLine(1, 3)
animatedPrint(f"As soon as {pName} received the summons from the king, {pName} set out with the army to confront the invaders. But along the way, he encountered a group of rebels who had been fighting against the king's rule for years.")
starLine(1, 5)
animatedPrint(f"The rebels see you as a potential ally and offer you to join forces with them to overthrow the king and take over the kingdom.\nAs {pName} pondered his options, he received another message from the king.\nIt read that the situation at the front was not optimistic for their kingdom. This time, the king urged {pName} to do whatever it takes to save the kingdom.\n{pName} was shocked by the king's message, and he realized that he was faced with an impossible choice. \nHe could either betray his king and ally with the rebels to seize power, or he could follow the king's orders and commit unspeakable acts to win the war.\nBut then, {pName} met a beautiful maiden named Isabella among the rebels, who stole his heart at first sight. Isabella was a kind and gentle soul who reminded {pName} of the values he had fought for all his life: honor, justice, and compassion.\n\nWith Isabella's guidance, {pName} realized that he had a choice. He could fight to defend the kingdom with either sacrificing innocent lives or betraying his king. He could use his skills and his army to protect his people and lead them to victory with honor and integrity.\n\nIt is upto you {pName} as to which path you choose..\n ")
animatedPrint("NOTE: ", newLine=False, bold=True)
animatedPrint("Each path has its own challenges and outcomes.\n")

enemyStats = [0] * 6
def fightEnemy(enemyNum=0):
    global enemyChoice, enemyStats, bDodgeAttempt
    enemyChoice = enemyNum
    inFight = True
    starLine(1, 0)
    animatedPrint("You Are Fighting Against " + str(enemyData[0][enemyChoice]))
    starLine(1, 1)
    valueIndex = 0
    enemyStats = [0] * 6
    for i in enemyData[enemyChoice + 1]:
        enemyStats[valueIndex] = int(i)
        valueIndex += 1
    enemyMaxStats = list(enemyStats)
    chanceAdditional = 0
    currentTurn = -1
    if pStats[3] > enemyStats[3]:
        chanceAdditional = random.randint(25, 50)
    turnChance = 50 + chanceAdditional
    if random.randint(0, 100) < turnChance:
        currentTurn = currentTurn * -1
    while inFight == True and pStats[4] > 0:
        # Player Turn!
        if currentTurn == 1:
            playerAttack(enemyStats)

        # Enemy Turn!
        else:
            increaseChance = 0
            if pStats[3] > enemyStats[3]:
                increaseChance = random.randint(25, 50)
            dodgeChance = 25 + increaseChance
            failChance = random.randint(0, 100)
            if bDodgeAttempt == True:
                if failChance < dodgeChance:
                    animatedPrint(str(pName) + " has narrowly avoided the attack!")
                else:
                    animatedPrint("Dodge Failed!")
                    decideEnemyAttack(enemyData[0][enemyChoice], enemyMaxStats)
                    bDodgeAttempt = False
            else:
                decideEnemyAttack(enemyData[0][enemyChoice], enemyMaxStats)
            starLine(1, 1)

        currentTurn *= -1
        if pStats[4] == 0:
            animatedPrint(str(pName) + " has Died! RIP")
            endGame()
            break
        if enemyStats[4] == 0:
            animatedPrint(str(pName) + " has defeated " + str(enemyData[0][enemyChoice]))
            break

def endGame():
    global inGameLoop
    inGameLoop = False
    return

def changeCheckPoint(currentCheckpoint=0):
    global checkPoint
    checkPoint = currentCheckpoint
    return

def startFromCheckPoint(checkPoint):
    if checkPoint == 0:
        choice = checkMenuRange("Choose Wisely:", ["Rebel", "Sacrifice Civillians"])
        if choice == 0: # Choosing Rebel
            animatedPrint(f"As {pName} listened to their reasons for rebellion, he began to see that the king was not as just and fair as he had thought.")
            animatedPrint(f"The rebels had suffered under the king's rule, with high taxes, unfair laws, and oppression. {pName} realized that if the king was defeated, the rebels could create a new, fairer society in Valoria, and he decided to ally himself with them. \nTogether, {pName} and the rebels plotted their attack on the kingdom while it was distracted by the invaders. They waited for the opportune moment when the king's army was away, fighting the enemy. \nThey marched into the castle.")
            fightEnemy(0)
            changeCheckPoint(1)
        elif choice == 1: # Choosing Sacrifice
            animatedPrint(f"{pName} decided not to ally himself with the rebels out of his duty and loyalty for the king and his kingdom. {pName} quickly escaped from there to hurry towards the invaders. As he reached the invaders, he protected some of the civillians who were being attacked.")
            fightEnemy(0)
            changeCheckPoint(-1)
    elif checkPoint == 1:
        animatedPrint(f"While fighting against the soldiers, {pName} was in deep pain to as he had to kill the people he fought side by side against. \nHe then realised that he will not have to do that if he defeats the king whom they are protecting. So {pName} spots the king and sprints towards him while shoving the other soldiers trying to block him to the side. \nAs he is moving towards the king, the kingdom General blocks his way and he could only pass if he defeats the general.")
        fightEnemy(5)
        changeCheckPoint(2)
    elif checkPoint == 2:
        animatedPrint(f"After defeating the General, {pName} runs towards the king and knocks him unconscious. The king was finally captured and brought to justice by rebellion led by {pName}. {pName}, with his strategic wits thwarted the invasion along with the rebels. The people of Valoria were shocked and confused by what had happened. They had always trusted their king, and now they were unsure of what to believe. \nThe rebels declared that they had taken over the kingdom to create a better society for all, with equal rights and justice for everyone. At first, there was some resistance from the people who remained loyal to the king.")
        fightEnemy(4)
        changeCheckPoint(3)
        if pStats[4] <= 0: return
        animatedPrint("After being defeated, the unsatisfied soldiers over time saw that the rebels were sincere in their intentions. The rebels worked hard to establish a new government that was fair and just, with laws that protected the people's rights and freedoms.")
        starLine(1, 1)
        animatedPrint(f"{pName} was hailed as a hero by the rebels, who made him the new leader of Valoria. He worked hard to unite the people and build a better future for them all. \nThe kingdom of Valoria had been saved, not by force of arms, but by the courage and determination of its people, who had stood up for what they believed in and created a better society for all.")
        endGame()
    elif checkPoint == -1:
        animatedPrint(f"After fighting for a while, {pName} observed that the enemy had far more soldiers and resources than Valoria.\n In a desperate move, {pName} decided to sacrifice the innocent lives of the people in the village in order to draw the enemy's attention away from the city and onto the villagers. It was a terrible decision, and {pName} knew it. \nBut he also knew that if he did not act quickly, the kingdom would be lost. The enemy army attacked the village, and a fierce battle ensued. \nMany innocent lives were lost, but in the end, {pName}'s plan worked. The enemy was distracted, and {pName} was able to lead a surprise attack that caught them off guard.")
        fightEnemy(1)
        changeCheckPoint(-2)
    elif checkPoint == -2:
        animatedPrint(f"While fighting the enemy soldiers, {pName} located the enemy General and sprinted towards him. The General also noticed {pName} and both were ready to fight each other.")
        fightEnemy(5)
        if pStats[4] <= 0: return
        animatedPrint("The enemy General was defeated. The enemy troops which noticed this started surrendering following which the remaining enemy army surrendered.")
        animatedPrint(f"The battle was long and grueling, but {pName} and his army emerged victorious. The enemy army was defeated, and the kingdom of Valoria was saved. However, the victory came at a great cost. \nMany lives had been lost, and {pName} knew that he would be haunted by the memory of the innocent lives he had sacrificed for the rest of his life. \nWhen the king returned to the city and saw the devastation, he was horrified. He could not believe that {pName} had made the decision to sacrifice innocent lives, even if it was for the greater good of the kingdom.\n The king banished {pName} from the kingdom, declaring him a traitor and a murderer. {pName} left Valoria, his heart heavy with grief and regret. \nHe knew that he had done what he thought was necessary to save the kingdom, but he could not shake the feeling that he had betrayed his own conscience. \nHe wandered the land, seeking redemption and forgiveness for his actions.")
        starLine(1, 0.5)
        animatedPrint(f"Years passed, and {pName} grew old and tired. He had never been able to forgive himself for what he had done, and he knew that he would never be able to return to Valoria. \nHowever, as he lay on his deathbed, he received a message from the king of Valoria. The message read: \"My dear {pName}, I am an old man now, and I have seen many things in my life. \nI have come to realize that sometimes, in order to save the ones we love, we must make difficult choices. \nYou did what you thought was right, and for that, I forgive you. I ask that you return to Valoria, to be honored as the hero that you are.\"\n {pName} wept tears of joy and relief. He knew that he would never be able to erase the memory of the lives he had sacrificed, but he also knew that he had been forgiven.\n He returned to Valoria, and was greeted as a hero. The people of Valoria honored him with a statue in the city square. After {pName}'s death, a memorial was made as the same city square to honor him.")
        endGame()
        
checkPoint = 0
inGameLoop = True
while (inGameLoop == True and pStats[4] > 0): # Main Game Loop
    starLine(1, 0) # Activity Menu Being (["Main Story", "View Stats", "Inventory"])
    actChoice = checkMenuRange("What do you want to do?", activityMenu)
    if actChoice == 0:
        startFromCheckPoint(checkPoint)
    if actChoice == 1:
        showPStats()
    elif actChoice == 2:
        showHealthPotions()
