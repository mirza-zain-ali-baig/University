numbers = [40,75,30,78]

# max_number = max(numbers)

# print("Maximum Number: " , max_number)

#second way
max =numbers[0]
for num in numbers:
    if num > max:
        max = num
        
print(max)