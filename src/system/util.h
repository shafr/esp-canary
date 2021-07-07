#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_

void stringToIntArray(const char *inString, char separator, uint8_t *resArray,
                      int structSize, int base);
String IPAddressToString(int ip);
void obfuscateHost();

#endif
