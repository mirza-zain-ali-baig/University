import math

print("----- MENU -----")
print("1. Rectangle")
print("2. Circle")
print("3. Cylinder")

choice = int(input("Enter your choice: "))

if choice == 1:
    length = float(input("Enter length: "))
    width = float(input("Enter width: "))

    area = length * width
    perimeter = 2 * (length + width)

    print("Area =", area)
    print("Perimeter =", perimeter)

elif choice == 2:
    radius = float(input("Enter radius: "))

    area = math.pi * radius ** 2
    circumference = 2 * math.pi * radius

    print("Area =", area)
    print("Circumference =", circumference)

elif choice == 3:
    radius = float(input("Enter radius: "))
    height = float(input("Enter height: "))

    volume = math.pi * radius ** 2 * height
    surface_area = 2 * math.pi * radius * (radius + height)

    print("Volume =", volume)
    print("Surface Area =", surface_area)

else:
    print("Invalid choice")