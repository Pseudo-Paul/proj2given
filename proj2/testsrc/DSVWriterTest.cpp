#include <iostream>
#include "../include/DSVWriter.h"
#include "../include/StringDataSink.h"

int main() {
    std::shared_ptr<CStringDataSink> sink = std::make_shared<CStringDataSink>();
    DSVWriter writer(sink, ',', false);

    std::vector<std::string> row1 = {"Alice", "25", "New York"};
    std::vector<std::string> row2 = {"Bob", "30", "Los Angeles"};

    writer.WriteRow(row1);
    writer.WriteRow(row2);

    std::cout << "Written Data:\n" << sink->String() << std::endl;

    return 0;
}
