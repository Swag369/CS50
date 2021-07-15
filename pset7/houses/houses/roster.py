import csv
from sys import argv
from cs50 import SQL

def main():
    db = SQL("sqlite:///students.db")
    names = db.execute('SELECT first, middle, last FROM students WHERE house == "'+argv[1]+'" ORDER BY last, first')
    birthdays = db.execute('SELECT birth FROM students WHERE house == "'+argv[1]+'" ORDER BY last, first')
    for i in range(len(names)):
        if names[i]["middle"]!=None:
            print(names[i]["first"], names[i]["middle"], names[i]["last"], end = "")
            print(", born", birthdays[i]["birth"])
        else:
            print(names[i]["first"], names[i]["last"], end = "")
            print(", born", birthdays[i]["birth"])

if len(argv)!=2:
    print("ERROR")
else:
    main()