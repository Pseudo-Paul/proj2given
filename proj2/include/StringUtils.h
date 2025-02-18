#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>

class StringUtils {
public:
    static std::string Capitalize(const std::string &input);
    static std::string Lower(const std::string &input);
    static std::string Upper(const std::string &input);
    static std::string Strip(const std::string &input);
    static std::string LStrip(const std::string &input);
    static std::string RStrip(const std::string &input);
    static std::string Replace(const std::string &input, const std::string &oldSub, const std::string &newSub);
};

#endif // STRINGUTILS_H
