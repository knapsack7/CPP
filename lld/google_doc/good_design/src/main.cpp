#include "../include/document.h"
#include "../include/document_element.h"
#include "../include/document_renderer.h"
#include "../include/document_storage.h"
#include <iostream>

int main() {
    // Get the singleton document instance
    Document* doc = Document::getInstance();
    
    // Create and add text elements
    doc->addElement(std::make_shared<TextElement>("Welcome to Document Editor!"));
    doc->addElement(std::make_shared<TextElement>("This is a sample document."));
    
    // Create and add image elements
    doc->addElement(std::make_shared<ImageElement>("sample.jpg"));
    doc->addElement(std::make_shared<ImageElement>("logo.png"));
    
    // Add more text
    doc->addElement(std::make_shared<TextElement>("End of document."));
    
    // Render the document
    DocumentRenderer renderer;
    std::cout << "Rendered Document:\n";
    std::cout << renderer.renderDocument() << std::endl;
    
    // Save the document
    DocumentStorage storage;
    if (storage.saveToFile("output.txt")) {
        std::cout << "Document saved successfully to output.txt" << std::endl;
    } else {
        std::cout << "Failed to save document" << std::endl;
    }
    
    return 0;
} 