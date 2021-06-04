//
//  DMUtils.hpp
//  DataManager
//
//  Created by 林思行 on 2021/6/4.
//

#ifndef DMUtils_hpp
#define DMUtils_hpp

#include <string>
#include <iomanip>
#include <sstream>

namespace DMUtils {

/// BKDR Hash Function
unsigned int BKDRHash(const std::string str);

std::string double2FixedStr(double num, unsigned fix);

}

#endif /* DMUtils_hpp */
