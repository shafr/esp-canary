#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_

void stringToIntArray(const char* str, char sep, uint8_t* macArr, int maxBytes, int base);
void obfuscateHost();

#endif