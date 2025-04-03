from pprint import pp
import sys
import json
def main():

    with open("input.txt", "r") as file:
        lines = file.readlines()

    cards = SplitList(lines)

    cards_reference = get_refernce(cards)

    scratch_cards = []
    Stack = []
    scratch_cards.append(cards[0][0])

    for card in cards[1::]:
        Stack.append(card[0])
    Stack = Stack[::-1]

    while Stack:
        next_value = cards_reference[scratch_cards[-1]]

        if next_value:
            for value in next_value[::-1]:
                Stack.append(value)
            scratch_cards.append(Stack[-1])
            Stack.pop()
        else:
            scratch_cards.append(Stack[-1])
            Stack.pop()

    with open("output.txt", 'w') as file:
        file.write(str(len(scratch_cards)))

    print(f"\033[34mTotal Number of Scratch cards: {len(scratch_cards)}\033[0m")



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

def get_refernce(cards:list) -> dict:
    """
    the returned dict contains the resulting copys for each orignal Card. used as a reference
    where the key is the card Number and value is a list of copys
    {"card 1": ["card 2", "card 3", "card 4", "card 5"], "card 2": ["card 3", "card 4"], ...} 
    """
    cards_reference = {}
    for i, card in enumerate(cards):
        i += 1

        matches_count = 0
        matches_list = [] # holds the a list of lists for each subsequent match so if 1 has 2 matches this list hold the value of these matches
        winning_numbers = card[1]
        numbers_have = card[2]

        for winning_number in winning_numbers:
            if winning_number in numbers_have:
                if winning_number == '':
                    continue
                matches_count += 1
        for j in range(matches_count):
            matches_list.append(cards[i + j][0])
        cards_reference[card[0]] = matches_list

    return cards_reference

if __name__ == '__main__':
    main()