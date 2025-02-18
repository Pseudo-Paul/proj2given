#ifndef DSVREADER_H
#define DSVREADER_H

#include <memory>
#include <vector>
#include <string>
#include "DataSource.h"
#include <cstdlib>


class DSVReader {
private:
    struct SImplementation;
    std::unique_ptr<SImplementation> DImplementation;

public:
    DSVReader(std::shared_ptr<CDataSource> src, char delimiter);
    ~DSVReader();

    bool End() const;
    bool ReadRow(std::vector<std::string>& row);
};

#endif  // DSVREADER_H
