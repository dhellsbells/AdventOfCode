# negative list indices:
#   [-1] second corner (inclusive) of coordinates to be manipulated
#   [-2] 'through' - can be safely ignored
#   [-3] first corner (inclusive) of coordinates to be manipulated
#   [-4],([-5]) indices of manipulation command(s). Use positive indices.

grid = [[0 for y in range(1000)] for x in range(1000)]
grid2 = [[0 for y in range(1000)] for x in range(1000)]

with open("Day06_2015.txt") as file:
    for line in file:
        xList = line.split()
        
        xy = list(map(int, xList[-3].split(',')))
        xy2 = list(map(int, xList[-1].split(',')))
        
        if len(xList) == 5:
            if xList[1] == 'on':
                for x in range(xy[0], (xy2[0]+1)):
                    for y in range(xy[1], (xy2[1]+1)):
                        grid[x][y] = 1
                        grid2[x][y] += 1
            elif xList[1] == 'off':
                for x in range(xy[0], (xy2[0]+1)):
                    for y in range(xy[1], (xy2[1]+1)):
                        grid[x][y] = 0
                        if grid2[x][y] > 0:
                            grid2[x][y] -= 1
            else:
                print('Error: 5list[1] returned incorrect string')
                quit()
        elif len(xList) == 4:
            for x in range(xy[0], (xy2[0]+1)):
                    for y in range(xy[1], (xy2[1]+1)):
                        if grid[x][y] == 0:
                            grid[x][y] = 1
                        elif grid[x][y] == 1:
                            grid[x][y] = 0
                        else:
                            print('Error: grid value not 0 or 1')
                            quit()
                        grid2[x][y] += 2
        else:
            print('Error: bad list size returned')
            quit()

file.close()

lightCount = 0
brightness = 0

for x in range(1000):
    for y in range(1000):
        if grid[x][y] == 1:
            lightCount += 1
        brightness += grid2[x][y]

print ("Total number of lights turned on: " + str(lightCount))
print ("Cumulative light brightness: " + str(brightness))
