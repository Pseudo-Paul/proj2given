#ifndef CDSVWRITER_H
#define CDSVWRITER_H

#include <memory>
#include <vector>
#include <string>
#include "DataSink.h"

class CDSVWriter {
private:
    std::shared_ptr<CDataSink> sink;
    char delimiter;
    bool quoteAll; // Whether to quote all values or only special cases

public:
    // Constructor
    CDSVWriter(std::shared_ptr<CDataSink> snk, char delim, bool quoteAll = false);

    // Destructor
    ~CDSVWriter();

    // Writes a row of values to the file
    bool WriteRow(const std::vector<std::string>& row);
};

#endif // CDSVWRITER_H
