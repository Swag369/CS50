import csv
from sys import argv

def main():
    Dict={}
    filloutdatabase(Dict, argv)
    sequences=Dict["name"]
    Dict.pop("name")

    f=open(argv[2], "r")    #reading the fullstrand
    fullstrand=f.read()
    f.close()

    maxcounts={}               #initializing a dict to keep count of max things reached
    for i in sequences:
        maxcounts[i]=0

    for i in sequences: #check through for each sequence
        count = 0   #count of the consecutive repeats
        wasinchain=False    #variable to see if we should increment the count
        j=0
        while(j<len(fullstrand)):
            if fullstrand[j]==i[0]: #if the letter is the same
                if compare(fullstrand, j, i)==True: #if this is one of the strands
                    j += len(i)-1
                    if wasinchain==True:
                        count+=1
                    else:
                        wasinchain=True
                        count=1
                    if maxcounts.get(i)<count:
                        maxcounts[i]=count
                else:
                    wasinchain=False
            else:
                wasinchain=False

            j+=1

    findperson(Dict, maxcounts, sequences)

def filloutdatabase(Dict, argv):
    with open(argv[1], 'r') as f:   #opening the csv
        database = csv.reader(f)
        for row in database:        #copying each row
            Dict[row[0]]=row[1:len(row)]    #Dict key is always name and then put a list in for the other values


def compare(fullstrand, j, i):
    if len(fullstrand)<j+len(i):
        return False
    for m in range(1, len(i)):
        if i[m]!=fullstrand[j+m]:
            return False
    return True

def findperson(Dict, maxcount, sequences):
    culprit="No Match"
    for i in Dict:#check everyone in dictionary
        isculprit=True
        for j in range(0, len(maxcount)): #checking each value for each strand sequence
            if (Dict.get(i))[j]!=str(maxcount.get(sequences[j])): #if they dont match, break
                isculprit=False
                break
        if isculprit==True:#if he didnt miss any indicies, hes the one
            culprit=i
            break
    print(culprit)

if len(argv)!=3:
        print("ERROR")
else:
    main()