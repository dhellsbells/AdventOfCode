/*  MD5.h
*
*   MD5 Hash generation function header file
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

#pragma once
#include <stdint.h>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

std::string MD5(std::string &input);

void MD5Init(uint32_t &a0, uint32_t &b0, uint32_t &c0, uint32_t &d0, uint32_t* s, uint32_t* K);
void sInit(uint32_t* s);
void KInit(uint32_t* K);

uint32_t* MD5Pad(std::string &input);
std::string MD5Main(uint32_t &a0, uint32_t &b0, uint32_t &c0, uint32_t &d0, uint32_t* s, uint32_t* K, uint32_t* M, uint32_t len);

uint32_t RotateLeft(uint32_t x, uint32_t n);
uint32_t ReverseBytes(uint32_t num);
uint32_t F(uint32_t x, uint32_t y, uint32_t z);
uint32_t G(uint32_t x, uint32_t y, uint32_t z);
uint32_t H(uint32_t x, uint32_t y, uint32_t z);
uint32_t I(uint32_t x, uint32_t y, uint32_t z);