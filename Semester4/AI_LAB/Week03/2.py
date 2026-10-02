student = {
    "name": "Mirza Zain Ali Baig",
    "age": "twenty one",
    "course": "Software Engineering"
}

key = "age"

if key in student.keys():
    print("Found")
else:
    print("Not found")

# other similar  way:

# print(student.get(key,"Not found"))