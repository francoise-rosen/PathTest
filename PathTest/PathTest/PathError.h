
#ifndef PathError_h
#define PathError_h
#include <string>

class PathNotFound
{
public:
    PathNotFound (const std::string& origin, const std::string& dest)
    :o {origin}, d {dest} {}
    std::string what() const {return "path from " + o + " to " + d + "not found"; }
private:
    std::string o;
    std::string d;
    
};

class IllegalArgument
{
public:
    IllegalArgument ()
    {}
    std::string what() const {return "Bad Input"; }
};

#endif /* PathError_h */

