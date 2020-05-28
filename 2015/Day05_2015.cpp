#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main()
{
    std::ifstream file("Day05_2015.txt");
    std::string line;

    int niceStrings = 0;
    int niceStrings2 = 0;

    while (std::getline(file, line))
    {
        int vowels = 0;
        bool dblLetter = false;
        bool dblOtherLetter = false;
        bool badStrings = false;
        bool repeatedPair = false;
        char prevChar = '\0';
        char prevChar2 = '\0';
        
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == 'a' || line[i] == 'e' || line[i] == 'i' || line[i] == 'o' || line[i] == 'u')
                vowels++;
            if (line[i] == prevChar)
                dblLetter = true;
            if (line[i] == prevChar2)
                dblOtherLetter = true;

            std::string lastTwoChars{prevChar, line[i]};

            if (lastTwoChars == "ab" || lastTwoChars == "cd" || lastTwoChars == "pq" || lastTwoChars == "xy")
                badStrings = true;

            prevChar2 = prevChar;
            prevChar = line[i];
        }

        if (vowels >= 3 && dblLetter == true && badStrings == false)
            niceStrings++;

        for (int i = 0; i < line.size() - 3; i++)
        {
            for (int j = i + 2; j < line.size() - 1; j++)
            {
                if (line[i] == line[j] && line[i+1] == line[j+1])
                    repeatedPair = true;
            }
        }

        if (dblOtherLetter == true && repeatedPair == true)
            niceStrings2++;
    }

    file.close();

    std::cout << "The number of nice strings in Santa's text file: " << niceStrings << "\n";
    std::cout << "The number of nice strings under the new rules: " << niceStrings2;

    return 0;
}