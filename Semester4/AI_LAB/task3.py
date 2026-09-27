#Write a program to calculate sales tax on an item sold. Consider the following information: Price of one packet of jellies = 10 rs Price of one packet of juice = 50 rs Price of one bag of chips = 40 rs Price of one cup of ice-cream = 60 rs Price of one bar of chocolate = 35 rs Sales Tax = 5% of the item price 


print("1. Jellies - Rs. 10")
print("2. Juice - Rs. 50")
print("3. Chips - Rs. 40")
print("4. Ice-cream - Rs. 60")
print("5. Chocolate - Rs. 35")

choice = int(input("Enter your choice (1-5): "))

if choice == 1:
    price = 10
    item = "Jellies"
elif choice == 2:
    price = 50
    item = "Juice"
elif choice == 3:
    price = 40
    item = "Chips"
elif choice == 4:
    price = 60
    item = "Ice-cream"
elif choice == 5:
    price = 35
    item = "Chocolate"
else:
    print("Invalid choice")
    exit()

tax = price * 0.05
total = price + tax

print("Item:", item)
print("Price: Rs.", price)
print("Sales Tax (5%): Rs.", tax)
print("Total Price: Rs.", total)