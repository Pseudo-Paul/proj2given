#include "XMLReader.h"
#include <iostream>
#include <vector>
#include <cstring>

XMLReader::XMLReader(std::shared_ptr<CDataSource> src) 
    : source(src), endOfFile(false) {
    parser = XML_ParserCreate(nullptr);
    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);
    XML_SetCharacterDataHandler(parser, CharacterDataHandler);
}

XMLReader::~XMLReader() {
    XML_ParserFree(parser);
}

bool XMLReader::End() const {
    return endOfFile;
}

bool XMLReader::ReadEntity(SXMLEntity &entity, bool skipCDATA) {
    char buffer[1024];
    std::vector<char> readBuffer;

    if (!source->Read(readBuffer, sizeof(buffer))) {
        endOfFile = true;
        return false;
    }

    std::memcpy(buffer, readBuffer.data(), readBuffer.size());

    if (XML_Parse(parser, buffer, readBuffer.size(), source->End()) == XML_STATUS_ERROR) {
        std::cerr << "❌ XML Parsing Error: " << XML_ErrorString(XML_GetErrorCode(parser)) << std::endl;
        return false;
    }

    entity = currentEntity;  // ✅ Assigns parsed entity correctly
    currentEntity = SXMLEntity();  // ✅ Reset entity for the next call
    return true;
}

void XMLReader::StartElementHandler(void *userData, const char *name, const char **atts) {
    XMLReader *reader = static_cast<XMLReader*>(userData);
    reader->currentEntity.DType = SXMLEntity::EType::StartElement;
    reader->currentEntity.DNameData = name;

    reader->currentEntity.DAttributes.clear();  // ✅ Clears attributes from previous elements

    while (*atts) {  // ✅ Parses attributes correctly
        SXMLEntity::TAttribute attr;
        attr.first = *atts++;
        attr.second = *atts++;
        reader->currentEntity.DAttributes.push_back(attr);
    }
}

void XMLReader::EndElementHandler(void *userData, const char *name) {
    XMLReader *reader = static_cast<XMLReader*>(userData);
    reader->currentEntity.DType = SXMLEntity::EType::EndElement;
    reader->currentEntity.DNameData = name;
}

void XMLReader::CharacterDataHandler(void *userData, const char *data, int len) {
    XMLReader *reader = static_cast<XMLReader*>(userData);
    if (len > 0) {
        reader->currentEntity.DType = SXMLEntity::EType::CompleteElement;
        reader->currentEntity.DNameData.assign(data, len);
    }
}
