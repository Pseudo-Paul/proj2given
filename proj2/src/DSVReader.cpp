// DSVReader.cpp
#include "DSVReader.h"

// Define the internal implementation structure (hidden from the user)
struct DSVReader::SImplementation {
    std::shared_ptr<CDataSource> source;  // Pointer to the data source (file, stream, etc.)
    char delimiter;  // Character used to separate values (e.g., ',' for CSV)

    SImplementation(std::shared_ptr<CDataSource> src, char delim)
        : source(src), delimiter(delim == '"' ? ',' : delim) {}

    bool HandleQuotedString(std::string& cell, bool& insideQuotes) {
        char ch;
        if (!source->Get(ch)) return false;

        if (ch == '"') {
            char nextChar;
if (insideQuotes && source->Peek(nextChar) && nextChar == '"') {

                source->Get(ch);
                cell += '"';
            } else {
                insideQuotes = !insideQuotes;
            }
            return true;
        }
        return false;
    }
};

// ✅ Fix constructor name
DSVReader::DSVReader(std::shared_ptr<CDataSource> src, char delim)
    : DImplementation(std::make_unique<SImplementation>(src, delim)) {}

DSVReader::~DSVReader() {}

bool DSVReader::End() const {
    return DImplementation->source->End();
}

bool DSVReader::ReadRow(std::vector<std::string>& row) {
    row.clear();
    if (DImplementation->source->End()) return false;

    std::string cell;
    char ch;
    bool insideQuotes = false;
    bool hasReadSomething = false;

    while (DImplementation->source->Get(ch)) {
        hasReadSomething = true;

        if (ch == '"') {
            if (!DImplementation->HandleQuotedString(cell, insideQuotes)) {
                break;
            }
        }
        else if (ch == DImplementation->delimiter && !insideQuotes) {
            row.push_back(cell);
            cell.clear();
        }
        else if (ch == '\n' && !insideQuotes) {
            row.push_back(cell);
            return true;
        }
        else {
            cell += ch;
        }
    }

    if (hasReadSomething) {
        row.push_back(cell);
        return true;
    }

    return false;
}
