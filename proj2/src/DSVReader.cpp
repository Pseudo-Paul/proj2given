#include "DSVReader.h"
#include <cstdlib>

// Internal implementation structure
struct DSVReader::SImplementation {
    std::shared_ptr<CDataSource> source; // Pointer to data source
    char delimiter; // Delimiter character

    SImplementation(std::shared_ptr<CDataSource> src, char delim)
        : source(src), delimiter(delim == '"' ? ',' : delim) {}

    bool HandleQuotedString(std::string& cell, bool& insideQuotes) {
        char ch;
        while (source->Get(ch)) {
            if (ch == '"') {
                char nextChar;
                if (source->Peek(nextChar) && nextChar == '"') {
                    // Handle escaped double quote ("" -> ")
                    source->Get(ch);
                    cell += '"';
                } else {
                    // Toggle insideQuotes state
                    insideQuotes = !insideQuotes;
                }
            } else {
                cell += ch;
            }

            if (!insideQuotes) return true; // Exit when quotes close
        }
        return false; // Unterminated quoted string
    }
};

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
                break; // Handle unterminated quoted string
            }
        }
        else if (ch == DImplementation->delimiter && !insideQuotes) {
            row.push_back(cell);
            cell.clear();
        }
        else if ((ch == '\n' || ch == '\r') && !insideQuotes) {
            if (ch == '\r') { // Handle Windows line endings (\r\n)
                DImplementation->source->Peek(ch);
                if (ch == '\n') {
                    DImplementation->source->Get(ch);
                }
            }
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
