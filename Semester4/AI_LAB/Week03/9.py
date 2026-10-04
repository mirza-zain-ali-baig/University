import array

# Using a standard Python list
my_list = [1, 2, 3, 4, 5]

# Method 1: Using the reverse() method (modifies in-place)
# my_list.reverse()
# print("Reversed list:", my_list)

# Method 2: Using slicing (creates a new reversed list)
original_list = [1, 2, 3, 4, 5]
reversed_list = original_list[::-1]
# here start should always less than stop

print(reversed_list[0])