#include <iostream>
#include "../include/CXMLReader.h"
#include "../include/StringDataSource.h"

int main() {
    std::string xmlData = "<root><name>Alice</name><age>25</age></root>";
    std::shared_ptr<CStringDataSource> source = std::make_shared<CStringDataSource>(xmlData);
    CXMLReader reader(source);

    SXMLEntity entity;
    while (reader.ReadEntity(entity)) {
        std::cout << "Type: " << (entity.DType == SXMLEntity::EType::StartElement ? "Start" : "End") 
                  << ", Name: " << entity.DNameData << std::endl;
    }

    return 0;
}
