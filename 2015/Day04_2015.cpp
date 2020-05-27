/*
*   Advent of Code Day 4, 2015.
*   Uses self-coded MD5 algorithm
*   Not particularly efficient for multiple runs.
*/

#include <iostream>
#include <string>
#include "MD5.h"

int main()
{
    std::string secretKey = "ckczppom";
    int keyFollower = 1;

    while(true)
    {
        std::string fullKey = secretKey + std::to_string(keyFollower);
        std::string MD5Hash = MD5(fullKey);

        if (MD5Hash.substr(0,5) == "00000")
        {
            std::cout << "The lowest positive number leading to the MD5 hash starting with at least 5 zeroes is: " << keyFollower << "\n";
            std::cout << "The AdventCoin MD5 hash for " << secretKey << " is: " << MD5Hash;
            break;
        }
        
        keyFollower++;
    }

    while(true)
    {
        std::string fullKey = secretKey + std::to_string(keyFollower);
        std::string MD5Hash = MD5(fullKey);

        if (MD5Hash.substr(0,6) == "000000")
        {
            std::cout << "The lowest positive number leading to the MD5 hash starting with at least 6 zeroes is: " << keyFollower << "\n";
            std::cout << "The AdventCoin MD5 hash for " << secretKey << " is: " << MD5Hash;
            break;
        }
        
        keyFollower++;
    }
    
    return 0;
}