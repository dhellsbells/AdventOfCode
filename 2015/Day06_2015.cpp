#include <iostream>
#include <fstream>
#include <string>

std::string* split(std::string& s, int size, char delim);

int main()
{
    const int xMax = 1000;
    const int yMax = 1000;

    std::ifstream file("Day06_2015.txt");
    std::string line;

    int* grid = new int[xMax * yMax]{0};
    int* grid2 = new int[xMax * yMax]{0};

    while (std::getline(file, line))
    {
        int numElements = 0;

        if (line[1] == 'u')
            numElements = 5;
        else if (line[1] == 'o')
            numElements = 4;

        std::string* xList = split(line, numElements, ' ');

        std::string* xy = split(xList[numElements - 3], 2, ',');
        int x1 = std::stoi(xy[0]);
        int y1 = std::stoi(xy[1]);
        std::string* xy2 = split(xList[numElements - 1], 2, ',');
        int x2 = std::stoi(xy2[0]) + 1;
        int y2 = std::stoi(xy2[1]) + 1;

        if (xy != nullptr)
            delete[] xy;
        if (xy2 != nullptr)
            delete[] xy2;

        if (numElements == 5)
        {
            if (xList[1] == "on")
            {
                for (int i = x1; i < x2; i++)
                {
                    for (int j = y1; j < y2; j++)
                    {
                        grid[xMax * i + j] = 1;
                        grid2[xMax * i + j]++;
                    }
                }
            }
            else if (xList[1] == "off")
            {
                for (int i = x1; i < x2; i++)
                {
                    for (int j = y1; j < y2; j++)
                    {
                        grid[xMax * i + j] = 0;
                        if (grid2[xMax * i + j] > 0)
                            grid2[xMax * i + j]--;
                    }
                }
            }
            else
            {
                std::cout << "Error: 5list[1] returned incorrect string\n";
                file.close();
                if (xList != nullptr)
                    delete[] xList;
                if (grid != nullptr)
                    delete[] grid;
                if (grid2 != nullptr)
                    delete[] grid2;
                return -1;
            }
        }
        else if (numElements == 4)
        {
            for (int i = x1; i < x2; i++)
            {
                for (int j = y1; j < y2; j++)
                {
                    if (grid[xMax * i + j] == 0)
                        grid[xMax * i + j] = 1;
                    else if (grid[xMax * i + j] == 1)
                        grid[xMax * i + j] = 0;
                    else
                    {
                        std::cout << "Error: grid value not 0 or 1\n";
                        file.close();
                        if (xList != nullptr)
                            delete[] xList;
                        if (grid != nullptr)
                            delete[] grid;
                        if (grid2 != nullptr)
                            delete[] grid2;
                        return -1;
                    }

                    grid2[xMax * i + j] += 2;
                }
            }
        }
        else
        {
            std::cout << "Error: bad list size returned\n";
            file.close();
            if (xList != nullptr)
                delete[] xList;
            if (grid != nullptr)
                delete[] grid;
            if (grid2 != nullptr)
                delete[] grid2;
            return -1;
        }

        if (xList != nullptr)
            delete[] xList;
    }

    file.close();

    int lightCount = 0;
    int brightness = 0;

    for (int i = 0; i < (xMax * yMax); i++)
    {
        if (grid[i] == 1)
            lightCount++;
        brightness += grid2[i];
    }
        
    std::cout << "Total number of lights turned on: " << lightCount << "\n";
    std::cout << "Cumulative light brightness: " << brightness << "\n";

    if (grid != nullptr)
        delete[] grid;
    if (grid2 != nullptr)
        delete[] grid2;

    return 0;
}

// splits a string into a string array based on a given char
// delimiter. Could be generalized with minimal alteration.
// NOTE: memory handled by CALLER.
std::string* split(std::string& s, int size, char delim)
{
    std::string* lineElements = new std::string[size];
    
    size_t last = 0;
    size_t next = s.find(delim);
    int index = 0;

    while (next != std::string::npos)
    {
        if (index >= size)
            throw("Index out of range.");

        lineElements[index] = s.substr(last, next - last);
        last = next + 1;
        next = s.find(delim, last);

        index++;
    }

    if (index < size)
        lineElements[index] = s.substr(last, next); // next should be npos which indicates all characters to end of string
    else
        throw("Index out of range.");
    
    return lineElements;
}