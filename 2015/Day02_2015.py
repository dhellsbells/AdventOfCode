paperFeet = 0
ribbonFeet = 0

with open("Day02_2015.txt") as file:
    for line in file:
        l, w, h = (int(dim) for dim in line.split('x'))

        lw = l * w
        wh = w * h
        lh = l * h
        sFace = lw

        if wh < sFace:
            sFace = wh
        if lh < sFace:
            sFace = lh
            
        if w < l:
            sSide1 = w
            sSide2 = l
        else:
            sSide1 = l
            sSide2 = w
        if h < sSide1:
            sSide2 = sSide1
            sSide1 = h
        elif h < sSide2:
            sSide2 = h

        paperFeet += 2*lw + 2*wh + 2*lh + sFace
        ribbonFeet += 2*sSide1 + 2*sSide2 + l*w*h

file.close()

print('Total square feet of paper needed: ' + str(paperFeet))
print('Total feet of ribbon needed: ' + str(ribbonFeet))
