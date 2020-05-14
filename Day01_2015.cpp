#include <iostream>
#include <fstream>

int main()
{
    int floor = 0;
    int position = 0;
    bool setFinal = false;
    int finalPosition = 0;

    std::ifstream file("Day01_2015.txt");
    char c;
    while (file.get(c))
    {
        if (c == '(')
            floor++;
        else if (c == ')')
            floor--;
        position++;
        if (floor == -1 && !setFinal)
        {
            finalPosition = position;
            setFinal = true;
        }
    }

    file.close();
    
    std::cout << "The floor is: " << floor << "\n";
    std::cout << "The position of the first character that enters the basement is: " << finalPosition;

    return 0;
}