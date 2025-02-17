#include "CXMLReader.h"
#include <iostream>
#include <vector>
#include <cstring>

CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) 
    : source(src), endOfFile(false) {
    parser = XML_ParserCreate(nullptr);
    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);
    XML_SetCharacterDataHandler(parser, CharacterDataHandler);
}

CXMLReader::~CXMLReader() {
    XML_ParserFree(parser);
}

bool CXMLReader::End() const {
    return endOfFile;
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipCDATA) {
    char buffer[1024];
    std::vector<char> readBuffer;

    if (source->Read(readBuffer, sizeof(buffer))) {
        std::memcpy(buffer, readBuffer.data(), readBuffer.size());
        if (XML_Parse(parser, buffer, readBuffer.size(), source->End()) == XML_STATUS_ERROR) {
            std::cerr << "XML Parsing Error: " << XML_ErrorString(XML_GetErrorCode(parser)) << std::endl;
            return false;
        }
        entity = currentEntity;
        return true;
    }
    endOfFile = true;
    return false;
}

void CXMLReader::StartElementHandler(void *userData, const char *name, const char **atts) {
    CXMLReader *reader = static_cast<CXMLReader*>(userData);
    reader->currentEntity.DType = SXMLEntity::EType::StartElement;
    reader->currentEntity.DNameData = name;

    reader->currentEntity.DAttributes.clear();
    for (int i = 0; atts[i]; i += 2) {
        reader->currentEntity.DAttributes.push_back({atts[i], atts[i + 1]});
    }
}

void CXMLReader::EndElementHandler(void *userData, const char *name) {
    CXMLReader *reader = static_cast<CXMLReader*>(userData);
    reader->currentEntity.DType = SXMLEntity::EType::EndElement;
    reader->currentEntity.DNameData = name;
}

void CXMLReader::CharacterDataHandler(void *userData, const char *data, int len) {
    CXMLReader *reader = static_cast<CXMLReader*>(userData);
    reader->currentEntity.DType = SXMLEntity::EType::CompleteElement;
    reader->currentEntity.DNameData.assign(data, len);
}
