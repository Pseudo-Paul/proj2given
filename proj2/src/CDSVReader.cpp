#include "CDSVReader.h"

CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delim) 
    : source(src), delimiter(delim == '"' ? ',' : delim) {} // Convert quote delimiter to comma

CDSVReader::~CDSVReader() {}

bool CDSVReader::End() const {
    return source->End();
}

bool CDSVReader::HandleQuotedString(std::string& cell, bool& insideQuotes) {
    char ch;
    if (!source->Get(ch)) return false;
    
    if (ch == '"') {
        if (insideQuotes && source->Peek() == '"') {
            // Handle escaped quote (double quote)
            source->Get(ch); // Skip the second quote
            cell += '"';
        } else {
            // Toggle quote mode
            insideQuotes = !insideQuotes;
        }
        return true;
    }
    return false;
}

bool CDSVReader::ReadRow(std::vector<std::string>& row) {
    row.clear();
    if (source->End()) return false;

    std::string cell;
    char ch;
    bool insideQuotes = false;
    bool hasReadSomething = false;

    while (source->Get(ch)) {
        hasReadSomething = true;

        if (ch == '"') {
            if (!HandleQuotedString(cell, insideQuotes)) {
                break;
            }
        }
        else if (ch == delimiter && !insideQuotes) {
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

    // Handle last cell if exists
    if (hasReadSomething) {
        row.push_back(cell);
        return true;
    }

    return false;
}