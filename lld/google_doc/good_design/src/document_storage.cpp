#include "../include/document_storage.h"
#include <sstream>

bool DocumentStorage::saveToFile(const std::string& filename) {
    Document* doc = Document::getInstance();
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Create JSON array to store all elements
    json documentJson = json::array();
    
    // Convert each element to JSON
    for (const auto& element : doc->getElements()) {
        documentJson.push_back(elementToJson(*element));
    }
    
    // Write JSON to file with pretty printing
    file << documentJson.dump(4);
    file.close();
    return true;
}

bool DocumentStorage::loadFromFile(const std::string& filename) {
    Document* doc = Document::getInstance();
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    try {
        // Read JSON from file
        json documentJson;
        file >> documentJson;
        file.close();

        // Clear existing document
        doc->clear();

        // Convert JSON back to elements
        for (const auto& elementJson : documentJson) {
            doc->addElement(jsonToElement(elementJson));
        }
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

json DocumentStorage::elementToJson(const IDocumentElement& element) {
    json j;
    j["type"] = element.getType();
    
    // Convert specific element types
    if (element.getType() == "text") {
        const TextElement& textElement = static_cast<const TextElement&>(element);
        j.merge_patch(textElementToJson(textElement));
    } else if (element.getType() == "image") {
        const ImageElement& imageElement = static_cast<const ImageElement&>(element);
        j.merge_patch(imageElementToJson(imageElement));
    } else if (element.getType() == "table") {
        const TableElement& tableElement = static_cast<const TableElement&>(element);
        j.merge_patch(tableElementToJson(tableElement));
    }
    
    return j;
}

std::unique_ptr<IDocumentElement> DocumentStorage::jsonToElement(const json& j) {
    std::string type = j["type"];
    
    if (type == "text") {
        return jsonToTextElement(j);
    } else if (type == "image") {
        return jsonToImageElement(j);
    } else if (type == "table") {
        return jsonToTableElement(j);
    }
    
    return nullptr;
}

json DocumentStorage::textElementToJson(const TextElement& element) {
    json j;
    j["content"] = element.getContent();
    j["style"] = element.getStyle();
    return j;
}

json DocumentStorage::imageElementToJson(const ImageElement& element) {
    json j;
    j["path"] = element.getImagePath();
    j["width"] = element.getWidth();
    j["height"] = element.getHeight();
    return j;
}

json DocumentStorage::tableElementToJson(const TableElement& element) {
    json j;
    j["data"] = element.getData();
    j["style"] = element.getStyle();
    return j;
}

std::unique_ptr<TextElement> DocumentStorage::jsonToTextElement(const json& j) {
    return std::make_unique<TextElement>(j["content"], j["style"]);
}

std::unique_ptr<ImageElement> DocumentStorage::jsonToImageElement(const json& j) {
    auto element = std::make_unique<ImageElement>(j["path"]);
    element->setDimensions(j["width"], j["height"]);
    return element;
}

std::unique_ptr<TableElement> DocumentStorage::jsonToTableElement(const json& j) {
    auto element = std::make_unique<TableElement>();
    element->setData(j["data"]);
    element->setStyle(j["style"]);
    return element;
}