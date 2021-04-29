//
//  stringTrim.h
//  PathTest
//
//  Created by syfo_dias on 29/04/2021.
//

#ifndef stringTrim_h
#define stringTrim_h
#include <string>

void ltrim (std::string& s)
{
    auto p = std::find_if (s.begin(), s.end(), [] (char ch) {return ! std::isspace(ch);});
    s.erase (s.begin(), p);
}

void rtrim (std::string& s)
{
    auto p = std::find_if (s.rbegin(), s.rend(), [] (char ch) {return ! std::isspace(ch);});
    s.erase (p.base(), s.end());
}

#endif /* stringTrim_h */
