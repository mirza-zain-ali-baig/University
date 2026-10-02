#Write a program that separately prints even numbers and odd numbers from a range specified by the user


start = int(input("Enter the starting number: "))
stop = int(input("Enter the stopping number: "))

if start <0 or start <= stop:
    print("Error in Input")
even = []
odd = []
for i in range(start,stop+1):
    if i%2==0:
        even.append(i)
    else:
        odd.append(i)

print("Even Numbers: ", even)
print("Odd Numbers: ", odd)