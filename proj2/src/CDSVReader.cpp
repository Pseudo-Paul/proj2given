#include "CDSVReader.h"

struct CDSVReader::SImplementation {
    std::shared_ptr<CDataSource> source;
    char delimiter;

    SImplementation(std::shared_ptr<CDataSource> src, char delim)
        : source(src), delimiter(delim == '"' ? ',' : delim) {}

    bool HandleQuotedString(std::string& cell, bool& insideQuotes) {
        char ch;
        if (!source->Get(ch)) return false;

        if (ch == '"') {
            if (insideQuotes && source->Peek() == '"') {
                source->Get(ch); // Skip second quote
                cell += '"';
            } else {
                insideQuotes = !insideQuotes;
            }
            return true;
        }
        return false;
    }
};



CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delim)
    : DImplementation(std::make_unique<SImplementation>(src, delim)) {} 


CDSVReader::~CDSVReader() {}

bool CDSVReader::End() const {
    return DImplementation->source->End();
}



bool CDSVReader::ReadRow(std::vector<std::string>& row) {
    row.clear();
    if (DImplementation->source->End()) return false;

    std::string cell;
    char ch;
    bool insideQuotes = false;
    bool hasReadSomething = false;

    while (DImplementation->source->Get(ch)) {
        hasReadSomething = true;

        if (ch == '"') {
            if (!DImplementation->HandleQuotedString(cell, insideQuotes)) {  // ⬅️ FIXED: Now calls DImplementation->HandleQuotedString()
                break;
            }
        }
        else if (ch == DImplementation->delimiter && !insideQuotes) {  // ⬅️ FIXED: Calls DImplementation->delimiter
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
