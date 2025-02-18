#include "CDSVReader.h"  // Include the header file where CDSVReader is declared

// Define the internal implementation structure (hidden from the user)
struct CDSVReader::SImplementation {
    std::shared_ptr<CDataSource> source;  // Pointer to the data source (file, stream, etc.)
    char delimiter;  // Character used to separate values (e.g., ',' for CSV)

    // Constructor: Initializes the data source and delimiter
    SImplementation(std::shared_ptr<CDataSource> src, char delim)
        : source(src), delimiter(delim == '"' ? ',' : delim) {}  // If delimiter is a quote, use ',' instead

    // Handles quoted text inside a CSV cell
    bool HandleQuotedString(std::string& cell, bool& insideQuotes) {
        char ch;
        if (!source->Get(ch)) return false;  // Get next character, return false if end of file

        if (ch == '"') {  // If a quote is found
            if (insideQuotes && source->Peek() == '"') {  
                // If inside quotes and another quote follows, it's an escaped quote ("" -> ")
                source->Get(ch);  // Consume the second quote
                cell += '"';  // Add a single quote to the cell
            } else {
                insideQuotes = !insideQuotes;  // Toggle quote mode (enter or exit)
            }
            return true;  // Successfully processed a quote
        }
        return false;  // Not a special quote case
    }
};

// Constructor: Initializes the internal implementation object
CDSVReader::CDSVReader(std::shared_ptr<CDataSource> src, char delim)
    : DImplementation(std::make_unique<SImplementation>(src, delim)) {} 

// Destructor (automatically cleans up memory)
CDSVReader::~CDSVReader() {}

// Checks if the end of the file has been reached
bool CDSVReader::End() const {
    return DImplementation->source->End();  // Check if there's more data
}

// Reads a single row from the CSV file
bool CDSVReader::ReadRow(std::vector<std::string>& row) {
    row.clear();  // Clear the vector before reading a new row
    if (DImplementation->source->End()) return false;  // Stop if at the end of the file

    std::string cell;  // Stores the current value being read
    char ch;  // Character currently being processed
    bool insideQuotes = false;  // Tracks whether we're inside quotes
    bool hasReadSomething = false;  // Tracks whether any data was read

    while (DImplementation->source->Get(ch)) {  // Read each character one by one
        hasReadSomething = true;  // Mark that we have read something

        if (ch == '"') {  
            // If a quote is found, process it using the helper function
            if (!DImplementation->HandleQuotedString(cell, insideQuotes)) {
                break;  // Stop if there's an issue handling the quote
            }
        }
        else if (ch == DImplementation->delimiter && !insideQuotes) {  
            // If a delimiter (e.g., comma) is found outside of quotes, store the cell
            row.push_back(cell);  // Add the value to the row
            cell.clear();  // Reset the cell for the next value
        }
        else if (ch == '\n' && !insideQuotes) {  
            // If a newline is found and we're not inside quotes, complete the row
            row.push_back(cell);  // Save the last value in the row
            return true;  // Successfully read a full row
        }
        else {  
            // Otherwise, add the character to the current cell
            cell += ch;
        }
    }

    // If we read at least some data before the file ended, save the last value
    if (hasReadSomething) {
        row.push_back(cell);
        return true;
    }

    return false;  // No data read (empty file or error)
}
