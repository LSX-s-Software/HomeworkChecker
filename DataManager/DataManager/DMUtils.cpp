//
//  DMUtils.cpp
//  DataManager
//
//  Created by 林思行 on 2021/6/4.
//

#include "DMUtils.hpp"

namespace DMUtils {

unsigned int BKDRHash(const std::string str) {
    char *strPtr = const_cast<char *>(str.c_str());
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*strPtr) {
        hash = hash * seed + (*strPtr++);
    }

    return (hash & 0x7FFFFFFF);
}

std::string double2FixedStr(double num, unsigned fix) {
    std::stringstream ss;
    ss << std::setiosflags(std::ios::fixed) << std::setprecision(fix) << num;
    return ss.str();
}

}
