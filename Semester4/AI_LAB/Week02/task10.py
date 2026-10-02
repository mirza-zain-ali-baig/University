start = int(input("Enter a number for start point: "))
stop = int(input("Enter a number for stop point: "))
step = int(input("Enter a number as a step in counting: "))
# outer loop to handle number of rows
# 10 in this case
for i in range(start, stop,step):

    # inner loop to handle number of columns
    # values changing acc. to outer loop
    for j in range(0, i):
    # printing stars
     print("* ",end="")
    print("\r")