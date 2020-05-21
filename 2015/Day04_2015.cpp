/*
*   I'm aware that there are libraries available that will perform MD5
*   calculations. I wrote my own code for the MD5 algorithm to learn.
*/

#include <iostream>
#include <string>
#include <stdint.h>
#include <cmath>
#include "MD5.h"

int main()
{
    std::string secretKey = "ckczppom117946";
    int keyFollower = 1;

    MD5{secretKey};
}