#ifndef CXMLREADER_H
#define CXMLREADER_H

#include <memory>
#include <string>
#include "DataSource.h"
#include "XMLEntity.h"
#include <expat.h>  // Expat XML Parser Library

class CXMLReader {
private:
    std::shared_ptr<CDataSource> source;
    XML_Parser parser;
    bool endOfFile;
    SXMLEntity currentEntity;
    static void StartElementHandler(void *userData, const char *name, const char **atts);
    static void EndElementHandler(void *userData, const char *name);
    static void CharacterDataHandler(void *userData, const char *data, int len);

public:
    // Constructor
    CXMLReader(std::shared_ptr<CDataSource> src);

    // Destructor
    ~CXMLReader();

    // Check if we have reached the end
    bool End() const;

    // Read an XML entity (element, text, etc.)
    bool ReadEntity(SXMLEntity &entity, bool skipCDATA = false);
};

#endif // CXMLREADER_H
