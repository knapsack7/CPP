#ifndef DOCUMENT_STORAGE_H
#define DOCUMENT_STORAGE_H

#include <string>
#include <fstream>
#include "../third_party/json.hpp"
#include "document.h"
#include "document_renderer.h"

using json = nlohmann::json;

class DocumentStorage {
public:
    DocumentStorage() = default;
    ~DocumentStorage() = default;
    
    // Save document to file in JSON format
    bool saveToFile(const std::string& filename);
    
    // Load document from JSON file
    bool loadFromFile(const std::string& filename);
    
private:
    // Helper methods for JSON conversion
    json elementToJson(const IDocumentElement& element);
    std::unique_ptr<IDocumentElement> jsonToElement(const json& j);
    
    // Helper methods for specific element types
    json textElementToJson(const TextElement& element);
    json imageElementToJson(const ImageElement& element);
    json tableElementToJson(const TableElement& element);
    
    std::unique_ptr<TextElement> jsonToTextElement(const json& j);
    std::unique_ptr<ImageElement> jsonToImageElement(const json& j);
    std::unique_ptr<TableElement> jsonToTableElement(const json& j);
};

#endif // DOCUMENT_STORAGE_H 