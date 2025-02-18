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
    bool quoteAll;

    // Helper function to handle value quoting
    std::string QuoteValue(const std::string& value) const;

public:
    // Constructor - takes sink, delimiter, and quoting preference
    CDSVWriter(std::shared_ptr<CDataSink> snk, char delim, bool quoteAll = false);
    
    // Destructor
    ~CDSVWriter();

    // Writes a row of values
    bool WriteRow(const std::vector<std::string>& row);
};

#endif