#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <memory>
#include "XMLEntity.h"
#include "DataSink.h"

class XMLWriter{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;
        
    public:
        XMLWriter(std::shared_ptr< CDataSink > sink);
        ~XMLWriter();
        
        bool Flush();
        bool WriteEntity(const SXMLEntity &entity);
};

#endif
                                      