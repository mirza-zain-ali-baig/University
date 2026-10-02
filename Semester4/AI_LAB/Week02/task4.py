marks = float(input("Enter student's marks (%): "))

if marks > 100 or marks < 0:
    print("Invalid marks")

elif marks >= 95:
    print("Grade: A+")

elif marks >= 85:
    print("Grade: A")

elif marks >= 80:
    print("Grade: B+")

elif marks >= 75:
    print("Grade: B")

elif marks >= 70:
    print("Grade: C+")

elif marks >= 65:
    print("Grade: C")

elif marks >= 60:
    print("Grade: D+")

elif marks >= 55:
    print("Grade: D")

elif marks >= 50:
    print("Grade: E+")

elif marks >= 45:
    print("Grade: E")

else:
    print("Grade: F")