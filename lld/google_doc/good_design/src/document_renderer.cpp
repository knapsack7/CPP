#include "document_renderer.h"

std::string DocumentRenderer::renderDocument() {
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