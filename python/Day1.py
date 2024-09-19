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
