from cs50 import get_string
from math import floor

s=get_string("Number: ")
oddsum=0
evensum=0
length=len(s)

print("odds")

for i in range(-2, -(length+1), -2):
	tensdigit=floor((2*int(s[i]))/10)
	onesdigit=(2*int(s[i]))%10
	oddsum+=tensdigit+onesdigit
	print("index: "+str(i)+" is "+ s[i], "which multiplied by two is "+str(tensdigit)+ " and "+ str(onesdigit))

print("evens")
for j in range(-1, -(length+1), -2):
	evensum+=int(s[j])
	print("index: "+str(j)+" is "+ s[j])
print (f"oddsum {oddsum}")
print (f"evensum {evensum}")

if((evensum+oddsum)%10!=0):
	print("INVALID")
else:
	if length==13 and s[0]=="4":
		print("VISA")
	
	elif length==15:
		if s[0]=="3":
			if s[1]=="4" or s[1]=="7":
				print("AMEX")
	
	elif length==16:
		if s[0]=="4":
			print("VISA")
		elif int(s[0])>50 and int(s[0])<56:
			print("MASTERCARD")
	else:
		print("INVALID")