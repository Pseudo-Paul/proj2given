#ifndef DSVWRITER_H
#define DSVWRITER_H

#include <memory>
#include <vector>
#include <string>
#include "DataSink.h"

class DSVWriter {
private:
    std::shared_ptr<CDataSink> sink;
    char delimiter;
    bool quoteAll;

    std::string QuoteValue(const std::string& value) const;

public:
    DSVWriter(std::shared_ptr<CDataSink> snk, char delimiter, bool quote_all = false);
    ~DSVWriter();

    bool WriteRow(const std::vector<std::string>& row);
};

#endif // DSVWRITER_H
