import csv
from cs50 import SQL

# titles = {}

# with open("Favorite TV Shows - Form Responses 1.csv", "r") as file:
#     reader = csv.DictReader(file)
#     for row in reader:
#         title = row["title"].strip().upper()
#         # initialize dict item if it doesnt exist
#         if not title in titles:
#             titles[title] = 0
#         titles[title] += 1


# for title in sorted(titles, key=lambda title: titles[title], reverse=True):
#     print(title, titles[title])

# title = input("Title: ").strip().upper()

# with open("Favorite TV Shows - Form Responses 1.csv", "r") as file:
#     reader = csv.DictReader(file)
#     counter = 0
#     for row in reader:
#         if row["title"].strip().upper() == title:
#             counter += 1

# print(counter)

open("shows.db", "w").close()
db = SQL("sqlite:///shows.db")

db.execute("CREATE TABLE shows (id INTEGER, title TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id))")

with open("Favorite TV Shows - Form Responses 1.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        title = row["title"].strip().upper()
        id = db.execute("INSERT INTO shows (title) VALUES(?)", title)
        for genre in row["genres"].split(", "):
            db.execute("INSERT INTO genres (show_id, genre) VALUES (?, ?)", id, genre)