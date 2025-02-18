#include "StringUtils.h"
#include <algorithm>
#include <cctype>

std::string StringUtils::Capitalize(const std::string &input) {
    if (input.empty()) return input;
    std::string result = input;
    result[0] = std::toupper(result[0]);
    return result;
}

std::string StringUtils::Lower(const std::string &input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string StringUtils::Upper(const std::string &input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string StringUtils::Strip(const std::string &input) {
    size_t start = input.find_first_not_of(" \t\n\r");
    size_t end = input.find_last_not_of(" \t\n\r");

    if (start == std::string::npos) return "";
    return input.substr(start, end - start + 1);
}

std::string StringUtils::LStrip(const std::string &input) {
    size_t start = input.find_first_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : input.substr(start);
}

std::string StringUtils::RStrip(const std::string &input) {
    size_t end = input.find_last_not_of(" \t\n\r");
    return (end == std::string::npos) ? "" : input.substr(0, end + 1);
}

std::string StringUtils::Replace(const std::string &input, const std::string &oldSub, const std::string &newSub) {
    std::string result = input;
    size_t pos = 0;
    while ((pos = result.find(oldSub, pos)) != std::string::npos) {
        result.replace(pos, oldSub.length(), newSub);
        pos += newSub.length();
    }
    return result;
}
