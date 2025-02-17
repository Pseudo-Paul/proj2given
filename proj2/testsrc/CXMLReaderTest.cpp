#include <iostream>
#include "../include/CXMLReader.h"
#include "../include/StringDataSource.h"

int main() {
    std::cout << "🚀 MAIN FUNCTION STARTED 🚀" << std::endl; // 🔥 Confirm main() runs

    std::string xmlData = "<root><name>Alice</name><age>25</age></root>";
    std::cout << "Creating CStringDataSource..." << std::endl;
    std::shared_ptr<CStringDataSource> source = std::make_shared<CStringDataSource>(xmlData);

    std::cout << "Creating CXMLReader..." << std::endl;
    CXMLReader reader(source);

    std::cout << "Starting XML Parsing..." << std::endl;

    SXMLEntity entity;
    int count = 0;
    while (reader.ReadEntity(entity)) {
        count++;
        std::cout << "Entity Read: " 
                  << ((entity.DType == SXMLEntity::EType::StartElement) ? "Start" : 
                     (entity.DType == SXMLEntity::EType::EndElement) ? "End" : "Complete") 
                  << " | Name: " << entity.DNameData << std::endl;
    }

    std::cout << "ReadEntity was called " << count << " times." << std::endl;
    std::cout << "XML Parsing Completed." << std::endl;
    return 0;
}
