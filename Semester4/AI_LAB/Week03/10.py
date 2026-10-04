# We can use a standard Python list as an array
my_array = [10, 20, 30, 40, 50]

# # Display the entire array
# print("Array items:", my_array)

# # Access individual elements through indexes
# print("Element at index 0:", my_array[0])
# print("Element at index 2:", my_array[2])
# print("Element at index 4:", my_array[4])

# Alternatively, using the 'array' module (if strictly required by your course):
import array
int_array = array.array('i', my_array)

# When you create an array, you must tell Python what type of data it will hold. You do this using a typecode (a single letter in quotes).

# Here are the most common typecodes:

# 'i' = Signed Integer (Whole numbers like 10, -5, 100)

# 'f' = Float (Decimals like 3.14, 2.5)

# 'u' = Unicode Character (A single letter like 'a', 'b')

# 'd' = Double precision float (More precise decimals)

print(int_array)
print(int_array[0])
print(int_array[1:3])