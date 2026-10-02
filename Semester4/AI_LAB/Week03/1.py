student = {
    "name": "Mirza Zain Ali Baig",
    "age": "twenty one",
    "course": "Software Engineering"
}

#.items() returns both the key and value together as pairs.

ascending = dict(sorted(student.items(), key=lambda item: item[1]))
descending = dict(sorted(student.items(), key = lambda itemss:itemss[1],reverse=True))
# dict convert items into dictionary
print(ascending)
print(descending)