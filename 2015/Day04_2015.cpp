/*
*   Shell tests MD5 algorithm. Still need to complete code for Day 4
*/

#include <iostream>
#include <string>
#include "MD5.h"

int main()
{
    std::string secretKey = "ckczppom3938038";
    int keyFollower = 1;

    std::string MD5Hash = MD5(secretKey);

    std::cout << "MD5 Hash for " << secretKey << " is: " << MD5Hash << "\n";

    return 0;
}