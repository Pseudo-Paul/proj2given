#include "CDSVReader.h"

CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delim) 
    : source(src), delimiter(delim) {}

CDSVReader::~CDSVReader() {}

bool CDSVReader::End() const {
    return source->End();
}

bool CDSVReader::ReadRow(std::vector<std::string>& row) {
    row.clear(); // Clear the row before reading new data
    if (source->End()) return false;

    std::string cell;
    char ch;
    bool insideQuotes = false; 

    while (source->Get(ch)) {  // Read one character at a time
        if (ch == '"') {
            insideQuotes = !insideQuotes; // Toggle quote mode
        } else if (ch == delimiter && !insideQuotes) {
            row.push_back(cell);
            cell.clear(); // Start new cell
        } else if (ch == '\n' && !insideQuotes) {
            break; // End of line
        } else {
            cell += ch;
        }
    }

    if (!cell.empty()) {
        row.push_back(cell); // Add last cell
    }

    return !row.empty();
}
