sum = 0

while True:
    number = int(input("Enter the number that do you want to add: "))
    sum = sum+number
    
    choice = input("Do you want to add another number? (y/n):")
    if choice == "n" or choice == "N":
        break
    
print("Sum: ", sum)