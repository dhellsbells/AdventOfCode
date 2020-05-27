/*  MD5.cpp
*
*   MD5 Hash generation function source file
*   Author: Dave Hellmer
*   Github: dhellsbells
*
*   Sources:
*       MD5 Wikipedia page:  https://en.wikipedia.org/wiki/MD5
*       IETF RFC 1321, MD5 Algorithm:  https://tools.ietf.org/html/rfc1321
*       Zedwood.com C++ implementation:  http://www.zedwood.com/article/cpp-md5-function
*       Stack Overflow, "Implementing a basic MD5 algorithm in c++":
*           https://stackoverflow.com/questions/10365351/implementing-a-basic-md5-algorithm-in-c
*       Stack Overflow, "MD5 Implementation in C++ is returning incorrect digest":
*           https://stackoverflow.com/questions/55623518/md5-implementation-in-c-is-returning-incorrect-digest"
*
*/

#include "MD5.h"

std::string MD5(std::string &input)
{
    if (input.length() > UINT32_MAX)
    {
        std::cout << "Maximum number of characters exceeded.\n";
        std::cout << "Input must be less than " << UINT32_MAX << " characters.\n";
        return "";
    }

    uint32_t a0, b0, c0, d0;
    uint32_t* s = new uint32_t[64];
    uint32_t* K = new uint32_t[64];

    MD5Init(a0, b0, c0, d0, s, K);
    uint32_t* M = MD5Pad(input);

    /*for (int i = 0; i < 16; i++)
        std::cout << std::hex << M[i] << " ";
    std::cout << "\n";*/

    std::string result = MD5Main(a0, b0, c0, d0, s, K, M, input.length());
    
    if (M != nullptr)
        delete[] M;
    if (K != nullptr)
        delete[] K;
    if (s != nullptr)
        delete[] s;

    return result;
}

void MD5Init(uint32_t &a0, uint32_t &b0, uint32_t &c0, uint32_t &d0, uint32_t* s, uint32_t* K)
{
    a0 = 0x67452301;
    b0 = 0xefcdab89;
    c0 = 0x98badcfe;
    d0 = 0x10325476;

    sInit(s);
    KInit(K);
}

void sInit(uint32_t* s)
{
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

void KInit(uint32_t* K)
{
    for (int i = 0; i < 64; i++)
        K[i] = floor(pow(2, 32) * fabs(sin(i + 1)));
}

// Takes input string, creates a char* buffer with its elements, pads
// it with a single 1 bit (as byte 0x80) and ends the buffer with 64-
// bit (as 8 char bytes) interpretation of the original string length.
// If buffer size isn't a multiple of 64 it is padded with zeroes
// between the 1 and the length to make it a multiple of 64.
uint32_t* MD5Pad(std::string &input)
{
    // 32-bit integer for input string size
    // NOTE: because this program is based on using a std::string for
    // input and it's maximum size is generally smaller than 2^32,
    // only a 32-bit integer is needed instead of 64-bit.
    uint32_t strLength = input.length();

    // How many multiples of 64 (bytes) does buffer 'm' need to be?
    // --> + 8 includes the 8 bytes for length. Leaving out the +1
    // for the 1 at end of input string fixes the math.
    uint32_t mult = ((strLength + 8) / 64) + 1;

    // Create char buffer m of a size that will fit each character,
    // a single 1 bit (followed by 7 zeroes - 0x80), between 0 and
    // 63 0s as padding and the final 8 bytes containing the length
    // of the input string.
    unsigned char* m = new unsigned char[64 * mult];

    // Copy input string into character buffer
    strcpy((char*)m, input.c_str());

    // Append '1000 0000' to character buffer
    m[strLength] = 0x80;

    // Fill remainder of buffer with zeroes
    for (int i = input.length() + 1; i < 64 * mult; i++)
        m[i] = 0;

    // Final 8 elements of buffer are 64-bit input length, low-order
    // first. This particular implementation only uses the first 32
    // bits due to existing string size limitations.
    
    for (int i = 0; i < 4; i++)
        m[i + (64 * mult) - 8] = ((strLength * 8) >> (i * 8)) & 0xff;

    // Return value - 32-bit integer array
    uint32_t* mRet = new uint32_t[16 * mult];

    // fill return value array using values from char array
    for (int i = 0, j = 0; i < 16; i++, j+= 4)
    {
        mRet[i] = (uint32_t)m[j] | ((uint32_t)m[j+1] << 8) | ((uint32_t)m[j+2] << 16) | ((uint32_t)m[j+3] << 24);
    }

    // Clean up character array
    delete[] m;

    // Return 32-bit integer array
    return mRet;
}


std::string MD5Main(uint32_t &a0, uint32_t &b0, uint32_t &c0, uint32_t &d0, uint32_t* s, uint32_t* K, uint32_t* M, uint32_t len)
{
    // Recalculate multiplier used in MD5Pad
    uint32_t mult = ((len + 8) / 64) + 1;

    // Outer loop. Repeated based on how many multiples
    // of 16 M is in size.
    for (int i = 0; i < mult; i++)
    {
        uint32_t A = a0;
        uint32_t B = b0;
        uint32_t C = c0;
        uint32_t D = d0;

        for (int j = 0; j < 64; j++)
        {
            uint32_t f;
            uint8_t g;

            if ((j >= 0) && (j < 16))
            {
                f = F(B, C, D);
                g = j;
            }
            else if ((j >= 16) && (j < 32))
            {
                f = G(B, C, D);
                g = (((j * 5) + 1) % 16);
            }
            else if ((j >= 32) && (j < 48))
            {
                f = H(B, C, D);
                g = (((j * 3) + 5) % 16);
            }
            else if ((j >= 48) && (j < 64))
            {
                f = I(B, C, D);
                g = ((j * 7) % 16);
            }

            // std::cout << std::dec << j << ".  g = " << g << "\ts = " <<  s[j] << "\tK = " << std::hex << K[j] << "\n";

            f = f + A + K[j] + M[g];
            A = D;
            D = C;
            C = B;
            B = B + RotateLeft(f, s[j]);
        }

        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    std::ostringstream md5String;
    md5String << std::hex << std::setfill('0') << std::setw(8) << ReverseBytes(a0);
    md5String << std::hex << std::setfill('0') << std::setw(8) << ReverseBytes(b0);
    md5String << std::hex << std::setfill('0') << std::setw(8) << ReverseBytes(c0);
    md5String << std::hex << std::setfill('0') << std::setw(8) << ReverseBytes(d0);
    
    return md5String.str();
}

uint32_t RotateLeft(uint32_t x, uint32_t n)
{
    return ((x << n) | (x >> (32 - n)));
}

uint32_t ReverseBytes(uint32_t num)
{
    uint32_t b0, b1, b2, b3;

    b0 = (num & 0x000000ff) << 24;
    b1 = (num & 0x0000ff00) << 8;
    b2 = (num & 0x00ff0000) >> 8;
    b3 = (num & 0xff000000) >> 24;

    return (b0 | b1 | b2 | b3);
}

uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & y) | (~x & z));
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z)
{
    return ((x & z) | (y & ~z));
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z)
{
    return (x ^ y ^ z);
}

uint32_t I(uint32_t x, uint32_t y, uint32_t z)
{
    return (y ^ (x | ~z));
}