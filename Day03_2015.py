x = 0
y = 0
sx = 0
sy = 0
rx = 0
ry = 0

visitDict = {}
visitDict[0, 0] = 1
uniqueVisits1 = 1
visitDict2 = {}
visitDict2[0, 0] = 1
uniqueVisits2 = 1
isSanta = True

with open("day03_2015.txt") as file:
    for line in file:
        for char in line:
            if char == '<':
                x -= 1
                if isSanta:
                    sx -= 1
                else:
                    rx -= 1
            elif char == '>':
                x += 1
                if isSanta:
                    sx += 1
                else:
                    rx += 1
            elif char == '^':
                y += 1
                if isSanta:
                    sy += 1
                else:
                    ry += 1
            elif char == 'v':
                y -= 1
                if isSanta:
                    sy -= 1
                else:
                    ry -= 1

            if (x, y) not in visitDict:
                visitDict[x, y] = 1
                uniqueVisits1 += 1

            if isSanta:
                if (sx, sy) not in visitDict2:
                    visitDict2[sx, sy] = 1
                    uniqueVisits2 += 1
            else:
                if (rx, ry) not in visitDict2:
                    visitDict2[rx, ry] = 1
                    uniqueVisits2 += 1
                    
            isSanta = not isSanta

file.close()

print("Number of unique houses visited by Santa alone: " + str(uniqueVisits1))
print("Number of unique houses visited by Santa and Robo-Santa: " + str(uniqueVisits2))
