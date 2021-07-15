import csv
from sys import argv
from cs50 import SQL


def filloutdatabase(db):
    people = {}
    with open(argv[1], 'r') as f:   #opening the csv
        people = csv.DictReader(f)
        for row in people:
            if (len(row.get('name').split())==2):
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", (row['name'].split())[0], None, (row['name'].split())[1], row['house'], row['birth'])
            else:
                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", (row['name'].split())[0], (row['name'].split())[1], (row['name'].split())[2], row['house'], row['birth'])
                
if len(argv)!=2:
    print("ERROR")

else:
    db = SQL("sqlite:///students.db")
    filloutdatabase(db)
