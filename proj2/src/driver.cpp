#include <iostream>
#include <memory>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"

int main() {
    std::cout << "🚀 Driver test running...\n" << std::endl;

    // Sample DSV content
    std::string sampleData = "Name,Age,City\nJohn,25,New York\nAlice,30,Los Angeles";

    // ✅ TEST DSVReader
    std::shared_ptr<CDataSource> src = std::make_shared<CStringDataSource>(sampleData);
    DSVReader reader(src, ',');
    std::vector<std::string> row;

    std::cout << "📖 Reading DSV Data:\n";
    while (reader.ReadRow(row)) {
        for (const auto& col : row) {
            std::cout << "[" << col << "] ";
        }
        std::cout << "\n";
    }

    
    std::shared_ptr<CDataSink> sink = std::make_shared<CStringDataSink>();
    DSVWriter writer(sink, ',');

    writer.WriteRow({"Bob", "22", "Chicago"});
    writer.WriteRow({"Eve", "28", "Houston"});
    writer.WriteRow({"Alice, Jr.", "19", "San Francisco"}); // Test escaping

    std::cout << "\n📝 DSV Output:\n" << sink->String() << std::endl;

    return
