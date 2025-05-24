#ifndef DOCUMENT_RENDERER_H
#define DOCUMENT_RENDERER_H

#include <string>
#include <memory>
#include "document.h"
#include "document_element.h"

class DocumentRenderer {
public:
    std::string renderDocument() {
        std::string result;
        Document* doc = Document::getInstance();
        
        for (const auto& element : doc->getElements()) {
            if (element->getType() == "text") {
                result += element->getContent() + "\n";
            } else if (element->getType() == "image") {
                result += "[Image: " + element->getContent() + "]\n";
            }
        }
        
        return result;
    }
};

#endif // DOCUMENT_RENDERER_H 