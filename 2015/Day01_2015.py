floor = 0
position = 0
setFinal = False
finalPosition = 0

with open("Day01_2015.txt") as file:
    for line in file:
        for char in line:
            if char == '(':
                floor += 1
            elif char == ')':
                floor -= 1
            position += 1

            if floor == -1 and not setFinal:
                finalPosition = position
                setFinal = True

file.close()

print("The floor is: " + str(floor))
print("The position of the first character that enters the basement is: " + str(finalPosition))
