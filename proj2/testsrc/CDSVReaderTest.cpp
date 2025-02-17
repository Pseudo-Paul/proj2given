#include <iostream>
#include "../include/CDSVReader.h"
#include "../include/StringDataSource.h"

int main() {  // ✅ This MUST be here
    std::string test_data = "name,age,city\nAlice,25,New York\nBob,30,Los Angeles";
    std::shared_ptr<CStringDataSource> source = std::make_shared<CStringDataSource>(test_data);
    CDSVReader reader(source, ',');

    std::vector<std::string> row;
    while (reader.ReadRow(row)) {
        for (const auto& cell : row) {
            std::cout << cell << " | ";
        }
        std::cout << std::endl;
    }

    return 0;
}
