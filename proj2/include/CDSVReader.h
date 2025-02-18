#ifndef DSVREADER_H
#define DSVREADER_H

#include <memory>
#include <vector>
#include <string>
#include "DataSource.h"

class CDSVReader {
private:
    struct SImplementation; // Forward declare the struct
    std::unique_ptr<SImplementation> DImplementation; // Pointer to implementation

public:
    CDSVReader(std::shared_ptr<CDataSource> src, char delimiter);
    ~CDSVReader();

    bool End() const;
    bool ReadRow(std::vector<std::string>& row);
};

#endif
