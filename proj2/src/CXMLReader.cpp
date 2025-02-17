#include "CXMLReader.h"
#include <iostream>
#include <vector>
#include <cstring>

CXMLReader::CXMLReader(std::shared_ptr<CDataSource> src) 
    : source(src), endOfFile(false) {
    std::cout << "✅ CXMLReader Constructor Called!" << std::endl;
    parser = XML_ParserCreate(nullptr);
    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, StartElementHandler, EndElementHandler);
    XML_SetCharacterDataHandler(parser, CharacterDataHandler);
}

CXMLReader::~CXMLReader() {
    std::cout << "❌ CXMLReader Destructor Called!" << std::endl;
    XML_ParserFree(parser);
}

bool CXMLReader::End() const {
    return endOfFile;
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipCDATA) {
    std::cout << "🔍 ReadEntity() called!" << std::endl; 

    char buffer[1024];
    std::vector<char> readBuffer;

    if (source->Read(readBuffer, sizeof(buffer))) {
        std::memcpy(buffer, readBuffer.data(), readBuffer.size());

        std::cout << "📄 Parsing buffer: " << std::string(buffer, readBuffer.size()) << std::endl;

        if (XML_Parse(parser, buffer, readBuffer.size(), source->End()) == XML_STATUS_ERROR) {
            std::cerr << "❌ XML Parsing Error: " << XML_ErrorString(XML_GetErrorCode(parser)) << std::endl;
            return false;
        }
        entity = currentEntity;
        return true;
    }

    std::cout << "⚠️ End of XML file reached." << std::endl;
    endOfFile = true;
    return false;
}

void CXMLReader::StartElementHandler(void *userData, const char *name, const char **atts) {
    CXMLReader *reader = static_cast<CXMLReader*>(userData);
    std::cout << "🟢 Start Element: " << name << std::endl;
    reader->currentEntity.DType = SXMLEntity::EType::StartElement;
    reader->currentEntity.DNameData = name;
}

void CXMLReader::EndElementHandler(void *userData, const char *name) {
    CXMLReader *reader = static_cast<CXMLReader*>(userData);
    std::cout << "🔴 End Element: " << name << std::endl;
    reader->currentEntity.DType = SXMLEntity::EType::EndElement;
    reader->currentEntity.DNameData = name;
}

void CXMLReader::CharacterDataHandler(void *userData, const char *data, int len) {
    CXMLReader *reader = static_cast<CXMLReader*>(userData);
    std::cout << "🔠 Character Data: " << std::string(data, len) << std::endl;
    reader->currentEntity.DType = SXMLEntity::EType::CompleteElement;
    reader->currentEntity.DNameData.assign(data, len);
}

