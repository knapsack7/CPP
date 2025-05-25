#include "../include/document_storage.h"

bool DocumentStorage::saveToFile(const std::string& filename) {
    Document* doc = Document::getInstance();
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    TextRenderer textRenderer;
    ImageRenderer imageRenderer;
    DocumentRenderer textDocRenderer(&textRenderer);
    DocumentRenderer imageDocRenderer(&imageRenderer);
    for (const auto& element : doc->getElements()) {
        if (element->getType() == "text") {
            file << textDocRenderer.render(*element) << std::endl;
        } else if (element->getType() == "image") {
            file << imageDocRenderer.render(*element) << std::endl;
        }
    }
    file.close();
    return true;
}

bool DocumentStorage::loadFromFile(const std::string& filename) {
    // Implementation for loading document from file
    // This would parse the file and create appropriate DocumentElements
    return true;
}