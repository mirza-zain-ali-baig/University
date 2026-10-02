books = int(input("Enter the number of books purchased: "))

if books == 0:
    points = 0
elif books == 1:
    points = 5
elif books == 2:
    points = 15
elif books == 3:
    points = 30
elif books >= 4:
    points = 60
else:
    print("Invalid number of books")
    exit()

print("Points awarded:", points)