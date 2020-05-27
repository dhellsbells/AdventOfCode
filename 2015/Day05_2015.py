niceStrings = 0
niceStrings2 = 0

with open("Day05_2015.txt") as file:
    for line in file:
        vowels = 0
        dblLetter = False
        dblOtherLetter = False
        badStrings = False
        repeatedPair = False
        prevChar =''
        prevChar2 = ''

        for char in line:
            if (char == 'a') or (char == 'e') or (char == 'i') or (char == 'o') or (char == 'u'):
                vowels += 1
            if char == prevChar:
                dblLetter = True
            if char == prevChar2:
                dblOtherLetter = True
            if ((prevChar + char) == 'ab') or ((prevChar + char) == 'cd') or ((prevChar + char) == 'pq') or ((prevChar + char) == 'xy'):
                badStrings = True
            prevChar2 = prevChar
            prevChar = char

        if (vowels >= 3) and (dblLetter == True) and (badStrings == False):
            niceStrings += 1
        
        for i in range(len(line)-3):
            for j in range(i+2, len(line)-1):
                if line[i:i+2] == line[j:j+2]:
                    repeatedPair = True

        if (dblOtherLetter == True and repeatedPair == True):
            niceStrings2 += 1

file.close()

print("The number of nice strings in Santa's text file: " + str(niceStrings))
print("The number of nice strings under the new rules: " + str(niceStrings2))
