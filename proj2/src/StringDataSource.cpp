#include "StringDataSource.h"
#include <iostream> // Add for debugging

CStringDataSource::CStringDataSource(const std::string &str) : DString(str), DIndex(0) {
    std::cout << "CStringDataSource initialized with string: " << DString << std::endl; // Debug print
}

bool CStringDataSource::End() const noexcept {
    return DIndex >= DString.length();
}

bool CStringDataSource::Get(char &ch) noexcept {
    if(DIndex < DString.length()){
        ch = DString[DIndex];
        DIndex++;
        std::cout << "Read char: " << ch << " at index: " << DIndex - 1 << std::endl; // Debug print
        return true;
    }
    std::cout << "Reached end of string." << std::endl;
    return false;
}

bool CStringDataSource::Peek(char &ch) noexcept {
    if(DIndex < DString.length()){
        ch = DString[DIndex];
        return true;
    }
    return false;
}

bool CStringDataSource::Read(std::vector<char> &buf, std::size_t count) noexcept {
    buf.clear();
    while(buf.size() < count){
        char TempChar;
        if(Get(TempChar)){
            buf.push_back(TempChar);
        }
        else{
            break;
        }
    }
    std::cout << "Read buffer: " << std::string(buf.begin(), buf.end()) << std::endl; // Debug print
    return !buf.empty();
}
