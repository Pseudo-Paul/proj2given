#include "CDSVWriter.h"

CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> snk, char delim, bool quote_all) 
    : sink(snk), delimiter(delim == '"' ? ',' : delim), quoteAll(quote_all) {}

CDSVWriter::~CDSVWriter() {}

std::string CDSVWriter::QuoteValue(const std::string& value) const {
    // Check if value needs quoting
    bool needsQuotes = quoteAll || 
                      value.find(delimiter) != std::string::npos ||
                      value.find('"') != std::string::npos ||
                      value.find('\n') != std::string::npos;

    if (!needsQuotes) {
        return value;
    }

    std::string result = "\"";
    for (char ch : value) {
        if (ch == '"') {
            result += "\"\""; // Double the quotes for escaping
        } else {
            result += ch;
        }
    }
    result += "\"";
    return result;
}

bool CDSVWriter::WriteRow(const std::vector<std::string>& row) {
    if (!sink) return false;

    try {
        std::string line;
        line.reserve(row.size() * 8); // Pre-allocate space for efficiency

        for (size_t i = 0; i < row.size(); ++i) {
            line += QuoteValue(row[i]);
            
            if (i < row.size() - 1) {
                line += delimiter;
            }
        }
        line += '\n';

        return sink->Write(std::vector<char>(line.begin(), line.end()));
    } catch (const std::exception&) {
        return false;
    }
}