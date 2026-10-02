student = {
    "name": "Mirza Zain Ali Baig",
    "age": "twenty one",
    "course": "Software Engineering"
}

subject = {
    "subject": "AI"
}


# Modern Techhnique to merge dictionary
# print(student | subject)


# Old Technique:

print({**student,**subject}) # here,**  is called dictionary unpacking.conceptully it removes the {}  braces

# *list1       # unpack a list/iterable

# numbers = [1, 2, 3]

# new_numbers = [*numbers, 4]
# output: [1, 2, 3, 4]
