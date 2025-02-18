#ifndef CDSVREADER_H
#define CDSVREADER_H

#include <memory>
#include <vector>
#include <string>
#include "DataSource.h"

class CDSVReader {
private:
    std::shared_ptr<CDataSource> source;
    char delimiter;
    std::string buffer;

    // Helper function to handle quotes and special cases
    bool HandleQuotedString(std::string& cell, bool& insideQuotes);

public:
    // Constructor - takes data source and delimiter character
    CDSVReader(std::shared_ptr<CDataSource> src, char delim);
    
    // Destructor
    ~CDSVReader();

    // Returns true if all rows have been read
    bool End() const;

    // Reads a row into the provided vector
    bool ReadRow(std::vector<std::string>& row);
};

#endif