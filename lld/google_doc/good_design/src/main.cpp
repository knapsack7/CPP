#include "../include/document.h"
#include "../include/document_element.h"
#include "../include/document_renderer.h"
#include "../include/document_storage.h"
#include <iostream>

void printDocument(const Document* doc) {
    std::cout << "\nCurrent Document Contents:\n";
    std::cout << "------------------------\n";
    for (const auto& element : doc->getElements()) {
        std::cout << "Type: " << element->getType() << "\n";
        if (element->getType() == "text") {
            const TextElement* textElement = static_cast<const TextElement*>(element.get());
            std::cout << "Content: " << textElement->getContent() << "\n";
            std::cout << "Style: " << textElement->getStyle() << "\n";
        } else if (element->getType() == "image") {
            const ImageElement* imageElement = static_cast<const ImageElement*>(element.get());
            std::cout << "Path: " << imageElement->getImagePath() << "\n";
            std::cout << "Dimensions: " << imageElement->getWidth() << "x" << imageElement->getHeight() << "\n";
        } else if (element->getType() == "table") {
            const TableElement* tableElement = static_cast<const TableElement*>(element.get());
            std::cout << "Style: " << tableElement->getStyle() << "\n";
            std::cout << "Content: " << tableElement->getContent() << "\n";
        }
        std::cout << "------------------------\n";
    }
}

int main() {
    // Get document instance
    Document* doc = Document::getInstance();
    
    // Create some test elements
    auto textElement1 = std::make_unique<TextElement>("Hello, World!", "bold");
    auto textElement2 = std::make_unique<TextElement>("This is a test document.", "italic");
    auto imageElement = std::make_unique<ImageElement>("test.jpg", 800, 600);
    auto tableElement = std::make_unique<TableElement>();
    tableElement->setContent("Sample table data");
    tableElement->setStyle("bordered");
    
    // Add elements to document
    doc->addElement(std::move(textElement1));
    doc->addElement(std::move(textElement2));
    doc->addElement(std::move(imageElement));
    doc->addElement(std::move(tableElement));
    
    // Print initial document
    std::cout << "Initial Document:\n";
    printDocument(doc);
    
    // Save document
    DocumentStorage storage;
    const std::string filename = "test_document.json";
    if (storage.saveToFile(filename)) {
        std::cout << "\nDocument saved successfully to " << filename << "\n";
    } else {
        std::cout << "\nFailed to save document!\n";
        return 1;
    }
    
    // Clear document
    doc->clear();
    std::cout << "\nDocument cleared.\n";
    
    // Load document
    if (storage.loadFromFile(filename)) {
        std::cout << "\nDocument loaded successfully from " << filename << "\n";
    } else {
        std::cout << "\nFailed to load document!\n";
        return 1;
    }
    
    // Print loaded document
    std::cout << "\nLoaded Document:\n";
    printDocument(doc);
    
    return 0;
} 