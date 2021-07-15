from cs50 import get_string

sentences = 0
words = 0
letters = 0
s = get_string("Text: ")
for i in s:
    if i == "." or i == "?" or i == "!":
        sentences+=1
    elif i == " ":
        words+=1
    elif (i>="a" and "z">=i) or ("Z">=i and i>="A"):
        letters+=1
words+=1
index=0.0588 * 100*(letters/words) - 0.296 * 100*(sentences/words) - 15.8
index=int(round(index, 0))
if index >= 16:
    print("Grade 16+")
elif index <1:
    print("Before Grade 1")
else:
    print("Grade", index)