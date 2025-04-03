def flatten(lst:list) -> list:
    flat_list = []
    # [[1, 2, 3], [3, 6]]
    for item in lst:
        if type(item) == list:
            for j in flatten(item):
                print(f"adding: {j}")
                flat_list.append(j)
        else:
            flat_list.append(item)
    
    return flat_list


mylist = [10, 11, [1, 2, 3, 4], [5, 6]]

newlist = flatten(mylist)
print(newlist)