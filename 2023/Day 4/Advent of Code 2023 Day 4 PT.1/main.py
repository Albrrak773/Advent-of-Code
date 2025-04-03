import os, pprint
with open("input.txt", "r") as file:
    lines = file.readlines()


def SplitList(lines: list):
    """
    Return: a list of lists each element represents a game \n
    each element is in the format: \n
    ['Game#', [num#, num#, num#], [num#, num#, num#]]
    """
    for i, line in enumerate(lines):
        lines[i] = line.split(':')
        tempElemet = lines[i][1]
        lines[i].pop()
        lines[i].append(tempElemet.split('|')[0].strip().split(" "))
        lines[i].append(tempElemet.split('|')[1].strip().split(" "))
    return lines

print("               \033[47m    Orignal List    \033[0m")
pprint.pprint(lines)
print("               \033[42m     New List     \033[0m")
cards = SplitList(lines)
# pprint.pprint(cards)
# ['Game#', [num#, num#, num#], [num#, num#, num#]]
card_total = 0
Game_total = 0
first_Time = True
for card in cards:
    for num in card[1]:
        if num in card[2]:
            if num is '':
                continue
            if first_Time:
                card_total = 1
                first_Time = False
                continue
            card_total = card_total*2
    print(f"The totla for {card[0]}: {card_total} ")
    Game_total += card_total
    first_Time = True
    card_total = 0
    
print(f"\033[34mGame total:{Game_total}\033[0m")