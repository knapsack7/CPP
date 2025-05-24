#include "../include/document.h"

// Initialize static member
Document* Document::instance = nullptr;

// Get singleton instance
Document* Document::getInstance() {
    if (instance == nullptr) {
        instance = new Document();
    }
    return instance;
}

// Document management methods
void Document::addElement(std::unique_ptr<DocumentElement> element) {
    elements.push_back(std::move(element));
}

void Document::removeElement(size_t index) {
    if (index < elements.size()) {
        elements.erase(elements.begin() + index);
    }
}

const std::vector<std::unique_ptr<DocumentElement>>& Document::getElements() const {
    return elements;
}

void Document::clear() {
    elements.clear();
} 