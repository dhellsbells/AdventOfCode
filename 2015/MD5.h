/*  MD5.h
*
*   MD5 Hash generation function
*
*/

#pragma once
#include <stdint.h>
#include <cmath>
#include <string>
#include <iostream>

// Creates an MD5 class object. This takes up space but allows
// certain calculations and declarations to only take place once.
class MD5
{
public:
    
    MD5();
    MD5(std::string input);

private:

    
    uint32_t K[64], s[64], M[16];
    uint8_t Digest[16];

    static const uint32_t A0 = 0x67452301;
    static const uint32_t B0 = 0xefcdab89;
    static const uint32_t C0 = 0x98badcfe;
    static const uint32_t D0 = 0x10325476;
    uint32_t A, B, C, D, AA, BB, CC, DD;

    void Init();
    void Encode(std::string input);
    void Process();
    uint32_t ReverseBytes(uint32_t value);
    uint32_t RotateLeft(uint32_t x, uint32_t n);
    uint32_t F(uint32_t x, uint32_t y, uint32_t z);
    uint32_t G(uint32_t x, uint32_t y, uint32_t z);
    uint32_t H(uint32_t x, uint32_t y, uint32_t z);
    uint32_t I(uint32_t x, uint32_t y, uint32_t z);
};

MD5::MD5()
{
    Init();
    //Encode("");

    M[0] = 0x80000000;

    for (int i = 1; i < 16; i++)
        M[i] = 0;

    for (int i = 0; i < 16; i++)
    {
        std::cout << std::hex << M[i] << " ";
    }

    std::cout << "\n";

    Process();
}

MD5::MD5(std::string input)
{
    Init();
    Encode(input);
    Process();
}

void MD5::Init()
{
    A = AA = A0;
    B = BB = B0;
    C = CC = C0;
    D = DD = D0;

    for (int i = 0; i < 64; i++)
        K[i] = floor(pow(2, 32) * fabs(sin(i + 1)));

    for (int i = 0; i < 4; i++)
    {
        s[i] = s[i+4] = s[i+8] = s[i+12] = 2 + (5 * (i + 1));
        
        if (i - 1 < 0)
            s[i+16] = s[i+20] = s[i+24] = s[i+28] = 5;
        else
            s[i+16] = s[i+20] = s[i+24] = s[i+28] = s[i+15] + i + 3;

        if (i % 2 == 0)
            s[i+32] = s[i+36] = s[i+40] = s[i+44] = pow((i + 2), 2);
        else
            s[i+32] = s[i+36] = s[i+40] = s[i+44] = pow((i + 1), 2) + 7;

        if (i - 1 < 0)
            s[i+48] = s[i+52] = s[i+56] = s[i+60] = 6;
        else
            s[i+48] = s[i+52] = s[i+56] = s[i+60] = s[i+47] + i + 3;
    }
}

// Encodes string to char array, appends 1 to end, fills remainder
// with zeroes except final element. Final element is a numerical
// representation of the original message length - currently
// limited to 255 characters.
void MD5::Encode(std::string input)
{
    unsigned char m[64];

    const unsigned char* chInput = (const unsigned char*)input.c_str();
    for  (int i = 0; i < input.length(); i++)
        m[i] = chInput[i];

    m[input.length()] = 0x80;

    for (int i = (input.length() + 1); i < 64; i++)
        m[i] = 0;
    
    m[56] = input.length() * 8;

    for (int i = 0, j = 0; i < 16; i++, j+= 4)
    {
        M[i] = (uint32_t)m[j] | ((uint32_t)m[j+1] << 8) | ((uint32_t)m[j+2] << 16) | ((uint32_t)m[j+3] << 24);
    }

    std::cout << "M[i]: ";

    for (int i = 0; i < 16; i++)
    {
        std::cout << std::hex << M[i] << " ";
    }

    std::cout << "\n";

}

void MD5::Process()
{
    for (int i = 0; i < 64; i++)
    {
        uint32_t f;
        uint8_t g;

        if ((i >= 0) && (i < 16))
        {
            f = F(B, C, D);
            g = i;
        }
        else if ((i >= 16) && (i < 32))
        {
            f = G(B, C, D);
            g = (((i * 5) + 1) % 16);
        }
        else if ((i >= 32) && (i < 48))
        {
            f = H(B, C, D);
            g = (((i * 3) + 5) % 16);
        }
        else if ((i >= 48) && (i < 64))
        {
            f = I(B, C, D);
            g = ((i * 7) % 16);
        }

        // std::cout << std::dec << i << ".  g = " << g << "\ts = " <<  s[i] << "\tK = " << std::hex << K[i] << "\n";

        f = f + A + K[i] + M[g];
        A = D;
        D = C;
        C = B;
        B = B + RotateLeft(f, s[i]);

        if (i == 15)
        {
            std::cout << std::hex << "f: " << f << "\tA: " << A << "\tD: " << D << "\tC: " << C << "\tB: " << B << "\ts[i]: " << std::dec << s[i] << std::hex << "\tK: " << K[i] << "\n";
            std::cout << std::hex << "M[i]: " << M[i] << "\n";
        }
    }

    AA = ReverseBytes(AA + A);
    BB = ReverseBytes(BB + B);
    CC = ReverseBytes(CC + C);
    DD = ReverseBytes(DD + D);

    std::cout << "A: " << std::hex << AA << "\n";
    std::cout << "B: " << std::hex << BB << "\n";
    std::cout << "C: " << std::hex << CC << "\n";
    std::cout << "D: " << std::hex << DD << "\n";

    std::cout << "MD5 Hash: " << std::hex << AA << BB << CC << DD << "\n";
}

uint32_t MD5::ReverseBytes(uint32_t num)
{
    uint32_t b0, b1, b2, b3;

    b0 = (num & 0x000000ff) << 24;
    b1 = (num & 0x0000ff00) << 8;
    b2 = (num & 0x00ff0000) >> 8;
    b3 = (num & 0xff000000) >> 24;

    return (b0 | b1 | b2 | b3);
}

uint32_t MD5::RotateLeft(uint32_t x, uint32_t n)
{
    return ((x << n) | (x >> (32 - n)));
}

uint32_t MD5::F(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & y) | (~x & z));
}

uint32_t MD5::G(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & z) | (y & ~z));
}

uint32_t MD5::H(uint32_t x, uint32_t y, uint32_t z)
{
    return (x ^ y ^ z);
}

uint32_t MD5::I(uint32_t x, uint32_t y, uint32_t z)
{
    return (y ^ (x | ~z));
}