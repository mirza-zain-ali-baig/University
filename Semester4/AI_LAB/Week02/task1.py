#Write a program to find the volume of cylinder (the cylinder's volume is π r² h) 

radius = float(input("Enter the radius of cylinder: "))
height = float(input("Enter the height of cylinder: "))

area_of_cylindder = (22/7)* radius**2 * height

print("Area of Cylinder is: ", area_of_cylindder)