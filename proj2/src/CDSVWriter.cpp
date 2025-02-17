#include "CDSVWriter.h"

CDSVWriter::CDSVWriter(std::shared_ptr<CDataSink> snk, char delim, bool quoteAll) 
    : sink(snk), delimiter(delim), quoteAll(quoteAll) {}

CDSVWriter::~CDSVWriter() {}

bool CDSVWriter::WriteRow(const std::vector<std::string>& row) {
    if (!sink) return false;

    std::string line;
    for (size_t i = 0; i < row.size(); ++i) {
        std::string cell = row[i];

        // Check if we need to quote the cell
        bool needsQuotes = quoteAll || cell.find(delimiter) != std::string::npos || 
                           cell.find('"') != std::string::npos || cell.find('\n') != std::string::npos;

        if (needsQuotes) {
            line += '"';
            for (char ch : cell) {
                if (ch == '"') line += "\"\""; // Escape double quotes
                else line += ch;
            }
            line += '"';
        } else {
            line += cell;
        }

        // Add delimiter except for the last column
        if (i < row.size() - 1) {
            line += delimiter;
        }
    }

    // Add newline at the end
    line += '\n';

    // Write the line to the sink
    std::vector<char> buffer(line.begin(), line.end());
    return sink->Write(buffer);
}
