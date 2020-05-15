#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
    int paperFeet = 0;
    int ribbonFeet = 0;
    int lw, wh, lh, sFace, sSide1, sSide2;

    std::ifstream file("Day02_2015.txt");
    std::string line;
    
    while (std::getline(file, line))
    {
        std::string tmp;
        int l, w, h;

        std::istringstream bruce(line);
        std::getline(bruce, tmp, 'x');
        l = std::stoi(tmp);
        std::getline(bruce, tmp, 'x');
        w = std::stoi(tmp);
        std::getline(bruce, tmp);
        h = std::stoi(tmp);

        lw = l * w;
        wh = w * h;
        lh = l * h;
        sFace = lw;

        if (wh < sFace)
            sFace = wh;
        if (lh < sFace)
            sFace = lh;
        
        if (w < l)
        {
            sSide1 = w;
            sSide2 = l;
        }
        else
        {
            sSide1 = l;
            sSide2 = w;
        }
        if (h < sSide1)
        {
            sSide2 = sSide1;
            sSide1 = h;
        }
        else if (h < sSide2)
            sSide2 = h;
        
        paperFeet += 2*lw + 2*wh + 2*lh + sFace;
        ribbonFeet += 2*sSide1 + 2*sSide2 + l*w*h;
    }

    file.close();

    std::cout << "Total square feet of paper needed: " << paperFeet << "\n";
    std::cout << "Total feet of ribbon needed: " << ribbonFeet;

    return 0;
}