#include <iostream>
#include <cassert>
#include "CDSVReader.h"
#include "StringDataSource.h"

void test_dsv_reader() {
    // Test case 1: Simple CSV parsing
    std::shared_ptr<CDataSource> source = std::make_shared<CStringDataSource>("a,b,c\n1,2,3\n");
    CDSVReader reader(source, ',');
    std::vector<std::string> row;
    
    bool success = reader.ReadRow(row);
    if (!success) {
        std::cerr << "Test failed: ReadRow returned false\n";
        return;
    }
    
    if (row.size() != 3) {
        std::cerr << "Test failed: Expected 3 columns, got " << row.size() << "\n";
        return;
    }
    
    if (row[0] != "a" || row[1] != "b" || row[2] != "c") {
        std::cerr << "Test failed: First row values incorrect\n";
        return;
    }
    
    std::cout << "DSV Reader tests passed!\n";
}

int main() {
    test_dsv_reader();
    return 0;
}