#ifndef DSVREADER_H
#define DSVREADER_H

#include <memory>
#include <vector>
#include <string>
#include "DataSource.h"

class DSVReader {
private:
    struct SImplementation;
    std::unique_ptr<SImplementation> DImplementation;

public:
    DSVReader(std::shared_ptr<CDataSource> src, char delimiter);
    ~DSVReader();

    DSVReader(const DSVReader&) = delete; // Prevent copy
    DSVReader& operator=(const DSVReader&) = delete;

    bool End() const;
    bool ReadRow(std::vector<std::string>& row);
};

#endif  // DSVREADER_H
