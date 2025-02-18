#ifndef XMLREADER_H
#define XMLREADER_H

#include <memory>
#include <string>
#include "DataSource.h"
#include "XMLEntity.h"
#include <expat.h>  // Expat XML Parser Library

class XMLReader {
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
    XMLReader(std::shared_ptr<CDataSource> src);

    // Destructor
    ~XMLReader();

    // Check if we have reached the end
    bool End() const;

    // Read an XML entity (element, text, etc.)
    bool ReadEntity(SXMLEntity &entity, bool skipCDATA = false);
};

#endif // XMLREADER_H
