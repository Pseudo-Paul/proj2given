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
    std::string buffer;  // Holds data being processed

public:
    // Constructor
    CDSVReader(std::shared_ptr<CDataSource> src, char delim);

    // Destructor
    ~CDSVReader();

    // Returns true if all rows have been read
    bool End() const;

    // Reads a row into a vector of strings
    bool ReadRow(std::vector<std::string>& row);
};

#endif // CDSVREADER_H
