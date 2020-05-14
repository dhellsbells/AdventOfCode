#include <iostream>
#include <fstream>
#include <set>
#include <utility>

int main()
{
    int x, y, sx, sy, rx, ry;
    x = y = sx = sy = rx = ry = 0;

    std::set <std::pair <int, int>> visitMap1;
    std::set <std::pair <int, int>> visitMap2;
    visitMap1.emplace(0, 0);
    visitMap2.emplace(0, 0);

    int uniqueVisits1 = 1, uniqueVisits2 = 1;
    bool isSanta = true;

    std::ifstream file("Day03_2015.txt");
    char c;
    
    while (file.get(c))
    {
        if (c == '<')
        {
            x -= 1;
            if (isSanta)
                sx -= 1;
            else
                rx -= 1;
        }
        else if (c == '>')
        {
            x += 1;
            if (isSanta)
                sx += 1;
            else
                rx += 1;
        }
        else if (c == '^')
        {
            y += 1;
            if (isSanta)
                sy += 1;
            else
                ry += 1;
        }
        else if (c == 'v')
        {
            y -= 1;
            if (isSanta)
                sy -= 1;
            else
                ry -= 1;
        }

        if (visitMap1.count(std::make_pair(x, y)) == 0)
        {
            visitMap1.emplace(x, y);
            uniqueVisits1++;
        }
                
        if (isSanta)
        {
            if (visitMap2.count(std::make_pair(sx, sy)) == 0)
            {
                visitMap2.emplace(sx, sy);
                uniqueVisits2++;
            }
        }
        else
        {
            if (visitMap2.count(std::make_pair(rx, ry)) == 0)
            {
                visitMap2.emplace(rx, ry);
                uniqueVisits2++;
            }
        }

        isSanta = !isSanta;
    }

    file.close();

    std::cout << "Number of unique houses visited by Santa alone: " << uniqueVisits1 << "\n";
    std::cout << "Number of unique houses visited by Santa and Robo-Santa: " << uniqueVisits2;
}