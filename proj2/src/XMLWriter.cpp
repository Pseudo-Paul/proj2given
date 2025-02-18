#include "XMLWriter.h"

XMLWriter::XMLWriter(std::shared_ptr<CDataSink> snk) : sink(snk) {
    openTags.clear();
}

XMLWriter::~XMLWriter() {
    Flush();  // Ensure all tags are closed
}

bool XMLWriter::WriteEntity(const SXMLEntity &entity) {
    if (!sink) return false;

    std::string output;

    if (entity.DType == SXMLEntity::EType::StartElement) {
        output += "<" + entity.DNameData;

        for (const auto &attr : entity.DAttributes) {
            output += " " + attr.first + "=\"" + attr.second + "\"";
        }
        output += ">";
        openTags.push(entity.DNameData);
    }
    else if (entity.DType == SXMLEntity::EType::EndElement) {
        if (!openTags.empty() && openTags.top() == entity.DNameData) {
            openTags.pop();
            output += "</" + entity.DNameData + ">";
        }
    }
    else if (entity.DType == SXMLEntity::EType::CompleteElement) {
        output += entity.DNameData;
    }

    output += "\n";
    return sink->Write(output.c_str(), output.size());
}

bool XMLWriter::Flush() {
    while (!openTags.empty()) {
        std::string output = "</" + openTags.top() + ">\n";
        sink->Write(output.c_str(), output.size());
        openTags.pop();
    }
    return true;
}

